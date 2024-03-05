/** @file movavg.h
 * @brief Brief description of movavg library
 *
 * libavg library provides a few VERY BASIC functions 
 * to compute a moving average of a series of values.
 * It was built just for illustration purposes. It is not
 * Intended to be a complete and robust library.
 * 
 * @author Paulo Pedreiras
 * @date 3 March 2022
 * @bug No known bugs.
 */


#ifndef _MOVAVG_H
#define _MOVAVG_H
 
/**
 * @brief mavg_init: init function, called before use
 *
 * This function must be called before the library is used as it 
 * inits the data structures
 * Doesn't have input/output parameters
 */
void mavg_init(void); /* Init vector */     

/**
 * @brief mavg_add: adds a new value to the series
 *
 * This function adds a new value to the series
 * @param n Value to add
 * Doesn't return anything
 */
void mavg_add(int n); /* Add an element */

/**
 * @brief mavg_get: returns the current movingh average
 *
 * This funtion computes and returns the moving average of the 
 * last three elements added
 * Doesn't have input parameters
 * Returns the average
 */
float mavg_get(void); /* Get the moving average (3 elements) */  
 
#endif
