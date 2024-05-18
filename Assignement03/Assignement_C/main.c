
#include "../src/sc_types.h"
#include "../src-gen/Statechart_required.h"
#include "../src-gen/Statechart.h"
/* Includes. Add according to the resources used  */
#include <zephyr/kernel.h>          /* for k_msleep() */
#include <zephyr/device.h>          /* for device_is_ready() and device structure */
#include <zephyr/devicetree.h>	    /* for DT_NODELABEL() */
#include <zephyr/drivers/gpio.h>    /* for GPIO api*/
#include <zephyr/sys/printk.h>      /* for printk()*/

#define ERR_ABORT -1
#define Num_Leds 4
#define Num_Buts 4
/* Get leds and buttons node IDs. Refer to the DTS file */
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)
#define LED3_NODE DT_ALIAS(led3)
#define BUT0_NODE DT_ALIAS(sw0)
#define BUT1_NODE DT_ALIAS(sw1)
#define BUT2_NODE DT_ALIAS(sw2)
#define BUT3_NODE DT_ALIAS(sw3)

/* Get the device pointer, pin number, and configuration flags for leds and buttons. A build error on this line means your board is unsupported. */
static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);
static const struct gpio_dt_spec led3 = GPIO_DT_SPEC_GET(LED3_NODE, gpios);
static const struct gpio_dt_spec leds[Num_Leds] = {led0,led1,led2,led3};

static const struct gpio_dt_spec but0 = GPIO_DT_SPEC_GET(BUT0_NODE, gpios);
static const struct gpio_dt_spec but1 = GPIO_DT_SPEC_GET(BUT1_NODE, gpios);
static const struct gpio_dt_spec but2 = GPIO_DT_SPEC_GET(BUT2_NODE, gpios);
static const struct gpio_dt_spec but3 = GPIO_DT_SPEC_GET(BUT3_NODE, gpios);
static const struct gpio_dt_spec buts[Num_Buts] = {but0,but1,but2,but3};

static struct gpio_callback button0_cb_data;
static struct gpio_callback button1_cb_data;
static struct gpio_callback button2_cb_data;
static struct gpio_callback button3_cb_data;

static int ret = 0;
static Statechart StateMachine;

int Check_Function(){

   for(int i=0; i<Num_Leds; i++){
      // Verify the state of the leds
      if (!device_is_ready(leds[i].port)) {
          printk("Error: led%d device %s is not ready\n", i,leds[i].port->name);
          return ERR_ABORT;
      }
   }
   
   for(int i=0; i<Num_Buts; i++){
      // Verify the state of the leds
      if (!device_is_ready(buts[i].port)) {
          printk("Error: button%d device %s is not ready\n", i,buts[i].port->name);
          return ERR_ABORT;
      }
   }
   
   return 0;
}

int Init_Function(){

   for(int i=0; i<Num_Leds; i++){
      // Initialize the led
      ret = gpio_pin_configure_dt(&leds[i], GPIO_OUTPUT_ACTIVE);
      if (ret < 0) {
	  printk("Error: gpio_pin_configure_dt failed for led%d, error:%d", i,ret);
	  return ERR_ABORT;
      }
   }
   
   for(int i=0; i<Num_Buts; i++){
      /* Initialize the buttons 
      Use internal pull-up to avoid the need for an external resitor (button)*/
      ret = gpio_pin_configure_dt(&buts[i], GPIO_INPUT | GPIO_PULL_UP);
      if (ret < 0) {
	  printk("Error: gpio_pin_configure_dt failed for button%d, error:%d", i,ret);
	  return ERR_ABORT;
      }
      
      /* Set Interrupts*/
      ret = gpio_pin_interrupt_configure_dt(&buts[i], GPIO_INT_EDGE_TO_ACTIVE);
      if (ret < 0) {
          printk("Error: gpio_pin_interrupt_configure_dt failed for button%d, error:%d", i,ret);
	  return ERR_ABORT;
      }
   }
   
   return 0;

}

