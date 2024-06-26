/** @file main.c
 *  @brief A multi-threaded application using Zephyr RTOS.
 *
 *  This application initializes hardware components including LEDs, buttons, ADC, and UART.
 *  It creates and manages three threads with different periodicities and priorities.
 *  - Thread A: Reads button states, controls LEDs, and toggles their states.
 *  - Thread B: Reads ADC values periodically.
 *  - Thread C: Prints sensor readings and UART data.
 *
 *  Dependencies:
 *  - Zephyr RTOS
 *  - GPIO, ADC, UART drivers
 *  - DeviceTree configuration for hardware components
 *
 *  Error Codes:
 *  - OK: Operation successful
 *  - Error: Operation failed
 *
 *  Mutexes:
 *  - Buttons_Mutex: Synchronizes access to button states.
 *  - Leds_Mutex: Synchronizes access to LED states.
 *  - ADC_Mutex: Synchronizes access to ADC operations.
 *  - UART_Mutex: Synchronizes access to UART operations.
 *  - Sensores_Mutex: Synchronizes access to sensor readings.
 *
 *  Timers:
 *  - thread_A_timer: Timer for thread A.
 *  - thread_B_timer: Timer for thread B.
 *  - thread_C_timer: Timer for thread C.
 *
 *  Thread Details:
 *  - Thread A: Controls LEDs based on button press and sensor values.
 *  - Thread B: Reads ADC value and updates sensor readings.
 *  - Thread C: Prints sensor readings and UART data.
 * 
 * @author 
 * - Pedro Afonso (104206)
 * - Carlos Teixeira (103187)
 *
 * @date 04/06/2024
 */

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
#define thread_A_prio 2 /* Higher priority */ 
#define thread_B_prio 2 /* Middle priority */
#define thread_C_prio 3 /* Lower priority */

/* Thread periodicity (in ms)*/
#define thread_A_period 200
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
K_MUTEX_DEFINE(Sensores_Mutex);

/* GPIO Initialization*/
/*Define the number of leds and buttons*/
#define Num_Leds 4
#define Num_Buts 4
#define Num_Sensores 4

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

/** 
 * @brief Takes one ADC sample
 * 
 * @return 0 on success, error code otherwise
 */
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
#define RX_TIMEOUT 1000                 /* Inactivity period after the instant when last char was received that triggers an rx event (in us) */
#define UART_NODE DT_NODELABEL(uart0)   /* UART0 node ID*/
#define RXBUF_SIZE 30

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
static u_int8_t rx_buf_1[RXBUF_SIZE];      /* RX buffer 1, to store received data */
static u_int8_t rx_buf_2[RXBUF_SIZE];      /* RX buffer 2, to store received data */
static u_int8_t rx_chars[RXBUF_SIZE];    /* chars actually received  */
static u_int8_t uart_rxbuf_nchar = 0;        /* Number of chars currently on the rx buffer */
bool buffer = 1;

/* UART callback function prototype */
static void uart_cb(const struct device *dev, struct uart_event *evt, void *user_data);


/* Global variables */
static int ret=0;
volatile bool LedsStates[Num_Leds] = {0};
volatile bool ButsStates[Num_Buts] = {0};
volatile uint16_t ADC_Raw = 0;
volatile uint16_t ADC_Voltage = 0;
volatile uint16_t Sensores[4] = {0};


/** 
 * @brief Hardware initialization function
 * 
 * @return 0 on success, error code otherwise
 */
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
        printk("device_is_ready(uart_dev) is false.\n\r");
        return Error;
    }

    /* Configure UART */
    ret = uart_configure(uart_dev, &uart_cfg);
    if (ret < 0) {
        printk("uart_configure() error. Errorcode:%d\n\r", ret);
        return Error;
    }

    /* Initialize UART RX buffers */
    ret = uart_rx_enable(uart_dev, rx_buf_1, RXBUF_SIZE, RX_TIMEOUT);
    if (ret < 0) {
        printk("uart_rx_enable() error. Errorcode:%d\n\r", ret);
        return Error;
    }
    
    /* Setup UART interrupt handler */
    uart_callback_set(uart_dev, uart_cb, NULL);  /* Note: a reference to the function is passed, i.e., no parentheses */


    return OK;
}

/**
 * @brief UART callback function, called on UART event.
 * 
 * @param dev Pointer to UART device
 * @param evt Pointer to UART event structure
 * @param user_data User data provided when callback was registered
 */
static void uart_cb(const struct device *dev, struct uart_event *evt, void *user_data)
{
        switch(evt->type)
        {
            case UART_TX_DONE:
                //printk("UART_TX_DONE\n\r");
                break;
            case UART_TX_ABORTED:
                printk("UART_TX_ABORTED\n\r");
                break;
            case UART_RX_RDY:
                //printk("UART_RX_RDY\n\r");
                memcpy(rx_chars, &evt->data.rx.buf[evt->data.rx.offset], evt->data.rx.len);
                uart_rxbuf_nchar = evt->data.rx.len;
                break;
            case UART_RX_BUF_REQUEST:
                if(buffer) {uart_rx_buf_rsp(uart_dev, rx_buf_2, RXBUF_SIZE);}
                else {uart_rx_buf_rsp(uart_dev, rx_buf_1, RXBUF_SIZE);}
                buffer = !buffer;
                break;
            case UART_RX_BUF_RELEASED:
                //printk("UART_RX_BUF_RELEASED\n\r");
                break;
            case UART_RX_DISABLED:
                //printk("UART_RX_DISABLED\n\r");
                break;
            case UART_RX_STOPPED:
                printk("UART_RX_STOPPED\n\r");
                break;
            default:
                printk("UART: unknown event\n\r");
                break;
        }
}

