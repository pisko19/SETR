/*
 * Paulo Pedreiras, 2024/02
 * Simple ADC example - nRF52840DK_nRF52840 board
 * 
 * 
 * Periodically reads an ADC input and prints the corresponding raw and voltage value in the console
 * 
 * Adapted from: 
 *            https://devzone.nordicsemi.com/f/nordic-q-a/80685/using-saadc-in-nrf-connect-sdk/334204#334204
 *            https://github.com/simon-iversen/sdk-nrf/blob/light_controller/samples/light_controller/src/main.c
 * 
 *
 *      HW info
 *          https://infocenter.nordicsemi.com/topic/struct_nrf52/struct/nrf52840.html
 *          Section: nRF52840 Product Specification -> Peripherals -> GPIO / GPIOTE and SAADC 
 *          Board specific HW info can be found in the nRF52840_DK_User_Guide_20201203. I/O pins available at pg 27
 *
 *      Peripheral libs
 *          https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/zephyr/reference/peripherals/index.html
 *          Section ADC     
 *
 *      NOTE 1:     **** NEVER APPLY MORE THAN 3 V (VDD) or negative voltages to ANx ****
 *
 *      NOTE 2:     In this board analog inputs are AIN{1,2,4,5,6,7} (see nRF52840_DK_User_Guide_20201203, page 28)
 *                  Some of the examples found in the internet are set to AIN0 and so do not work. 
 *                  The PCB also has a label "A0", which refers to Arduino and induces in error. 
 *    
 *      NOTE 3:     must add "CONFIG_ADC=y" to prj.conf
 *                  DT overlay added to enable ADC. Required if the ADC status is not OK on the board DTS.
 * 
 */

/* Includes. Add according to the resources used  */
#include <zephyr/kernel.h>          /* for k_msleep() */
#include <zephyr/device.h>          /* for device_is_ready() and device structure */
#include <zephyr/devicetree.h>	    /* for DT_NODELABEL() */
#include <zephyr/drivers/gpio.h>    /* for GPIO API*/
#include <zephyr/drivers/adc.h>     /* for ADC API*/
#include <zephyr/sys/printk.h>      /* for printk()*/
#include <string.h>

/*ADC definitions and includes*/
#include <hal/nrf_saadc.h>
#define ADC_RESOLUTION 10
#define ADC_GAIN ADC_GAIN_1_4
#define ADC_REFERENCE ADC_REF_VDD_1_4
#define ADC_ACQUISITION_TIME ADC_ACQ_TIME(ADC_ACQ_TIME_MICROSECONDS, 40)
#define ADC_CHANNEL_ID 1  

/* This is the actual nRF ANx input to use. Note that a channel can be assigned to any ANx. In fact a channel can */
/*    be assigned to two ANx, when differential reading is set (one ANx for the positive signal and the other one for the negative signal) */  
/* Note also that the configuration of different channels is completely independent (gain, resolution, ref voltage, ...) */
#define ADC_CHANNEL_INPUT NRF_SAADC_INPUT_AIN1 

#define BUFFER_SIZE 1

#define ADC_NODE DT_NODELABEL(adc)  
const struct device *adc_dev = DEVICE_DT_GET(ADC_NODE);	

/* Other defines */
#define TIMER_INTERVAL_MSEC 1000 /* Interval between ADC samples */

/* ADC channel configuration */
static const struct adc_channel_cfg my_channel_cfg = {
	.gain = ADC_GAIN,
	.reference = ADC_REFERENCE,
	.acquisition_time = ADC_ACQUISITION_TIME,
	.channel_id = ADC_CHANNEL_ID,
	.input_positive = ADC_CHANNEL_INPUT
};

/* Error codes */
#define ERR_OK 0        // All fine
#define ERR_CONFIG -1   // Fail at set-up


/* Global vars */
struct k_timer my_timer;
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


int main(void)
{
    int err=0;
   
    /* Welcome message */
    printk("\n\r Simple adc demo for  \n\r");
    printk(" Reads an analog input connected to AN%d and prints its raw and mV value \n\r", ADC_CHANNEL_ID);
    printk(" *** ASSURE THAT ANx IS BETWEEN [0...3V]\n\r");
         
   
   /* Set-up ADC channel */
    err = adc_channel_setup(adc_dev, &my_channel_cfg);
    if (err) {
        printk("adc_channel_setup() failed with error code %d\n", err);
        return ERR_CONFIG;
    }
    
    /* It is recommended to calibrate the SAADC at least once before use, and whenever the ambient temperature has changed by more than 10 °C */
    NRF_SAADC->TASKS_CALIBRATEOFFSET = 1;
    
    /* Main loop */
    while(true){
        /* Get one sample, checks for errors and prints the values */
        err=adc_sample();
        if(err) {
            printk("adc_sample() failed with error code %d\n\r",err);
        }
        else {
            if(adc_sample_buffer[0] > 1023) {
                printk("adc reading out of range (value is %u)\n\r", adc_sample_buffer[0]);
            }
            else {
                /* ADC is set to use gain of 1/4 and reference VDD/4, so input range is 0...VDD (3 V), with 10 bit resolution */
                printk("adc reading: raw:%4u / %4u mV: \n\r",adc_sample_buffer[0],(uint16_t)(1000*adc_sample_buffer[0]*((float)3/1023)));
            }
        }

        /* Sleep a while ... */
        k_msleep(TIMER_INTERVAL_MSEC);
    }

    /* Should never reach this place ...*/
    return ERR_OK;
}
