/* Includes. Add according to the resources used  */
#include <zephyr/kernel.h>          /* for k_msleep() */
#include <zephyr/device.h>          /* for device_is_ready() and device structure */
#include <zephyr/devicetree.h>	    /* for DT_NODELABEL() */
#include <zephyr/drivers/gpio.h>    /* for GPIO API*/
#include <zephyr/drivers/adc.h>     /* for ADC API*/
#include <zephyr/drivers/uart.h>    /* for UART API*/
#include <zephyr/sys/printk.h>      /* for printk()*/
#include <zephyr/timing/timing.h>
#include <stdio.h>                  /* for sprintf() */
#include <stdlib.h>
#include <string.h>

/* Error codes */
#define OK  0
#define Error -1

/* Thread Initialization */
/* Size of stack area used by each thread (can be thread specific, if necessary)*/
#define STACK_SIZE 1024

/* Thread scheduling priority: 1...MAX, decreasing (smaller value -> Higher priority) */
#define thread_A_prio 1 /* Higher priority */ 
#define thread_B_prio 2 /* Middle priority */
#define thread_C_prio 3 /* Lower priority */

/* Thread periodicity (in ms)*/
#define thread_A_period 5
#define thread_B_period 10
#define thread_C_period 200

/* Create thread stack space */
K_THREAD_STACK_DEFINE(thread_A_stack, STACK_SIZE);
K_THREAD_STACK_DEFINE(thread_B_stack, STACK_SIZE);
K_THREAD_STACK_DEFINE(thread_C_stack, STACK_SIZE); 
  
/* Create variables for thread data */
struct k_thread thread_A_data;
struct k_thread thread_B_data;
struct k_thread thread_C_data;

/* Create task IDs */
k_tid_t thread_A_tid;
k_tid_t thread_B_tid;
k_tid_t thread_C_tid;

/* Thread code prototypes */
void thread_A_code(void *argA, void *argB, void *argC);
void thread_B_code(void *argA, void *argB, void *argC);
void thread_C_code(void *argA, void *argB, void *argC);

/* Define timers for tasks activations */
K_TIMER_DEFINE(thread_A_timer, NULL, NULL);
K_TIMER_DEFINE(thread_B_timer, NULL, NULL);
K_TIMER_DEFINE(thread_C_timer, NULL, NULL);

/*Define mutex */
K_MUTEX_DEFINE(Buttons_Mutex);
K_MUTEX_DEFINE(Leds_Mutex);
K_MUTEX_DEFINE(ADC_Mutex);
K_MUTEX_DEFINE(UART_Mutex);

/* GPIO Initialization*/
/*Define the number of leds and buttons*/
#define Num_Leds 4
#define Num_Buts 4

#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)
#define LED3_NODE DT_ALIAS(led3)
#define BUT0_NODE DT_ALIAS(sw0)
#define BUT1_NODE DT_ALIAS(sw1)
#define BUT2_NODE DT_ALIAS(sw2)
#define BUT3_NODE DT_ALIAS(sw3)

static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);
static const struct gpio_dt_spec led3 = GPIO_DT_SPEC_GET(LED3_NODE, gpios);
static const struct gpio_dt_spec leds[Num_Leds] = {led0, led1, led2, led3};

static const struct gpio_dt_spec but0 = GPIO_DT_SPEC_GET(BUT0_NODE, gpios);
static const struct gpio_dt_spec but1 = GPIO_DT_SPEC_GET(BUT1_NODE, gpios);
static const struct gpio_dt_spec but2 = GPIO_DT_SPEC_GET(BUT2_NODE, gpios);
static const struct gpio_dt_spec but3 = GPIO_DT_SPEC_GET(BUT3_NODE, gpios);
static const struct gpio_dt_spec buts[Num_Buts] = {but0, but1, but2, but3};

/*ADC Initialization*/
/*ADC definitions and includes*/
#include <hal/nrf_saadc.h>
#define ADC_RESOLUTION 10
#define ADC_GAIN ADC_GAIN_1_4
#define ADC_REFERENCE ADC_REF_VDD_1_4
#define ADC_ACQUISITION_TIME ADC_ACQ_TIME(ADC_ACQ_TIME_MICROSECONDS, 40)
#define ADC_CHANNEL_ID 1  
#define ADC_CHANNEL_INPUT NRF_SAADC_INPUT_AIN1 

#define BUFFER_SIZE 1

#define ADC_NODE DT_NODELABEL(adc)  
const struct device *adc_dev = DEVICE_DT_GET(ADC_NODE);	

