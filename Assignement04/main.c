#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <zephyr/timing/timing.h>

/* Error codes */
#define OK  0
#define Error -1

/* Size of stack area used by each thread (can be thread specific, if necessary)*/
#define STACK_SIZE 1024

/* Thread scheduling priority: 1...MAX, decreasing (smaller value -> Higher priority) */
#define thread_A_prio 1 /* Higher priority */ 

/* Thread periodicity (in ms)*/
#define thread_A_period 100

/* Create thread stack space */
K_THREAD_STACK_DEFINE(thread_A_stack, STACK_SIZE);
  
/* Create variables for thread data */
struct k_thread thread_A_data;

/* Create task IDs */
k_tid_t thread_A_tid;

/* Thread code prototypes */
void thread_A_code(void *argA, void *argB, void *argC);

/* Define timers for tasks activations */
K_TIMER_DEFINE(thread_A_timer, NULL, NULL);

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

static int ret=0;

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
        ret = gpio_pin_configure_dt(&buts[i], GPIO_INPUT | GPIO_PULL_DOWN);
        if (ret < 0) {
            printk("Error: gpio_pin_configure_dt failed for button%d, error:%d", i, ret);
            return Error;
        }
    }

    /* Successfully initialized */
    return OK;
}


int main (){
    ret = Init();
    if (ret < 0) {
        return Error;
    }
    
    /* Crate three tasks */
    thread_A_tid = k_thread_create(&thread_A_data, thread_A_stack,
        K_THREAD_STACK_SIZEOF(thread_A_stack), thread_A_code,
        NULL, NULL, NULL, thread_A_prio, 0, K_NO_WAIT);


    return OK;
}


/* Thread code implementation */
void thread_A_code(void *argA , void *argB, void *argC)
{
    /* Local vars */
    int64_t fin_time=0, release_time=0, init_time=0;     /* Timing variables to control task periodicity */
        
    /* Task init code */
    printk("Thread A init (periodic)\n");
               
    /* Compute next release instant */
    release_time = k_uptime_get() + thread_A_period;

    /* Thread loop */
    while(1) {        
        
        init_time = k_uptime_get();
        printk("Thread A activated\n\r");  
        
        for (int i = 0; i < Num_Buts; i++) {
           if(gpio_pin_get_dt(&buts[i])) {
               gpio_pin_set_dt(&leds[i],1);
               printk("but0 active\n\r");
           } else {
               gpio_pin_set_dt(&leds[i],0);
               printk("but0 not active\n\r");
           }
        }
        /* Wait for next release instant */ 
        fin_time = k_uptime_get();
        printk("Thread A Ended -> Time %lld\n\r",(fin_time-init_time)); 
         
        if( fin_time < release_time) {
            k_msleep(release_time - fin_time);
            release_time += thread_A_period;

        }
    }

    /* Stop timing functions */
    timing_stop();
}
