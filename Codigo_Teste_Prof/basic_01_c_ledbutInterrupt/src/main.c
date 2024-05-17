/*
 * Paulo Pedreiras, 2024/01
 * Interrupt-driven simple Digital Input/Output example.
 *
 * Toggles LED1 when BUT1 is pressed, via interrupt. 
 *
 * Base documentation:
 *
 *      HW info:
 *          https://infocenter.nordicsemi.com/topic/struct_nrf52/struct/nrf52840.html
 *          Section: nRF52840 Product Specification -> Peripherals -> GPIO / GPIOTE
 *
 *          Board specific HW info can be found in the nRF52840_DK_User_Guide_20201203. I/O pins available at pg 27
 *
 *          Note that by default leds are active-low. I.e., they turn on when a logic zero is output at the corresponding port, and vice-versa.
 *          This behaviour can be reverted by adding the "GPIO_ACTIVE_LOW" flag - gpio_pin_config( ...., GPIO_OUTPUT_ACTIVE | GPIO_ACTIVE_LOW)

 *
 *      SW API info:
 *          https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/zephyr/reference/peripherals/gpio.html
 *
 *
 * 	Notes:
 * 		Note that the GPIO must be enabled in prj.conf (CONFIG_GPIO=y)
 *
 */

/* Includes. Add according to the resources used  */
#include <zephyr/kernel.h>          /* for k_msleep() */
#include <zephyr/device.h>          /* for device_is_ready() and device structure */
#include <zephyr/devicetree.h>		/* for DT_NODELABEL() */
#include <zephyr/drivers/gpio.h>    /* for GPIO api*/

/* Get led0 and button0 node IDs. Refer to the DTS file */
#define LED0_NODE DT_ALIAS(led0)
#define BUT0_NODE DT_ALIAS(sw0)

/* Get the device pointer, pin number, and configuration flags for led0 and button 0. A build error on this line means your board is unsupported. */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec but = GPIO_DT_SPEC_GET(BUT0_NODE, gpios);

/* Define the callback function */
void button0Pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    gpio_pin_toggle_dt(&led);

	return;
}

/*
 * The main function
 */
int main(void)
{
	int ret =0;
	
	static struct gpio_callback button0CbData; // Define variable for holding callback data 

	
	/* Check if devices are ready */
	if (!device_is_ready(led.port) || !device_is_ready(but.port)) {
		return 0;
	}	

	/* Configure the GPIO pins for input/output and set active logic */
	/* Note that the devicetree activates the internal pullup and sets the active low flag */
	/*   so an external resistor is not needed and pressing the button causes a logic level of 1*/
	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&but, GPIO_INPUT);
	if (ret < 0) {
		return 0;
	}

	/* Set interrupt */
	ret = gpio_pin_interrupt_configure_dt(&but, GPIO_INT_EDGE_TO_ACTIVE);
	gpio_init_callback(&button0CbData, button0Pressed, BIT(but.pin));
	
	/* Add the callback function by calling gpio_add_callback()   */
	 gpio_add_callback(but.port, &button0CbData);

	/* 
 	* No need for a while(1) at the end of the main. 
	* In Zephyr main() is a thread that can terminate without resetting the system 
	* and there is an idle() thread that is called when there are not other tasks/ints ready
	* The idle() thread activates the power saving modes, so it should be left running when possible
 	*/ 	

	return 0;
}