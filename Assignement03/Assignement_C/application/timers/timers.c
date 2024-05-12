/* *******************************************************************
 * Simple SW Timer manager lib
 * Paulo Pedreiras, pbrp@ua.pt, Mar 2015
 * 
 * Simple library to manage timers.
 * Tailored for use with itemisCreate C code
 * 
 * See .h file for additional details 
 *  
 * *******************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "timers.h"
#include "debugprint.h"

static pthread_mutex_t lock; /* Lock for serialization of access to timers data */
	
static Timers_t timers[TIMERS_MAXTIMERS];
static pthread_t timersThreadId;

static uint32_t timers_resolution_ms;	/* Timer resolution is ms (i.e. the tick period) */


int32_t Timers_Init(uint32_t tmr_res_ms){
	int i, err;
	
	/* Set timer system resolution */
	timers_resolution_ms = tmr_res_ms;
	
	/* Initialize timers array */
	for(i=0; i<TIMERS_MAXTIMERS; i++) {
		timers[i].status = 0;
		timers[i].period = 0;
		timers[i].time=0;
	}
			
	/* Create timer tick thread */
	err=pthread_create(&timersThreadId, NULL, Timers_Tick, NULL);
 	if(err != 0) {
		perror("Error creating Timers_Tick Thread");
		return TIMERS_INITERR;
	}
	
	/* Create mutext */
	if (pthread_mutex_init(&lock, NULL) != 0) { 
        perror("Mutex init failed"); 
        return TIMERS_INITERR; 
    } 
    
    DBGPRINT("TIMERS: Init function OK\n");
	
	return TIMERS_OK;	
}		

void * Timers_Tick(void *arg){
	uint16_t i; 	/* Generic counter */
	
	/* Timespec variables to manage time */
	struct timespec ts, // Thread next activation time (absolute)			
			tp; 		// Thread period
		 
	/* Set absolute activation time of first instance */
	tp.tv_nsec = timers_resolution_ms * TIMERS_MS_TO_NS; 
	tp.tv_sec = 0;	
	clock_gettime(CLOCK_MONOTONIC, &ts);
	ts = TsAdd(ts,tp);	
		
	/* Periodic jobs ...*/ 
	while(1) {

		/* Wait until next cycle */
		clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME,&ts,NULL);		
		
		/* Compute next activation time */
		ts = TsAdd(ts,tp);		
		
		/* Get exclusive access to timers data */
		pthread_mutex_lock(&lock);
        
		/* Go through the list of timers and process eventual events*/ 
		for(i=0; i<TIMERS_MAXTIMERS; i++) {
			if(timers[i].status & TIMERS_IN_USE_FLAG) {		/* If timer active/in use */
				//printf("Timer %d in use\n",i);
				timers[i].time --;
				if(timers[i].time == 0) { /* If end of count reached */
					DBGPRINT("TIMERS: Timer %d expired - event raise_time_event generated\n",i);
					statechart_raise_time_event(timers[i].StateMachine, timers[i].event_id);					
					
					if(timers[i].status & TIMERS_PERIODIC_FLAG) { /* If periodic, set counter to rearm */
						timers[i].time = timers[i].period;
						DBGPRINT("TIMERS: Periodic timer - rearmed\n");
					} else {
						timers[i].status &= (!TIMERS_IN_USE_FLAG);	/* If single-shot, make it inactive */
						DBGPRINT("TIMERS: Single shot timer - stopped\n");
					}					
				}
			} else {
				//printf("Timer %d not in use\n",i);
			}
		}
		
		/* Release access to timers data */
		pthread_mutex_unlock(&lock);	
	}  
	
  
    return NULL;
}		

// Adds two timespect variables
struct  timespec  TsAdd(struct  timespec  ts1, struct  timespec  ts2){
	
    struct  timespec  tr;
	
	// Add the two timespec variables
   	tr.tv_sec = ts1.tv_sec + ts2.tv_sec ;
   	tr.tv_nsec = ts1.tv_nsec + ts2.tv_nsec ;
	// Check for nsec overflow	
	if (tr.tv_nsec >= TIMERS_SEC_TO_NS) {
		tr.tv_sec++ ;
		tr.tv_nsec = tr.tv_nsec - TIMERS_SEC_TO_NS ;
	}

    return (tr) ;
}


void statechart_set_timer(Statechart* handle, const sc_eventid evid, const sc_time time_ms, const sc_boolean periodic){
	int32_t i;
	
	/* Get exclusive access to timers data */
	pthread_mutex_lock(&lock);
	
	/* Try to get a free timers and set it */
	for(i=0; i<TIMERS_MAXTIMERS; i++) {
		if(!(timers[i].status & TIMERS_IN_USE_FLAG)) {		/* If timer not active/in use */
			DBGPRINT("TIMERS: Creating timer at position %d\n",i);
			timers[i].status = 0;
			timers[i].status |= TIMERS_IN_USE_FLAG;
			if(periodic) {
				timers[i].status |= TIMERS_PERIODIC_FLAG;
			}
			timers[i].StateMachine = handle;
			timers[i].event_id = evid;
			timers[i].period = time_ms / timers_resolution_ms;
			timers[i].time = timers[i].period;			
			
			break;
		}
	}
	
	/* Release exclusive access to timers data */
	pthread_mutex_unlock(&lock);
	return;
}		

void statechart_unset_timer(Statechart* handle, const sc_eventid evid){
	int32_t i;
	
	/* Get exclusive access to timers data */
	pthread_mutex_lock(&lock);
	
	/* Locate timer and mark it as inactive */
	for(i=0; i<TIMERS_MAXTIMERS; i++) {
		if(timers[i].status & TIMERS_IN_USE_FLAG) {		/* If timer active/in use */
			if( (timers[i].StateMachine == handle) && (timers[i].event_id == evid) ) {
				timers[i].status = 0;			
				DBGPRINT("TIMERS: unset timer: timer %d removed \n",i);
				break;
			}
		}
	}
	
	/* Release exclusive access to timers data */
	pthread_mutex_unlock(&lock);
	
	return;
}		


