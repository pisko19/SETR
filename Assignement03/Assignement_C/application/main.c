
#include "../src/sc_types.h"
#include "../src-gen/Statechart_required.h"
#include "../src-gen/Statechart.h"
#include "timers.h"
/* Includes. Add according to the resources used  */
#include <zephyr/kernel.h>          /* for k_msleep() */
#include <zephyr/device.h>          /* for device_is_ready() and device structure */
#include <zephyr/devicetree.h>	    /* for DT_NODELABEL() */
#include <zephyr/drivers/gpio.h>    /* for GPIO api*/
#include <zephyr/sys/printk.h>      /* for printk()*/

#define ERR_ABORT -1
/* Get led0 and button0 node IDs. Refer to the DTS file */
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define BUT0_NODE DT_ALIAS(sw0)
#define BUT1_NODE DT_ALIAS(sw1)
#define BUT2_NODE DT_ALIAS(sw2)
#define BUT3_NODE DT_ALIAS(sw3)

/* Get the device pointer, pin number, and configuration flags for led0 and button 0. A build error on this line means your board is unsupported. */
static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec but0 = GPIO_DT_SPEC_GET(BUT0_NODE, gpios);
static const struct gpio_dt_spec but1 = GPIO_DT_SPEC_GET(BUT1_NODE, gpios);
static const struct gpio_dt_spec but2 = GPIO_DT_SPEC_GET(BUT2_NODE, gpios);
static const struct gpio_dt_spec but3 = GPIO_DT_SPEC_GET(BUT3_NODE, gpios);

static struct gpio_callback button0_cb_data;
static struct gpio_callback button1_cb_data;
static struct gpio_callback button2_cb_data;
static struct gpio_callback button3_cb_data;

static int ret = 0;

int Check_Function(){

   // Verify the state of the leds and the buttons
   if (!device_is_ready(led0.port)) {
        printk("Error: led0 device %s is not ready\n", led0.port->name);
   	return ERR_ABORT;
   }
   if (!device_is_ready(led1.port)) {
        printk("Error: led1 device %s is not ready\n", led1.port->name);
   	return ERR_ABORT;
   }
   if (!device_is_ready(but0.port)) {
        printk("Error: but0 device %s is not ready\n", but0.port->name);
   	return ERR_ABORT;
   }
   if (!device_is_ready(but1.port)) {
        printk("Error: but1 device %s is not ready\n", but1.port->name);
   	return ERR_ABORT;
   }
   if (!device_is_ready(but2.port)) {
        printk("Error: but3 device %s is not ready\n", but2.port->name);
   	return ERR_ABORT;
   }
   if (!device_is_ready(but3.port)) {
        printk("Error: but4 device %s is not ready\n", but3.port->name);
   	return ERR_ABORT;
   }
   return 0;
}

int Init_Function(){
   // Initialize the led and the buttons
   // Use internal pull-up to avoid the need for an external resitor (button)
   ret = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
   if (ret < 0) {
	printk("Error: gpio_pin_configure_dt failed for led0, error:%d", ret);
	return ERR_ABORT;
   }
   ret = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE);
   if (ret < 0) {
	printk("Error: gpio_pin_configure_dt failed for led1, error:%d", ret);
	return ERR_ABORT;
   }
   ret = gpio_pin_configure_dt(&but0, GPIO_INPUT | GPIO_PULL_UP);
   if (ret < 0) {
	printk("Error: gpio_pin_configure_dt failed for button0, error:%d", ret);
	return ERR_ABORT;
   }
   ret = gpio_pin_configure_dt(&but1, GPIO_INPUT | GPIO_PULL_UP);
   if (ret < 0) {
	printk("Error: gpio_pin_configure_dt failed for button1, error:%d", ret);
	return ERR_ABORT;
   }
   ret = gpio_pin_configure_dt(&but2, GPIO_INPUT | GPIO_PULL_UP);
   if (ret < 0) {
	printk("Error: gpio_pin_configure_dt failed for button2, error:%d", ret);
	return ERR_ABORT;
   }
   ret = gpio_pin_configure_dt(&but3, GPIO_INPUT | GPIO_PULL_UP);
   if (ret < 0) {
	printk("Error: gpio_pin_configure_dt failed for button3, error:%d", ret);
	return ERR_ABORT;
   }
   
   /* Set Interrupts*/
   ret = gpio_pin_interrupt_configure_dt(&but0, GPIO_INT_EDGE_TO_ACTIVE);
   if (ret < 0) {
	printk("Error: gpio_pin_interrupt_configure_dt failed for button0, error:%d", ret);
	return ERR_ABORT;
   }
   ret = gpio_pin_interrupt_configure_dt(&but1, GPIO_INT_EDGE_TO_ACTIVE);
   if (ret < 0) {
	printk("Error: gpio_pin_interrupt_configure_dt failed for button1, error:%d", ret);
	return ERR_ABORT;
   }
   ret = gpio_pin_interrupt_configure_dt(&but2, GPIO_INT_EDGE_TO_ACTIVE);
   if (ret < 0) {
	printk("Error: gpio_pin_interrupt_configure_dt failed for button2, error:%d", ret);
	return ERR_ABORT;
   }
   ret = gpio_pin_interrupt_configure_dt(&but3, GPIO_INT_EDGE_TO_ACTIVE);
   if (ret < 0) {
	printk("Error: gpio_pin_interrupt_configure_dt failed for button3, error:%d", ret);
	return ERR_ABORT;
   }
   
   return 0;

}

int main (){
   
   ret = Check_Function();
   if (ret < 0) {
	return ERR_ABORT;
   }
   
   ret = Init_Function();
   if (ret < 0) {
	return ERR_ABORT;
   }
   
   gpio_init_callback(&button0_cb_data, button0Pressed, BIT(but0.pin));
   gpio_add_callback(but0.port, &button0_cb_data);
   
   gpio_init_callback(&button1_cb_data, button1Pressed, BIT(but1.pin));
   gpio_add_callback(but1.port, &button1_cb_data);
   
   gpio_init_callback(&button2_cb_data, button2Pressed, BIT(but2.pin));
   gpio_add_callback(but2.port, &button2_cb_data);
   
   gpio_init_callback(&button3_cb_data, button3Pressed, BIT(but3.pin));
   gpio_add_callback(but3.port, &button3_cb_data);
   
   
   return 0;
}

void button0Pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    /* Toggle led0 */
   gpio_pin_toggle_dt(&led0);
   
   return;  

}
void button1Pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    /* Toggle led1 */
   gpio_pin_toggle_dt(&led1);
   
   return;  

}
void button2Pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    /* Toggle led0 */
   gpio_pin_toggle_dt(&led0);
   
   return;  

}
void button3Pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    /* Toggle led1 */
   gpio_pin_toggle_dt(&led1);
   
   return;  

}