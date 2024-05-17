/*
 * Paulo Pedreiras, 2024/03
 * Zephyr: Simple thread and Digital Input Interrupt example
 * 
 *  Button 1 generates an interrupt that toggles a global var
 *  A Periodic task updates LED status according to global var
 *  Also shows how a single callback can handle multiple gpio interrupts
 *
 * Base documentation:
 *  Zephyr kernel:  
 *      https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/zephyr/kernel/services/index.html#kernel-services
 *      
 *  DeviceTree 
 *      Board DTS can be found in BUILD_DIR/zephyr/zephyr.dts
 *      https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/zephyr/guides/dts/api-usage.html#dt-from-c  
 *
 *      HW info
 *      https://infocenter.nordicsemi.com/topic/struct_nrf52/struct/nrf52840.html
 *      Section: nRF52840 Product Specification -> Peripherals -> GPIO / GPIOTE
 * 
 *      Board specific HW info can be found in the nRF52840_DK_User_Guide_20201203. I/O pins available at pg 27
 * 
 * 
 */
#include <zephyr/kernel.h>          /* for kernel functions*/
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <zephyr/timing/timing.h>   /* for timing services */

/* Error codes */
#define ERR_OK       0
#define ERR_CFG     -1
#define ERR_RDY     -2

/* Size of stack area used by each thread (can be thread specific, if necessary)*/
#define STACK_SIZE 1024

/* Thread scheduling priority */
#define thread_A_prio 1

/* Therad periodicity (in ms)*/
#define thread_A_period 20


/* Create thread stack space */
K_THREAD_STACK_DEFINE(thread_A_stack, STACK_SIZE);
  
/* Create variables for thread data */
struct k_thread thread_A_data;

/* Create task IDs */
k_tid_t thread_A_tid;

/* Thread code prototypes */
void thread_A_code(void *, void *, void *);

/* Get node IDs. Refer to dts file and HW documentation*/
#define LED0_NID DT_NODELABEL(led0) 
#define BUT0_NID DT_NODELABEL(button0) 
#define BUT1_NID DT_NODELABEL(button1) 
#define BUT2_NID DT_NODELABEL(button2) 
#define BUT3_NID DT_NODELABEL(button3) 

/* Get gpio device structures */
const struct gpio_dt_spec led0_dev = GPIO_DT_SPEC_GET(LED0_NID,gpios);
const struct gpio_dt_spec but0_dev = GPIO_DT_SPEC_GET(BUT0_NID,gpios);
const struct gpio_dt_spec but1_dev = GPIO_DT_SPEC_GET(BUT1_NID,gpios);
const struct gpio_dt_spec but2_dev = GPIO_DT_SPEC_GET(BUT2_NID,gpios);
const struct gpio_dt_spec but3_dev = GPIO_DT_SPEC_GET(BUT3_NID,gpios);

/* Int related declarations */
static struct gpio_callback but_cb_data; /* Callback structure */

/* Callback function and variables*/
volatile int ledstat = 0; /* Led status variable. Updated by the callback function */

void butpress_cbfunction(const struct device *dev, struct gpio_callback *cb, uint32_t pins) {
    
    /* Test each button ...*/
    if(BIT(but0_dev.pin) & pins) {
        /* Update global var*/
        ledstat=!ledstat;
        printk("BUT0 pressed - Led will toggle! \n\r");
    }

    if(BIT(but1_dev.pin) & pins) {
        /* Update global var*/        
        printk("BUT1 pressed - Led shall not toggle!\n\r");
    }

    if(BIT(but2_dev.pin) & pins) {
        /* Update global var*/        
        printk("BUT2 pressed - Led shall not toggle!\n\r");
    }

    if(BIT(but3_dev.pin) & pins) {
        /* Update global var*/        
        printk("BUT3 pressed - Led shall not toggle!\n\r");
    }

}