void statechart_setLeds( Statechart* handle, const sc_integer Leds){
   
   switch(Leds){
      case(0):
         for(int i=0; i<Num_Leds; i++){
             ret = gpio_pin_set_dt(&leds[i],0);
             if (ret < 0) {
                 printk("Error: gpio_pin_set_dt failed for led%d, error:%d", i,ret);
	         return;
            }
         }
         break;
         
      case(1):
        for(int i=0; i<Num_Leds; i++){
             if(i<2){
                ret = gpio_pin_set_dt(&leds[i],1-i);
                if (ret < 0) {
                    printk("Error: gpio_pin_set_dt failed for led%d, error:%d", i,ret);
	            return;
                }
             }
             else{
                ret = gpio_pin_set_dt(&leds[i],0);
                if (ret < 0) {
                    printk("Error: gpio_pin_set_dt failed for led%d, error:%d", i,ret);
	            return;
                }
             }
        }
        break;
        
      case(2):
        for(int i=0; i<Num_Leds; i++){
             if(i<2){
                ret = gpio_pin_set_dt(&leds[i],i);
                if (ret < 0) {
                    printk("Error: gpio_pin_set_dt failed for led%d, error:%d", i,ret);
	            return;
                }
             }
             else{
                ret = gpio_pin_set_dt(&leds[i],0);
                if (ret < 0) {
                    printk("Error: gpio_pin_set_dt failed for led%d, error:%d", i,ret);
	            return;
                }
             }
        }
        break;
        
      case(3):
         for(int i=0; i<Num_Leds; i++){
             if(i<2){
                ret = gpio_pin_set_dt(&leds[i],1);
                if (ret < 0) {
                    printk("Error: gpio_pin_set_dt failed for led%d, error:%d", i,ret);
	            return;
                }
             }
             else{
                ret = gpio_pin_set_dt(&leds[i],0);
                if (ret < 0) {
                    printk("Error: gpio_pin_set_dt failed for led%d, error:%d", i,ret);
	            return;
                }
             }
         }
         break;
      
      case(4):
         for(int i=0; i<Num_Leds; i++){
             if(i<2){
                ret = gpio_pin_set_dt(&leds[i],0);
                if (ret < 0) {
                    printk("Error: gpio_pin_set_dt failed for led%d, error:%d", i,ret);
	            return;
                }
             }
             else{
                ret = gpio_pin_set_dt(&leds[i],i%2);
                if (ret < 0) {
                    printk("Error: gpio_pin_set_dt failed for led%d, error:%d", i,ret);
	            return;
                }
             }
         }
         break;
      
      case(5):
         for(int i=0; i<Num_Leds; i++){
             if(i<2){
                ret = gpio_pin_set_dt(&leds[i],0);
                if (ret < 0) {
                    printk("Error: gpio_pin_set_dt failed for led%d, error:%d", i,ret);
	            return;
                }
             }
             else{
                ret = gpio_pin_set_dt(&leds[i],i%3);
                if (ret < 0) {
                    printk("Error: gpio_pin_set_dt failed for led%d, error:%d", i,ret);
	            return;
                }
             }
         }
         break;
   }

}


void button0Pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    /* Activate the 1 Euro button */
   statechart_Button_raise_one_Euro(&StateMachine);
   
   return;  

}
void button1Pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    /* Activate the 2 Euros button */
   statechart_Button_raise_two_Euro(&StateMachine);
   
   return;  

}
void button2Pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    /* Activate the select button */
   statechart_Button_raise_select(&StateMachine);
   
   return;  

}
void button3Pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    /* Activate the enter button */
   statechart_Button_raise_enter(&StateMachine);
   
   return;  

}

void statechart_display( Statechart* handle, const sc_integer Type){

   switch(Type){
   	case 0:
   	    printk("\n\r"
                "############################################\n\r"
                "#                                          #\n\r"
                "#                  AMOUNT                  #\n\r"
                "#                 --------                 #\n\r"
                "#                  %3d €                   #\n\r"
                "#                                          #\n\r"
                "############################################\n",handle->internal.Cash);
            break;
        case 1:
            printk("\n\r"
                "############################################\n\r"
                "#                                          #\n\r"
                "#             Product Selection            #\n\r"
                "#                 --------                 #\n\r"
                "#               Product ->%3d              #\n\r"
                "#                Price ->%3d €             #\n\r"
                "#                                          #\n\r"
                "############################################\n",handle->internal.Product,handle->internal.Product);
            break;
       case 2:
            printk("\n\r"
                "############################################\n\r"
                "#                                          #\n\r"
                "#             Return the Credit            #\n\r"
                "#                 --------                 #\n\r"
                "#               Credit ->%3d €             #\n\r"
                "#                                          #\n\r"
                "############################################\n",handle->internal.Cash);
            break;
      case 3:
            printk("\n\r"
                "############################################\n\r"
                "#                                          #\n\r"
                "#           Product Selectioned            #\n\r"
                "#                 --------                 #\n\r"
                "#               Product ->%3d              #\n\r"
                "#                Price ->%3d €             #\n\r"
                "#              New Amount ->%3d €          #\n\r"
                "#                                          #\n\r"
                "############################################\n",handle->internal.Product,handle->internal.Product,handle->internal.Cash);
            break;
      case 4:
            printk("\n\r"
                "############################################\n\r"
                "#                                          #\n\r"
                "#     Not Enough Cash For The Product      #\n\r"
                "#     Product->%3d    Cash->%3d            #\n\r"
                "#                                          #\n\r"
                "############################################\n",handle->internal.Product,handle->internal.Cash);
            break;
      default:
      	   return;
   }
   return;
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
   
   statechart_init(&StateMachine);
   statechart_enter(&StateMachine);
   
   
   return 0;
}