/** 
 * @brief Function for reading sensors
 * 
 * @return 0 on success, error code otherwise
 */
int Read_Sensores()
{
    int s = 0;
    k_mutex_lock(&Sensores_Mutex, K_FOREVER);
    for (s = 0; s < Num_Sensores; s++)
    {
        /* Dummy read values */
        Sensores[s] = 10*s;
    }
    k_mutex_unlock(&Sensores_Mutex);
    return OK;
}

/**
 * @brief Thread A code. Controls LED based on button press and sensor values.
 *
 * @param argA Pointer to argument A
 * @param argB Pointer to argument B
 * @param argC Pointer to argument C
 */
void thread_A_code(void *argA , void *argB, void *argC)
{
    int64_t fin_time=0, release_time=0; 
    int n=0;

    printk("Thread A init (periodic)\n");

    release_time = k_uptime_get() + thread_A_period;

    while(1) {
        /* Computation */
        k_mutex_lock(&Buttons_Mutex, K_FOREVER);
        for (n = 0; n < Num_Buts; n++)
        {
            ButsStates[n] = gpio_pin_get_dt(&buts[n]);
        }
        k_mutex_unlock(&Buttons_Mutex);

        k_mutex_lock(&Leds_Mutex, K_FOREVER);
        for (n = 0; n < Num_Leds; n++)
        {
            if (ButsStates[n] == 0) {LedsStates[n] = !LedsStates[n];}
            gpio_pin_set_dt(&leds[n], LedsStates[n]);
        }
        k_mutex_unlock(&Leds_Mutex);

        printk("Thread A periodic job\n");

        /* Wait for next release */
        fin_time = k_uptime_get();
        if( fin_time < release_time) {
            k_msleep(release_time - fin_time);
            release_time += thread_A_period;
        }
    }
}


/**
 * @brief Thread B code. Reads ADC value and updates sensor readings.
 *
 * @param argA Pointer to argument A
 * @param argB Pointer to argument B
 * @param argC Pointer to argument C
 */
void thread_B_code(void *argA , void *argB, void *argC)
{
    int64_t fin_time=0, release_time=0; 
    int16_t buf;
    printk("Thread B init (periodic)\n");

    release_time = k_uptime_get() + thread_B_period;

    while(1) {

        /* Computation */
        k_mutex_lock(&ADC_Mutex, K_FOREVER);
        adc_sample();
        buf = adc_sample_buffer[0];
        k_mutex_unlock(&ADC_Mutex);

        printk("Thread B periodic job\n");

        /* Wait for next release */
        fin_time = k_uptime_get();
        if( fin_time < release_time) {
            k_msleep(release_time - fin_time);
            release_time += thread_B_period;
        }
    }
}


/**
 * @brief Thread C code. Prints sensor readings and UART data.
 *
 * @param argA Pointer to argument A
 * @param argB Pointer to argument B
 * @param argC Pointer to argument C
 */
void thread_C_code(void *argA , void *argB, void *argC)
{
    int64_t fin_time=0, release_time=0; 
    char str[80];
    int n = 0;
    printk("Thread C init (periodic)\n");

    release_time = k_uptime_get() + thread_C_period;

    while(1) {
        /* Computation */
        k_mutex_lock(&UART_Mutex, K_FOREVER);
        if (uart_rxbuf_nchar > 0) {
            uart_rxbuf_nchar = 0;
            printk("Data received: %s\n", rx_chars);
        }
        k_mutex_unlock(&UART_Mutex);

        k_mutex_lock(&Sensores_Mutex, K_FOREVER);
        for (n = 0; n < Num_Sensores; n++)
        {
            printk("Sensor %d: %d\n", n, Sensores[n]);
        }
        k_mutex_unlock(&Sensores_Mutex);

        printk("Thread C periodic job\n");

        /* Wait for next release */
        fin_time = k_uptime_get();
        if( fin_time < release_time) {
            k_msleep(release_time - fin_time);
            release_time += thread_C_period;
        }
    }
}


/**
 * @brief Main function. Initializes hardware and starts threads.
 *
 * @return Always returns 0.
 */
void main(void)
{
    int ret = Init();
    if (ret != OK) {
        printk("Initialization error. Exiting.\n");
        return;
    }

    printk("Main Init done\n");

    thread_A_tid = k_thread_create(&thread_A_data, thread_A_stack,
                    K_THREAD_STACK_SIZEOF(thread_A_stack), thread_A_code,
                    NULL, NULL, NULL, thread_A_prio, 0, K_NO_WAIT);

    k_thread_name_set(thread_A_tid, "thread_A");

    thread_B_tid = k_thread_create(&thread_B_data, thread_B_stack,
                    K_THREAD_STACK_SIZEOF(thread_B_stack), thread_B_code,
                    NULL, NULL, NULL, thread_B_prio, 0, K_NO_WAIT);

    k_thread_name_set(thread_B_tid, "thread_B");

    thread_C_tid = k_thread_create(&thread_C_data, thread_C_stack,
                    K_THREAD_STACK_SIZEOF(thread_C_stack), thread_C_code,
                    NULL, NULL, NULL, thread_C_prio, 0, K_NO_WAIT);

    k_thread_name_set(thread_C_tid, "thread_C");
}