/* Main function */
int main(void) {
    int ret;

    /* Welcome message */
    printk("\n\r Press BUT1 to toggle the led.\n\r");

    /* Check device status */   
	if (!device_is_ready(led0_dev.port))  
	{
        printk("Fatal error: led0 device not ready!");
		return ERR_RDY;
	}

    if (!device_is_ready(but0_dev.port))  
	{
        printk("Fatal error: but0 device not ready!");
		return ERR_RDY;
	}

    if (!device_is_ready(but1_dev.port))  
	{
        printk("Fatal error: but1 device not ready!");
		return ERR_RDY;
	}

    if (!device_is_ready(but2_dev.port))  
	{
        printk("Fatal error: but2 device not ready!");
        return ERR_RDY;
	}

    if (!device_is_ready(but3_dev.port))  
	{
        printk("Fatal error: but3 device not ready!");
		return ERR_RDY;
	}
    
    
    /* Configure PINS */
    ret = gpio_pin_configure_dt(&led0_dev, led0_dev.dt_flags | GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("Error %d: Failed to configure LED 0 \n\r", ret);
	    return ERR_CFG;
    }

    ret = gpio_pin_configure_dt(&but0_dev, GPIO_INPUT | GPIO_PULL_UP);
    if (ret < 0) {
        printk("Error %d: Failed to configure BUT 0 \n\r", ret);
	    return ERR_CFG;
    }

    ret = gpio_pin_configure_dt(&but1_dev, GPIO_INPUT | GPIO_PULL_UP);
    if (ret < 0) {
        printk("Error %d: Failed to configure BUT 1 \n\r", ret);
	    return ERR_CFG;
    }

    ret = gpio_pin_configure_dt(&but2_dev, GPIO_INPUT | GPIO_PULL_UP);
    if (ret < 0) {
        printk("Error %d: Failed to configure BUT 2 \n\r", ret);
	    return ERR_CFG;
    }

    ret = gpio_pin_configure_dt(&but3_dev, GPIO_INPUT | GPIO_PULL_UP);
    if (ret < 0) {
        printk("Error %d: Failed to configure BUT 3 \n\r", ret);
	    return ERR_CFG;
    }

    /* Set interrupt HW - which pin and event generate interrupt */
    ret = gpio_pin_interrupt_configure_dt(&but0_dev, GPIO_INT_EDGE_TO_ACTIVE);
    if (ret != 0) {
	    printk("Error %d: failed to configure interrupt on BUT0 pin \n\r", ret);
	    return ERR_CFG;
    }

    /* Set interrupt HW - which pin and event generate interrupt */
    ret = gpio_pin_interrupt_configure_dt(&but1_dev, GPIO_INT_EDGE_TO_ACTIVE);
    if (ret != 0) {
	    printk("Error %d: failed to configure interrupt on BUT1 pin \n\r", ret);
	    return ERR_CFG;
    }

    /* Set interrupt HW - which pin and event generate interrupt */
    ret = gpio_pin_interrupt_configure_dt(&but2_dev, GPIO_INT_EDGE_TO_ACTIVE);
    if (ret != 0) {
	    printk("Error %d: failed to configure interrupt on BUT2 pin \n\r", ret);
	    return ERR_CFG;
    }

    /* Set interrupt HW - which pin and event generate interrupt */
    ret = gpio_pin_interrupt_configure_dt(&but3_dev, GPIO_INT_EDGE_TO_ACTIVE);
    if (ret != 0) {
	    printk("Error %d: failed to configure interrupt on BUT3 pin \n\r", ret);
	    return ERR_CFG;
    }
    
    /* Set callback */
    gpio_init_callback(&but_cb_data, butpress_cbfunction, BIT(but0_dev.pin)| BIT(but1_dev.pin)| BIT(but2_dev.pin) | BIT(but3_dev.pin));
    
    gpio_add_callback(but0_dev.port, &but_cb_data);
    gpio_add_callback(but1_dev.port, &but_cb_data);
    gpio_add_callback(but2_dev.port, &but_cb_data);
    gpio_add_callback(but3_dev.port, &but_cb_data);

    
    /* Then create the task */
    thread_A_tid = k_thread_create(&thread_A_data, thread_A_stack,
        K_THREAD_STACK_SIZEOF(thread_A_stack), thread_A_code,
        NULL, NULL, NULL, thread_A_prio, 0, K_NO_WAIT);


    return ERR_OK;

} 

/* Thread code implementation */
void thread_A_code(void *argA , void *argB, void *argC)
{
    /* Local vars */
    int64_t fin_time=0, release_time=0;     /* Timing variables to control task periodicity */    
        
    /* Task init code */
    printk("Thread A init (periodic)\n");

    /* Compute next release instant */
    release_time = k_uptime_get() + thread_A_period;

    /* Thread loop */
    while(1) {        
               
        if(ledstat)
            gpio_pin_set_dt(&led0_dev, 1);
        else
            gpio_pin_set_dt(&led0_dev, 0);
       
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

