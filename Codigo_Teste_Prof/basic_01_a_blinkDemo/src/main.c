/*
 * Paulo Pedreiras, 2024/01
 * Simple Digital Output example, based on Nordic blinky
 *
 * Toggles periodically LED1, which is internally connected to P0.13 and labeled led0 on the devicetree
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

/* Define the sleep time, in ms (roughly half the period) */
#define SLEEP_TIME_MS 2000

/* Get led 0 node ID. Refer to the DTS file to find "led0" node label
 *   (could also be obtained via alias, see below).
 */
#define LED0_NODE DT_NODELABEL(led0)
//#define LED0_NODE DT_ALIAS(led0) /* Same action, via alias */

/* Get the device pointer, pin number, and configuration flags. A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

/*
 * The main function
 */
int main(void)
{
	int ret, ledstate=0;
	
	/* Check if device is ready */
	if (!device_is_ready(led.port))  {
		return 0;
	}

	/* Configure the GPIO pin for output ans set it to logic 0 */
	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return 0;
	}

	/*
	 * The main loop
	 */
	while(1) { 
		/* Toggle the led */
		/* Could be used instead "ret = gpio_pin_toggle_dt(&led);" (simpler-one line only) */
		ret = gpio_pin_set_dt(&led,ledstate);
		if (ret < 0) {
			return 0;
		}

		if(ledstate == 1)
			ledstate = 0;
		else
			ledstate = 1; 

		/* Sleep */
		k_msleep(SLEEP_TIME_MS);
	}

	return 0;
}