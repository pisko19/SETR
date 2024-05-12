/* *******************************************************************
 * Simple SW Timer manager lib
 * Paulo Pedreiras, pbrp@ua.pt, Mar 2015
 * 
 * Simple library to manage timers.
 * Tailored for use with itemisCreate C code
 * 
 * There are two native functions:
 *  	Timers_Init: should be called once, to initialzie the system. The only
 * 			arguement is the resolution is ms (integer)
 *   
 * 		Timers_Tick: is a periodic therad (period is the resolution) that is 
 * 			activated once per clock tick. When activated updtes the counters
 * 			detects expirations, generates time events and rearms the timers,
 * 			when these are periodic. 
 * 
 * Are also implemented two interface funcions, set by itemis Create:
 *  	lCSc_set_timer: called by create SM code to set a timer 
 * 		lCSc_set_timer: called by create SM code to clear/unset a timer 
 * 
 * There is also an auxiliary function to manage timspect variables:.
 * 		TsAdd: adds two timespec variables, normalizing the result 
 * 
 * Porting to a microcontroller is trivial.
 * Note only that mutexes cannot be used from within ISRs, so it is 
 * necessary to use some sort of workaround. Can be using 
 * a task, like in tis implementatio, polling the timer flag, generate 
 * a signal, ...
 * 
 * *******************************************************************/
#ifndef TIMERS_H_
#define TIMERS_H_

#include <stdint.h>
#include "Statechart.h"
#include "Statechart_required.h"

/* Some self-explanatory defines */
#define TIMERS_OK 		0 		/* Success */
#define TIMERS_INITERR	-1		/* Error in init function */

#define TIMERS_MAXTIMERS		10		/* Timers are statically allocated. Number of allowed timers. */
#define TIMERS_MS_TO_NS			1000000	/* Conversion factor between ms and ns */
#define TIMERS_SEC_TO_NS		(TIMERS_MS_TO_NS * 1000)	/* Number of ns in a second */

#define TIMERS_IN_USE_FLAG		0x00000001	/* Bit flag that signals that the timer is in use */
#define TIMERS_PERIODIC_FLAG	0x00000002	/* Bit flag that signals that the timer is periodic */

/* The basic timers data structure */
typedef struct {
	uint32_t status;		/* In use or not, periodic/one shot,  */
	uint32_t time; 			/* Current timer value */
	uint32_t period; 		/* Timer period, if periodic */
	void * event_id;		/* Event ID*/
	void * StateMachine;	/* Statemachine */
} Timers_t;

/* And the prototypes */
int32_t Timers_Init(uint32_t tmr_res_ms);	/* Timers init function */
void * Timers_Tick(void *arg); 				/* Timers tick thread */

struct  timespec  TsAdd(struct  timespec  ts1, struct  timespec  ts2); 	/* Adds timespec variables */
																		/* normalizing the result */

#endif
