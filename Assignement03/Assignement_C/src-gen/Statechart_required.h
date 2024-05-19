/** 
 * @file
 * This header file defines prototypes for all functions that are required by the state machine implementation.
 *
 * This state machine makes use of operations declared in the state machine's interface or internal scopes. Thus, the function prototypes:
 * - statechart_display
 * - statechart_setLeds
 * are defined here.
 *
 * These functions will be called during a 'run to completion step' (runCycle) of the statechart. 
 * There are some constraints that have to be considered for the implementation of these functions:
 * - never call the statechart API functions from within these functions.
 * - make sure that the execution time is as short as possible.
 */

#ifndef STATECHART_REQUIRED_H_
#define STATECHART_REQUIRED_H_

#include "../src/sc_types.h"
#include "Statechart.h"

#ifdef __cplusplus
extern "C" {
#endif 

/*! 
 * Displays information on the statechart based on the provided type.
 *
 * @param handle Pointer to the Statechart instance.
 * @param Type Type of information to be displayed.
 */
extern void statechart_display(Statechart* handle, const sc_integer Type);

/*! 
 * Sets the LEDs of the statechart based on the provided LED configuration.
 *
 * @param handle Pointer to the Statechart instance.
 * @param Leds Configuration of LEDs.
 */
extern void statechart_setLeds(Statechart* handle, const sc_integer Leds);

#ifdef __cplusplus
}
#endif 

#endif /* STATECHART_REQUIRED_H_ */

