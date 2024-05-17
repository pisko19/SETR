/*
 * Paulo Pedreiras, 2024/01
 * Simple Digital Input/Output example.
 *
 * Sets LED1 according to the state of BUT1
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

/* Define the polling time, in ms */
#define SLEEP_TIME_MS 100

/* Get led0 and button0 node IDs. Refer to the DTS file */
#define LED0_NODE DT_ALIAS(led0)
#define BUT0_NODE DT_ALIAS(sw0)


/* Get the device pointer, pin number, and configuration flags for led0 and button 0. A build error on this line means your board is unsupported. */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec but = GPIO_DT_SPEC_GET(BUT0_NODE, gpios);

/*
 * The main function
 */
int main(void)
{
	int ret =0;
	int butStat=0; // Variable to code the button status
	
	/* Check if device are ready */
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

	/*
	 * The main loop
	 */
	while(1) { 
		/* Read button status and set led accordingly */
		/* Could (and should) be improved by adding e.g. debouncing */		
		butStat = gpio_pin_get_dt(&but);
		ret = gpio_pin_set_dt(&led,butStat);
		if (ret < 0) {
			return 0;
		}

		/* Sleep for a while to allow energy saving */
		k_msleep(SLEEP_TIME_MS);
	}

	return 0;
}