/*
 * Paulo Pedreiras, 2024/01
 * 
 * Simple SW module example
 * 
 * Ilustrates a simple way of organizing SW modules in CMake / Zephyr *      
 *  Note that the standard CMakesLists.txt must be updated as follows (lines with "#Add ... " as comment)    
 *
 *          ...
 *          project(ModularSWDemo)
 *          ...
 *          target_include_directories(app PRIVATE src/MyMath) #Add path to .h file(s)
 *          target_sources(app PRIVATE src/MyMath/MyMath.c) #Add path to .c source files
 *          
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
#include "MyMath.h"

#define STEPTIME_MS 500 /* Time between calls to MyAdd (in ms) */ 

/* Main function */
int main(void) {

    /* Variables */
    int x=0,y=10,res=0;

    /* Task init code */
    printk("Example if the use of SW modules  \n");
    printk("Call to MyAdd(x,y) in MyMath module\n\r"); 

    /* Blink loop */
    while(1) {  
        res=MyAdd(x++,y++);
        printk("MyAdd(%d,%d)=%d \n\r",x,y,res);

        /* Pause  */ 
        k_msleep(STEPTIME_MS);      
   }
    
    return 0;
} 