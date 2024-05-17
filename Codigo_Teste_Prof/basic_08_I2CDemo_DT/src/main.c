/*
 * Paulo Pedreiras, 2024/02
 * 
 * Shows the use of the I2C interface
 *      Interfaces with a TC74A0-3.3VAT I2C temperature sensor
 *      Operation:
 *          TC74 sensors have diverse factory-set addresses. Check the right address!!
 *          Operation is very simple: 
 *              - At first write the command Read TempeRature (RTR). This operation is 
 *                      necessary only if previously a write to config reg is done
 *              - Then read the device as many times as you want with a simple I2C read 
 *
 * See:
 *      https://github.com/NordicDeveloperAcademy/ncs-fund
 *      https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/zephyr/hardware/peripherals/i2c.html#i2c     
 * 
 *
 * Configurations/prj.conf:
 *      To enable the I2C module
 *          CONFIG_I2C=y
 *      Note that the address of the TC74 must be set via overlay file
 * 
 * PINS -  get info from devicetree (Actions tab or Config files):
 *      SDA P0.26
 *      SDA P0.27
 */

#include <zephyr/sys/printk.h>
#include <zephyr/drivers/i2c.h> /* Required for  I2C */

#define ERR_FATAL -1   /* If I2C fails ...*/

/* TC74 sensor-related defines */
    /* Address is set via overlay */
    /* CHECK THE SENSOR DATASHEET as sensors ship with DIFFERENT ADDRESSES */
    /* Do not forget to make sure that this address in set on the overlay file      */ 
    /*      as the sensor address is obtained from the DT */
#define TC74_CMD_RTR 0x00   /* Read temperature command */
#define TC74_CMD_RWCR 0x01  /* Read/write configuration register */

/* I2C device vars and defines */
#define I2C0_NID DT_NODELABEL(tc74sensor)
static const struct i2c_dt_spec dev_i2c = I2C_DT_SPEC_GET(I2C0_NID);

/* Other defines*/
#define UPDATE_PERIOD_MS 100 /* Time between temperature readings */

/* 
 * Main() function
 */
int main(void)
{
    int ret=0; /* General return variable */   
    uint8_t temp=0; /* Temperature value (raw read from sensor)*/

    printk("I2C demo - reads the temperature of a TC74 temperature sensor connected to I2C0\n\r");

    if (!device_is_ready(dev_i2c.bus)) {
	    printk("I2C bus %s is not ready!\n\r",dev_i2c.bus->name);
	    return ERR_FATAL;
    } else {
        printk("I2C bus %s, device address %x ready\n\r",dev_i2c.bus->name, dev_i2c.addr);
    }    
    
    /* Write (command RTR) to set the read address to temperature */
    /* Only necessary if a config done before (not the case), but let's stay in the safe side */
    ret = i2c_write_dt(&dev_i2c, TC74_CMD_RTR, 1);
    if(ret != 0){
        printk("Failed to write to I2C device at address %x, register %x \n\r", dev_i2c.addr ,TC74_CMD_RTR);
    }
    while(1) {
        /* Read temperature register */       
        ret = i2c_read_dt(&dev_i2c, &temp, sizeof(temp));
        if(ret != 0){
	        printk("Failed to read from I2C device at address %x, register  at Reg. %x \n\r", dev_i2c.addr,TC74_CMD_RTR);      
        }

        printk("Last temperature reading is %d \n\r",temp);

        /* Pause  */ 
        k_msleep(UPDATE_PERIOD_MS);    
    }
 
}
