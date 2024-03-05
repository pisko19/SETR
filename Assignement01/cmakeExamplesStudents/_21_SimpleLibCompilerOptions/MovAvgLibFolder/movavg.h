#ifndef _MOVAVG_H
#define _MOVAVG_H
 
void mavg_init(void); /* Init vector */     
void mavg_add(int n); /* Add an element */
float mavg_get(void); /* Get the moving average (3 elements) */  
 
#endif