/* ADC channel configuration */
static const struct adc_channel_cfg my_channel_cfg = {
	.gain = ADC_GAIN,
	.reference = ADC_REFERENCE,
	.acquisition_time = ADC_ACQUISITION_TIME,
	.channel_id = ADC_CHANNEL_ID,
	.input_positive = ADC_CHANNEL_INPUT
};

static uint16_t adc_sample_buffer[BUFFER_SIZE];

/* Takes one sample */
static int adc_sample(void)
{
	int ret;
	const struct adc_sequence sequence = {
		.channels = BIT(ADC_CHANNEL_ID),
		.buffer = adc_sample_buffer,
		.buffer_size = sizeof(adc_sample_buffer),
		.resolution = ADC_RESOLUTION,
	};

	if (adc_dev == NULL) {
            printk("adc_sample(): error, must bind to adc first \n\r");
            return -1;
	}

	ret = adc_read(adc_dev, &sequence);
	if (ret) {
            printk("adc_read() failed with code %d\n", ret);
	}	

	return ret;
}

/*UART Initializaton*/
#define RXBUF_SIZE 2                    /* RX buffer size */
#define TXBUF_SIZE 60                   /* TX buffer size */
#define MSG_BUF_SIZE 100                /* Buffer for messages sent vai UART */
#define RX_TIMEOUT 1000                 /* Inactivity period after the instant when last char was received that triggers an rx event (in us) */
#define UART_NODE DT_NODELABEL(uart0)   /* UART0 node ID*/

/* Struct for UART configuration. */
const struct uart_config uart_cfg = {
		.baudrate = 115200,
		.parity = UART_CFG_PARITY_NONE,
		.stop_bits = UART_CFG_STOP_BITS_1,
		.data_bits = UART_CFG_DATA_BITS_8,
		.flow_ctrl = UART_CFG_FLOW_CTRL_NONE
};


/* UART related variables */
const struct device *uart_dev = DEVICE_DT_GET(UART_NODE);
static uint8_t rx_buf[RXBUF_SIZE];      /* RX buffer, to store received data */
static uint8_t rx_chars[RXBUF_SIZE];    /* chars actually received  */
volatile int uart_rxbuf_nchar=0;        /* Number of chars currrntly on the rx buffer */

/* UART callback function prototype */
static void uart_cb(const struct device *dev, struct uart_event *evt, void *user_data);


/*Glocal variables */
static int ret=0;
volatile bool LedsStates[Num_Leds] = {0};
volatile bool ButsStates[Num_Buts] = {0};
volatile uint16_t ADC_Raw = 0;
volatile uint16_t ADC_Voltage = 0;


/* Hardware initialization */
int Init(void) {

    // Check the leds and configure them 
    for (int i = 0; i < Num_Leds; i++) {
        if (!device_is_ready(leds[i].port)) {
            printk("Error: led%d device %s is not ready\n", i, leds[i].port->name);
            return Error;
        }
    }
    for (int i = 0; i < Num_Leds; i++) {
        ret = gpio_pin_configure_dt(&leds[i], GPIO_OUTPUT_ACTIVE);
        if (ret < 0) {
            printk("Error: gpio_pin_configure_dt failed for led%d, error:%d", i, ret);
            return Error;
        }
    }

    // Check the buttons and configure them
    for (int i = 0; i < Num_Buts; i++) {
        if (!device_is_ready(buts[i].port)) {
            printk("Error: button%d device %s is not ready\n", i, buts[i].port->name);
            return Error;
        }
    }
    for (int i = 0; i < Num_Buts; i++) {
        ret = gpio_pin_configure_dt(&buts[i], GPIO_INPUT | GPIO_PULL_UP);
        if (ret < 0) {
            printk("Error: gpio_pin_configure_dt failed for button%d, error:%d", i, ret);
            return Error;
        }
    }

    /* Set-up ADC channel */
    ret = adc_channel_setup(adc_dev, &my_channel_cfg);
    if (ret) {
        printk("adc_channel_setup() failed with error code %d\n", ret);
        return Error;
    }
    
    /* It is recommended to calibrate the SAADC at least once before use, and whenever the ambient temperature has changed by more than 10 °C */
    NRF_SAADC->TASKS_CALIBRATEOFFSET = 1;


    /* Check if uart device is open */
    if (!device_is_ready(uart_dev)) {
        printk("device_is_ready(uart) returned error! Aborting! \n\r");
        return Error;
    }
    
    /* Configure UART */
    ret = uart_configure(uart_dev, &uart_cfg);
    if (ret == -ENOSYS) { /* If invalid configuration */
        printk("uart_configure() error. Invalid configuration\n\r");
        return Error; 
    }
        
    /* Register callback */
    ret = uart_callback_set(uart_dev, uart_cb, NULL);
    if (ret) {
        printk("uart_callback_set() error. Error code:%d\n\r",ret);
        return Error;
    }
    
    /* Enable data reception */
    ret =  uart_rx_enable(uart_dev ,rx_buf,sizeof(rx_buf),RX_TIMEOUT);
    if (ret) {
        printk("uart_rx_enable() error. Error code:%d\n\r",ret);
        return Error;
    }
    /* Successfully initialized */
    return OK;
}

