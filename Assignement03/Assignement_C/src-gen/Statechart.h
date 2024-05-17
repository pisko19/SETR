/** Generated by itemis CREATE code generator. */

#ifndef STATECHART_H_
#define STATECHART_H_

#ifdef __cplusplus
extern "C" { 
#endif

/*!
* Forward declaration for the Statechart state machine.
*/
typedef struct Statechart Statechart;

/*!
* Forward declaration of the data structure for the StatechartIfaceButton interface scope.
*/
typedef struct StatechartIfaceButton StatechartIfaceButton;

/*!
* Forward declaration of the data structure for the StatechartInternal interface scope.
*/
typedef struct StatechartInternal StatechartInternal;

#ifdef __cplusplus
}
#endif

#include "../src/sc_types.h"
#include <string.h>

#ifdef __cplusplus
extern "C" { 
#endif 

/*! \file
Header of the state machine 'Statechart'.
*/

#ifndef STATECHART_EVENTQUEUE_BUFFERSIZE
#define STATECHART_EVENTQUEUE_BUFFERSIZE 20
#endif
#ifndef STATECHART_IN_EVENTQUEUE_BUFFERSIZE
#define STATECHART_IN_EVENTQUEUE_BUFFERSIZE STATECHART_EVENTQUEUE_BUFFERSIZE
#endif
#ifndef SC_INVALID_EVENT_VALUE
#define SC_INVALID_EVENT_VALUE 0
#endif
/*! Define number of states in the state enum */
#define STATECHART_STATE_COUNT 7

/*! Define dimension of the state configuration vector for orthogonal states. */
#define STATECHART_MAX_ORTHOGONAL_STATES 1

/*! Define indices of states in the StateConfVector */
#define SCVI_STATECHART_MAIN_REGION_MONEY 0
#define SCVI_STATECHART_MAIN_REGION_INIT 0
#define SCVI_STATECHART_MAIN_REGION_SELECTION 0
#define SCVI_STATECHART_MAIN_REGION_RETURN_CREDIT 0
#define SCVI_STATECHART_MAIN_REGION_RETURN_PRODUCT 0
#define SCVI_STATECHART_MAIN_REGION_RETURN_PRODUCT_CALCULATE_THE_NEW_CASH_VALUE_DISPLAY_ERROR 0
#define SCVI_STATECHART_MAIN_REGION_RETURN_PRODUCT_CALCULATE_THE_NEW_CASH_VALUE_DISPLAY_NORMAL 0


/* 
 * Enum of event names in the statechart.
 */
typedef enum  {
	Statechart_invalid_event = SC_INVALID_EVENT_VALUE,
	Statechart_Button_One_Euro,
	Statechart_Button_Two_Euro,
	Statechart_Button_Select,
	Statechart_Button_Enter
} StatechartEventID;

/*
 * Struct that represents a single event.
 */
typedef struct {
	StatechartEventID name;
} statechart_event;

/*
 * Queue that holds the raised events.
 */
typedef struct statechart_eventqueue_s {
	statechart_event *events;
	sc_integer capacity;
	sc_integer pop_index;
	sc_integer push_index;
	sc_integer size;
} statechart_eventqueue;

/*! Enumeration of all states */ 
typedef enum
{
	Statechart_last_state,
	Statechart_main_region_Money,
	Statechart_main_region_INIT,
	Statechart_main_region_Selection,
	Statechart_main_region_Return_Credit,
	Statechart_main_region_Return_Product,
	Statechart_main_region_Return_Product_Calculate_the_new_cash_value_Display_Error,
	Statechart_main_region_Return_Product_Calculate_the_new_cash_value_Display_Normal
} StatechartStates;


/*! Type declaration of the data structure for the StatechartIfaceButton interface scope. */
struct StatechartIfaceButton
{
	sc_boolean One_Euro_raised;
	sc_boolean Two_Euro_raised;
	sc_boolean Select_raised;
	sc_boolean Enter_raised;
};



/*! Type declaration of the data structure for the StatechartInternal interface scope. */
struct StatechartInternal
{
	sc_integer Cash;
	sc_integer Product;
};








/*! 
 * Type declaration of the data structure for the Statechart state machine.
 * This data structure has to be allocated by the client code. 
 */
struct Statechart
{
	StatechartStates stateConfVector[STATECHART_MAX_ORTHOGONAL_STATES];
	StatechartIfaceButton ifaceButton;
	StatechartInternal internal;
	sc_boolean completed;
	sc_boolean doCompletion;
	sc_boolean isExecuting;
	statechart_eventqueue in_event_queue;
	statechart_event in_buffer[STATECHART_IN_EVENTQUEUE_BUFFERSIZE];
};



/*! Initializes the Statechart state machine data structures. Must be called before first usage.*/
extern void statechart_init(Statechart* handle);


/*! Activates the state machine. */
extern void statechart_enter(Statechart* handle);

/*! Deactivates the state machine. */
extern void statechart_exit(Statechart* handle);

/*! 
Can be used by the client code to trigger a run to completion step without raising an event.
*/
extern void statechart_trigger_without_event(Statechart* handle);



/*! Raises the in event 'One_Euro' that is defined in the interface scope 'Button'. */ 
extern void statechart_Button_raise_one_Euro(Statechart* handle);
/*! Raises the in event 'Two_Euro' that is defined in the interface scope 'Button'. */ 
extern void statechart_Button_raise_two_Euro(Statechart* handle);
/*! Raises the in event 'Select' that is defined in the interface scope 'Button'. */ 
extern void statechart_Button_raise_select(Statechart* handle);
/*! Raises the in event 'Enter' that is defined in the interface scope 'Button'. */ 
extern void statechart_Button_raise_enter(Statechart* handle);

/*!
 * Checks whether the state machine is active (until 2.4.1 this method was used for states).
 * A state machine is active if it was entered. It is inactive if it has not been entered at all or if it has been exited.
 */
extern sc_boolean statechart_is_active(const Statechart* handle);

/*!
 * Checks if all active states are final. 
 * If there are no active states then the state machine is considered being inactive. In this case this method returns false.
 */
extern sc_boolean statechart_is_final(const Statechart* handle);

/*! Checks if the specified state is active (until 2.4.1 the used method for states was called isActive()). */
extern sc_boolean statechart_is_state_active(const Statechart* handle, StatechartStates state);


#ifdef __cplusplus
}
#endif 

#endif /* STATECHART_H_ */
