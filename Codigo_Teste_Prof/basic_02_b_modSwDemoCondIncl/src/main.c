/*
 * Paulo Pedreiras, 2024/01
 * 
 * Simple SW module example, with optional inclusion 
 * 
 * Ilustrates a simple way of organizing SW modules in CMake / Zephyr *      
 * Note that the standard CMakesLists.txt must be updated as follows (lines with "#Add ... " as comment)    
 *
 *          ...
 *          project(ModularSWDemo)
 *          ...
 *          target_include_directories_ifdef(CONFIG_MYMATH app PRIVATE src/MyMath) #Add this line
 *          target_sources_ifdef(CONFIG_MYMATH app PRIVATE src/MyMath/MyMath.c) #Add module c source
 *
 *      Moreover, a Kconfig file must be created with the following contents         
 *          source "Kconfig.zephyr"
 *          config MYMATH
 *              bool "Enable MyMath lib"
 *              default n
 * 
 * Then have to enable it in prj.conf or via Kconfig GUI
*            CONFIG_MYMATH=y
 * 
 * Output via printk(). 
 * Use a terminal (nRF terminal, minicom, Putty) to check the messages.
 * Configuration is /dev/ttyACM0 (com?? on Windows), {115200,8,N,1}, no flow control
 * 
 * Note: SW module inclusion can be controlled by the prj.conf. This way only used
 *          modules are included, thereby reduncing the app footprint.
 *  
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>      /* for printk()*/

#ifdef CONFIG_MYMATH
#include "MyMath.h"
#endif

#define STEPTIME_MS 500 /* Time between calls to MyAdd (in ms) */ 

/* Main function */
int main(void) {

    /* Variables */
    int x=0,y=10,res=0;

    /* Task init code */
    printk("Example of the use of SW modules with optional inclusion \n");
    
    #ifdef CONFIG_MYMATH
    printk("Call to MyAdd(x,y) in MyMath module\n\r"); 
    #else
    printk("Call to MyAdd(x,y) not done as module is not included\n\r"); 
    #endif

    /* Blink loop */
    while(1) {  
        #ifdef CONFIG_MYMATH
        res=MyAdd(x++,y++);
        printk("MyAdd(%d,%d)=%d \n\r",x,y,res);
        #else
        printk("MyAdd() not included");
        #endif

        /* Pause  */ 
        k_msleep(STEPTIME_MS);      
   }
    
    return 0;
} 