/* MAIN */
int main (){
    ret = Init();
    if (ret < 0) {
        return Error;
    }
    printk("\x1B[2J\x1B[H");
    
    /* Crate three tasks */
    thread_A_tid = k_thread_create(&thread_A_data, thread_A_stack,
        K_THREAD_STACK_SIZEOF(thread_A_stack), thread_A_code,
        NULL, NULL, NULL, thread_A_prio, 0, K_NO_WAIT);

    thread_B_tid = k_thread_create(&thread_B_data, thread_B_stack,
        K_THREAD_STACK_SIZEOF(thread_B_stack), thread_B_code,
        NULL, NULL, NULL, thread_B_prio, 0, K_NO_WAIT);

    thread_C_tid = k_thread_create(&thread_C_data, thread_C_stack,
        K_THREAD_STACK_SIZEOF(thread_C_stack), thread_C_code,
        NULL, NULL, NULL, thread_C_prio, 0, K_NO_WAIT);
    return OK;
}


/* Thread code implementation 
   Thread A -> Responsible to read the buttons satates and set the leds*/

void thread_A_code(void *argA , void *argB, void *argC)
{
    /* Local vars */
    int64_t fin_time=0, release_time=0, init_time=0;     /* Timing variables to control task periodicity */
    int j = 0;
               
    /* Compute next release instant */
    release_time = k_uptime_get() + thread_A_period;

    /* Thread loop */
    while(1) {        
        
        init_time = k_uptime_get();

        /*Block the mutex corresponding to the buttons*/
        ret = k_mutex_lock(&Buttons_Mutex,K_FOREVER);
        if (ret < 0){
            printk("Error: Buttons mutex doesn't lock, error:%d",ret);
            break;
        }
        
        /*Set the state of the buttons to an array*/
        for (int i = 0; i < Num_Buts; i++) {
            ButsStates[i] = gpio_pin_get_dt(&buts[i]);    
        }
        
        /*Unblock the mutex corresponding to the buttons*/
        ret = k_mutex_unlock(&Buttons_Mutex);
        if (ret < 0){
            printk("Error: Buttons mutex doesn't unlock, error:%d",ret);
            break;
        }
        
        /*Block the mutex corresponding to the leds*/
        ret = k_mutex_lock(&Leds_Mutex,K_FOREVER);
        if (ret < 0){
            printk("\n\rError: Buttons mutex doesn't lock, error:%d",ret);
            break;
        }

        LedsStates[j] = (1 - LedsStates[j]);
        j = ((j+1) % 4);
        
        for (int i = 0; i < Num_Leds; i++){
           gpio_pin_set_dt(&leds[i],LedsStates[i]);
        }
        
        /*Unblock the mutex corresponding to the leds*/
        ret = k_mutex_unlock(&Leds_Mutex);
        if (ret < 0){
            printk("\n\rError: Buttons mutex doesn't unlock, error:%d",ret);
            break;
        }

        /* Wait for next release instant */ 
        fin_time = k_uptime_get();

        if( fin_time < release_time) {
            k_msleep(release_time - fin_time);
            release_time += thread_A_period;
        }
    }

    /* Stop timing functions */
    timing_stop();
}

/* Thread B -> Responsible to read the ADC RAW and convert to the respective voltage*/
void thread_B_code(void *argA , void *argB, void *argC)
{
    /* Local vars */
    int64_t fin_time=0, release_time=0, init_time=0;     /* Timing variables to control task periodicity */
    
    /* Compute next release instant */
    release_time = k_uptime_get() + thread_B_period;

    while(1){
        init_time = k_uptime_get();

        /*Block the mutex corresponding to the ADC*/
        ret = k_mutex_lock(&ADC_Mutex,K_FOREVER);
        if (ret < 0){
            printk("Error: Buttons mutex doesn't lock, error:%d",ret);
            break;
        }

        /* Get one sample, checks for errors and prints the values */
        ret=adc_sample();
        if(ret) {
            printk("\n\radc_sample() failed with error code %d\n\r",ret);
            break;
        }
        else {
            if(adc_sample_buffer[0] > 1023) {
                printk("\n\radc reading out of range (value is %u)\n\r", adc_sample_buffer[0]);
            }
            else {
                ADC_Raw = adc_sample_buffer[0];
                /* ADC is set to use gain of 1/4 and reference VDD/4, so input range is 0...VDD (3 V), with 10 bit resolution */
                ADC_Voltage = (1000 * adc_sample_buffer[0])*((float)3/1023);
            }
        }

        /*Unblock the mutex corresponding to the ADC*/
        ret = k_mutex_unlock(&ADC_Mutex);
        if (ret < 0){
            printk("Error: Buttons mutex doesn't lock, error:%d",ret);
            break;
        }

        /* Wait for next release instant */ 
        fin_time = k_uptime_get();

        if(fin_time < release_time) {
            k_msleep(release_time - fin_time);
            release_time += thread_B_period;

        }
    }
    /* Stop timing functions */
    timing_stop();
}

void thread_C_code(void *argA, void *argB, void *argC){

    /* Local vars */
    int64_t fin_time=0, release_time=0, init_time=0;     /* Timing variables to control task periodicity */
    
    /* Compute next release instant */
    release_time = k_uptime_get() + thread_C_period;

    uint8_t welcome_mesg[] = "What operation you want to do ?\n\r1 -> See buttons states\n\r2 -> See leds states\n\r";

    while(1){

        //printk("\x1B[2J\x1B[H");
        init_time = k_uptime_get();

        ret = uart_tx(uart_dev, welcome_mesg, sizeof(welcome_mesg), SYS_FOREVER_MS);
        if (ret) {
            printk("uart_tx() error. Error code:%d\n\r",ret);
            break;
        }
        
        if(uart_rxbuf_nchar>0){
            switch (rx_chars[0])
            {
            case '1':
                printk("\x1B[2J");
                while(rx_chars[0]!= '0'){
                    printk("\x1B[H");
                    printk("The states of the button are:\n");
                    for (int i=0; i < Num_Buts; i++){
                        printk("The state of button%d is %d\n\r",i,ButsStates[i]);
                    }
                }
                break;

            default:
                break;
            }
        }
        /* Wait for next release instant */ 
        fin_time = k_uptime_get();

        if(fin_time < release_time) {
            k_msleep(release_time - fin_time);
            release_time += thread_C_period;

        }
    }
    /* Stop timing functions */
    timing_stop();
}
/* UART callback implementation */
/* Note that callback functions are executed in the scope of interrupt handlers. */
/* They run asynchronously after hardware/software interrupts and have a higher priority than tasks/threads */
/* Should be kept as short and simple as possible. Heavier processing should be deferred to a task with suitable priority*/
static void uart_cb(const struct device *dev, struct uart_event *evt, void *user_data)
{   
    int err;
    
    switch (evt->type) {
	
        case UART_TX_DONE:
		    //printk("UART_TX_DONE event \n\r");
            break;

    	case UART_TX_ABORTED:
	    	//printk("UART_TX_ABORTED event \n\r");
		    break;
		
	    case UART_RX_RDY:
		    printk("UART_RX_RDY event \n\r");
            /* Just copy data to a buffer. */
            /* Simple approach, just for illustration. In most cases it is necessary to use */
            /*    e.g. a FIFO or a circular buffer to communicate with a task that shall process the messages*/
            memcpy(&rx_chars[uart_rxbuf_nchar],&(rx_buf[evt->data.rx.offset]),evt->data.rx.len); 
            uart_rxbuf_nchar++;           
		    break;

	    case UART_RX_BUF_REQUEST:
		    printk("UART_RX_BUF_REQUEST event \n\r");
            /* Should be used to allow continuous reception */
            /* To this end, declare at least two buffers and switch among them here */
            /*      using function uart_rx_buf_rsp() */
		    break;

	    case UART_RX_BUF_RELEASED:
		    printk("UART_RX_BUF_RELEASED event \n\r");
            uart_rxbuf_nchar = 0; 
		    break;
		
	    case UART_RX_DISABLED: 
            /* When the RX_BUFF becomes full RX is disabled automaticaly.  */
            /* It must be re-enabled manually for continuous reception */
            printk("UART_RX_DISABLED event \n\r");
		    err =  uart_rx_enable(uart_dev ,rx_buf,sizeof(rx_buf),RX_TIMEOUT);
            if (err) {
                printk("uart_rx_enable() error. Error code:%d\n\r",err);
                exit(Error);                
            }
		    break;

	    case UART_RX_STOPPED:
		    printk("UART_RX_STOPPED event \n\r");
		    break;
		
	    default:
            printk("UART: unknown event \n\r");
		    break;
    }
}