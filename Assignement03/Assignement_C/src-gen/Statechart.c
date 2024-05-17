/** Generated by itemis CREATE code generator. */


#include "../src/sc_types.h"

#include "Statechart.h"
#include "Statechart_required.h"

/*! \file
Implementation of the state machine 'Statechart'
*/

#ifndef SC_UNUSED
#define SC_UNUSED(P) (void)(P)
#endif

/* prototypes of all internal functions */
static void effect_main_region_Return_Product_tr0(Statechart* handle);
static void enact_main_region_Money(Statechart* handle);
static void enact_main_region_INIT(Statechart* handle);
static void enact_main_region_Selection(Statechart* handle);
static void enact_main_region_Return_Credit(Statechart* handle);
static void enact_main_region_Return_Product_Calculate_the_new_cash_value_Display_Error(Statechart* handle);
static void enact_main_region_Return_Product_Calculate_the_new_cash_value_Display_Normal(Statechart* handle);
static void exact_main_region_INIT(Statechart* handle);
static void enseq_main_region_Money_default(Statechart* handle);
static void enseq_main_region_INIT_default(Statechart* handle);
static void enseq_main_region_Selection_default(Statechart* handle);
static void enseq_main_region_Return_Credit_default(Statechart* handle);
static void enseq_main_region_Return_Product_default(Statechart* handle);
static void enseq_main_region_Return_Product_Calculate_the_new_cash_value_Display_Error_default(Statechart* handle);
static void enseq_main_region_Return_Product_Calculate_the_new_cash_value_Display_Normal_default(Statechart* handle);
static void enseq_main_region_default(Statechart* handle);
static void enseq_main_region_Return_Product_Calculate_the_new_cash_value_default(Statechart* handle);
static void exseq_main_region_Money(Statechart* handle);
static void exseq_main_region_INIT(Statechart* handle);
static void exseq_main_region_Selection(Statechart* handle);
static void exseq_main_region_Return_Credit(Statechart* handle);
static void exseq_main_region_Return_Product(Statechart* handle);
static void exseq_main_region_Return_Product_Calculate_the_new_cash_value_Display_Error(Statechart* handle);
static void exseq_main_region_Return_Product_Calculate_the_new_cash_value_Display_Normal(Statechart* handle);
static void exseq_main_region(Statechart* handle);
static void exseq_main_region_Return_Product_Calculate_the_new_cash_value(Statechart* handle);
static void react_main_region__choice_0(Statechart* handle);
static void react_main_region__choice_1(Statechart* handle);
static void react_main_region_Return_Product_Calculate_the_new_cash_value__choice_0(Statechart* handle);
static void react_main_region__entry_Default(Statechart* handle);
static void react_main_region_Return_Product_Calculate_the_new_cash_value__entry_Default(Statechart* handle);

/*! State machine reactions. */
static sc_integer react(Statechart* handle, const sc_integer transitioned_before);

/*! The reactions of state Money. */
static sc_integer main_region_Money_react(Statechart* handle, const sc_integer transitioned_before);

/*! The reactions of state INIT. */
static sc_integer main_region_INIT_react(Statechart* handle, const sc_integer transitioned_before);

/*! The reactions of state Selection. */
static sc_integer main_region_Selection_react(Statechart* handle, const sc_integer transitioned_before);

/*! The reactions of state Return Credit. */
static sc_integer main_region_Return_Credit_react(Statechart* handle, const sc_integer transitioned_before);

/*! The reactions of state Return Product. */
static sc_integer main_region_Return_Product_react(Statechart* handle, const sc_integer transitioned_before);

/*! The reactions of state Display Error. */
static sc_integer main_region_Return_Product_Calculate_the_new_cash_value_Display_Error_react(Statechart* handle, const sc_integer transitioned_before);

/*! The reactions of state Display Normal. */
static sc_integer main_region_Return_Product_Calculate_the_new_cash_value_Display_Normal_react(Statechart* handle, const sc_integer transitioned_before);


static void clear_in_events(Statechart* handle);

static void micro_step(Statechart* handle);

/*! Performs a 'run to completion' step. */
static void run_cycle(Statechart* handle);




static void statechart_internal_set_cash(Statechart* handle, sc_integer value)
;
static void statechart_internal_set_product(Statechart* handle, sc_integer value)
;


static void statechart_eventqueue_init(statechart_eventqueue * eq, statechart_event *buffer, sc_integer capacity);
static sc_integer statechart_eventqueue_size(statechart_eventqueue * eq);
static void statechart_event_init(statechart_event * ev, StatechartEventID name);
static statechart_event statechart_eventqueue_pop(statechart_eventqueue * eq);
static sc_boolean statechart_eventqueue_push(statechart_eventqueue * eq, statechart_event ev);
static void statechart_add_event_to_queue(statechart_eventqueue * eq, StatechartEventID name);
static sc_boolean statechart_dispatch_event(Statechart* handle, const statechart_event * event);
static statechart_event statechart_get_next_event(Statechart* handle);
static sc_boolean statechart_dispatch_next_event(Statechart* handle);


void statechart_init(Statechart* handle)
{
	sc_integer i;
	
	for (i = 0; i < STATECHART_MAX_ORTHOGONAL_STATES; ++i)
	{
		handle->stateConfVector[i] = Statechart_last_state;
	}
	
				
	clear_in_events(handle);
	
	
	/* Default init sequence for statechart Statechart */
	statechart_internal_set_cash(handle, 0);
	statechart_internal_set_product(handle, 0);
	
	handle->isExecuting = bool_false;
	statechart_eventqueue_init(&handle->in_event_queue, handle->in_buffer, STATECHART_IN_EVENTQUEUE_BUFFERSIZE);
}

void statechart_enter(Statechart* handle)
{
	/* Activates the state machine. */
	if (handle->isExecuting == bool_true)
	{ 
		return;
	} 
	handle->isExecuting = bool_true;
	/* Default enter sequence for statechart Statechart */
	enseq_main_region_default(handle);
	handle->doCompletion = bool_false;
	do
	{ 
		if (handle->completed == bool_true)
		{ 
			handle->doCompletion = bool_true;
		} 
		handle->completed = bool_false;
		micro_step(handle);
		handle->doCompletion = bool_false;
	} while (handle->completed == bool_true);
	handle->isExecuting = bool_false;
}

void statechart_exit(Statechart* handle)
{
	/* Deactivates the state machine. */
	if (handle->isExecuting == bool_true)
	{ 
		return;
	} 
	handle->isExecuting = bool_true;
	/* Default exit sequence for statechart Statechart */
	exseq_main_region(handle);
	handle->isExecuting = bool_false;
}

/*!
Can be used by the client code to trigger a run to completion step without raising an event.
*/
void statechart_trigger_without_event(Statechart* handle) {
	run_cycle(handle);
}


sc_boolean statechart_is_active(const Statechart* handle)
{
	sc_boolean result = bool_false;
	sc_integer i;
	
	for(i = 0; i < STATECHART_MAX_ORTHOGONAL_STATES; i++)
	{
		result = result || handle->stateConfVector[i] != Statechart_last_state;
	}
	
	return result;
}

/* 
 * Always returns 'false' since this state machine can never become final.
 */
sc_boolean statechart_is_final(const Statechart* handle)
{
	SC_UNUSED(handle);
	return bool_false;
}

sc_boolean statechart_is_state_active(const Statechart* handle, StatechartStates state)
{
	sc_boolean result = bool_false;
	switch (state)
	{
		case Statechart_main_region_Money :
			result = (sc_boolean) (handle->stateConfVector[SCVI_STATECHART_MAIN_REGION_MONEY] == Statechart_main_region_Money
			);
				break;
		case Statechart_main_region_INIT :
			result = (sc_boolean) (handle->stateConfVector[SCVI_STATECHART_MAIN_REGION_INIT] == Statechart_main_region_INIT
			);
				break;
		case Statechart_main_region_Selection :
			result = (sc_boolean) (handle->stateConfVector[SCVI_STATECHART_MAIN_REGION_SELECTION] == Statechart_main_region_Selection
			);
				break;
		case Statechart_main_region_Return_Credit :
			result = (sc_boolean) (handle->stateConfVector[SCVI_STATECHART_MAIN_REGION_RETURN_CREDIT] == Statechart_main_region_Return_Credit
			);
				break;
		case Statechart_main_region_Return_Product :
			result = (sc_boolean) (handle->stateConfVector[SCVI_STATECHART_MAIN_REGION_RETURN_PRODUCT] >= Statechart_main_region_Return_Product
				&& handle->stateConfVector[SCVI_STATECHART_MAIN_REGION_RETURN_PRODUCT] <= Statechart_main_region_Return_Product_Calculate_the_new_cash_value_Display_Normal);
				break;
		case Statechart_main_region_Return_Product_Calculate_the_new_cash_value_Display_Error :
			result = (sc_boolean) (handle->stateConfVector[SCVI_STATECHART_MAIN_REGION_RETURN_PRODUCT_CALCULATE_THE_NEW_CASH_VALUE_DISPLAY_ERROR] == Statechart_main_region_Return_Product_Calculate_the_new_cash_value_Display_Error
			);
				break;
		case Statechart_main_region_Return_Product_Calculate_the_new_cash_value_Display_Normal :
			result = (sc_boolean) (handle->stateConfVector[SCVI_STATECHART_MAIN_REGION_RETURN_PRODUCT_CALCULATE_THE_NEW_CASH_VALUE_DISPLAY_NORMAL] == Statechart_main_region_Return_Product_Calculate_the_new_cash_value_Display_Normal
			);
				break;
			default:
				result = bool_false;
				break;
		}
		return result;
	}

static void clear_in_events(Statechart* handle)
{
	handle->ifaceButton.One_Euro_raised = bool_false;
	handle->ifaceButton.Two_Euro_raised = bool_false;
	handle->ifaceButton.Select_raised = bool_false;
	handle->ifaceButton.Enter_raised = bool_false;
}

static void micro_step(Statechart* handle)
{
	switch(handle->stateConfVector[ 0 ])
	{
		case Statechart_main_region_Money :
		{
			main_region_Money_react(handle,-1);
			break;
		}
		case Statechart_main_region_INIT :
		{
			main_region_INIT_react(handle,-1);
			break;
		}
		case Statechart_main_region_Selection :
		{
			main_region_Selection_react(handle,-1);
			break;
		}
		case Statechart_main_region_Return_Credit :
		{
			main_region_Return_Credit_react(handle,-1);
			break;
		}
		case Statechart_main_region_Return_Product_Calculate_the_new_cash_value_Display_Error :
		{
			main_region_Return_Product_Calculate_the_new_cash_value_Display_Error_react(handle,-1);
			break;
		}
		case Statechart_main_region_Return_Product_Calculate_the_new_cash_value_Display_Normal :
		{
			main_region_Return_Product_Calculate_the_new_cash_value_Display_Normal_react(handle,-1);
			break;
		}
		default: 
			/* do nothing */
			break;
	}
}

static void run_cycle(Statechart* handle)
{
	/* Performs a 'run to completion' step. */
	if (handle->isExecuting == bool_true)
	{ 
		return;
	} 
	handle->isExecuting = bool_true;
	statechart_dispatch_next_event(handle);
	do
	{ 
		handle->doCompletion = bool_false;
		do
		{ 
			if (handle->completed == bool_true)
			{ 
				handle->doCompletion = bool_true;
			} 
			handle->completed = bool_false;
			micro_step(handle);
			handle->doCompletion = bool_false;
		} while (handle->completed == bool_true);
		clear_in_events(handle);
	} while (statechart_dispatch_next_event(handle) == bool_true);
	handle->isExecuting = bool_false;
}


void statechart_Button_raise_one_Euro(Statechart* handle)
{
	statechart_add_event_to_queue(&(handle->in_event_queue), Statechart_Button_One_Euro);
	run_cycle(handle);
}

void statechart_Button_raise_two_Euro(Statechart* handle)
{
	statechart_add_event_to_queue(&(handle->in_event_queue), Statechart_Button_Two_Euro);
	run_cycle(handle);
}

void statechart_Button_raise_select(Statechart* handle)
{
	statechart_add_event_to_queue(&(handle->in_event_queue), Statechart_Button_Select);
	run_cycle(handle);
}

void statechart_Button_raise_enter(Statechart* handle)
{
	statechart_add_event_to_queue(&(handle->in_event_queue), Statechart_Button_Enter);
	run_cycle(handle);
}






static void statechart_internal_set_cash(Statechart* handle, sc_integer value)
{
	handle->internal.Cash = value;
}
static void statechart_internal_set_product(Statechart* handle, sc_integer value)
{
	handle->internal.Product = value;
}


/* implementations of all internal functions */

static void effect_main_region_Return_Product_tr0(Statechart* handle)
{
	exseq_main_region_Return_Product(handle);
	react_main_region__choice_1(handle);
}

/* Entry action for state 'Money'. */
static void enact_main_region_Money(Statechart* handle)
{
	/* Entry action for state 'Money'. */
	statechart_display(handle,0);
}

/* Entry action for state 'INIT'. */
static void enact_main_region_INIT(Statechart* handle)
{
	/* Entry action for state 'INIT'. */
	statechart_internal_set_cash(handle, 0);
	statechart_internal_set_product(handle, 0);
}

/* Entry action for state 'Selection'. */
static void enact_main_region_Selection(Statechart* handle)
{
	/* Entry action for state 'Selection'. */
	statechart_display(handle,1);
}

static void enact_main_region_Return_Credit(Statechart* handle)
{
	/* Entry action for state 'Return Credit'. */
	statechart_display(handle,2);
	handle->completed = bool_true;
}

static void enact_main_region_Return_Product_Calculate_the_new_cash_value_Display_Error(Statechart* handle)
{
	/* Entry action for state 'Display Error'. */
	statechart_display(handle,4);
	handle->completed = bool_true;
}

static void enact_main_region_Return_Product_Calculate_the_new_cash_value_Display_Normal(Statechart* handle)
{
	/* Entry action for state 'Display Normal'. */
	statechart_display(handle,3);
	handle->completed = bool_true;
}

/* Exit action for state 'INIT'. */
static void exact_main_region_INIT(Statechart* handle)
{
	/* Exit action for state 'INIT'. */
	statechart_display(handle,0);
}

/* 'default' enter sequence for state Money */
static void enseq_main_region_Money_default(Statechart* handle)
{
	/* 'default' enter sequence for state Money */
	enact_main_region_Money(handle);
	handle->stateConfVector[0] = Statechart_main_region_Money;
}

/* 'default' enter sequence for state INIT */
static void enseq_main_region_INIT_default(Statechart* handle)
{
	/* 'default' enter sequence for state INIT */
	enact_main_region_INIT(handle);
	handle->stateConfVector[0] = Statechart_main_region_INIT;
}

/* 'default' enter sequence for state Selection */
static void enseq_main_region_Selection_default(Statechart* handle)
{
	/* 'default' enter sequence for state Selection */
	enact_main_region_Selection(handle);
	handle->stateConfVector[0] = Statechart_main_region_Selection;
}

/* 'default' enter sequence for state Return Credit */
static void enseq_main_region_Return_Credit_default(Statechart* handle)
{
	/* 'default' enter sequence for state Return Credit */
	enact_main_region_Return_Credit(handle);
	handle->stateConfVector[0] = Statechart_main_region_Return_Credit;
}

/* 'default' enter sequence for state Return Product */
static void enseq_main_region_Return_Product_default(Statechart* handle)
{
	/* 'default' enter sequence for state Return Product */
	enseq_main_region_Return_Product_Calculate_the_new_cash_value_default(handle);
}

/* 'default' enter sequence for state Display Error */
static void enseq_main_region_Return_Product_Calculate_the_new_cash_value_Display_Error_default(Statechart* handle)
{
	/* 'default' enter sequence for state Display Error */
	enact_main_region_Return_Product_Calculate_the_new_cash_value_Display_Error(handle);
	handle->stateConfVector[0] = Statechart_main_region_Return_Product_Calculate_the_new_cash_value_Display_Error;
}

/* 'default' enter sequence for state Display Normal */
static void enseq_main_region_Return_Product_Calculate_the_new_cash_value_Display_Normal_default(Statechart* handle)
{
	/* 'default' enter sequence for state Display Normal */
	enact_main_region_Return_Product_Calculate_the_new_cash_value_Display_Normal(handle);
	handle->stateConfVector[0] = Statechart_main_region_Return_Product_Calculate_the_new_cash_value_Display_Normal;
}

/* 'default' enter sequence for region main region */
static void enseq_main_region_default(Statechart* handle)
{
	/* 'default' enter sequence for region main region */
	react_main_region__entry_Default(handle);
}

/* 'default' enter sequence for region Calculate the new cash value */
static void enseq_main_region_Return_Product_Calculate_the_new_cash_value_default(Statechart* handle)
{
	/* 'default' enter sequence for region Calculate the new cash value */
	react_main_region_Return_Product_Calculate_the_new_cash_value__entry_Default(handle);
}

/* Default exit sequence for state Money */
static void exseq_main_region_Money(Statechart* handle)
{
	/* Default exit sequence for state Money */
	handle->stateConfVector[0] = Statechart_last_state;
}

/* Default exit sequence for state INIT */
static void exseq_main_region_INIT(Statechart* handle)
{
	/* Default exit sequence for state INIT */
	handle->stateConfVector[0] = Statechart_last_state;
	exact_main_region_INIT(handle);
}

/* Default exit sequence for state Selection */
static void exseq_main_region_Selection(Statechart* handle)
{
	/* Default exit sequence for state Selection */
	handle->stateConfVector[0] = Statechart_last_state;
}

/* Default exit sequence for state Return Credit */
static void exseq_main_region_Return_Credit(Statechart* handle)
{
	/* Default exit sequence for state Return Credit */
	handle->stateConfVector[0] = Statechart_last_state;
}

/* Default exit sequence for state Return Product */
static void exseq_main_region_Return_Product(Statechart* handle)
{
	/* Default exit sequence for state Return Product */
	exseq_main_region_Return_Product_Calculate_the_new_cash_value(handle);
}

/* Default exit sequence for state Display Error */
static void exseq_main_region_Return_Product_Calculate_the_new_cash_value_Display_Error(Statechart* handle)
{
	/* Default exit sequence for state Display Error */
	handle->stateConfVector[0] = Statechart_last_state;
}

/* Default exit sequence for state Display Normal */
static void exseq_main_region_Return_Product_Calculate_the_new_cash_value_Display_Normal(Statechart* handle)
{
	/* Default exit sequence for state Display Normal */
	handle->stateConfVector[0] = Statechart_last_state;
}

/* Default exit sequence for region main region */
static void exseq_main_region(Statechart* handle)
{
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of Statechart.main_region) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case Statechart_main_region_Money :
		{
			exseq_main_region_Money(handle);
			break;
		}
		case Statechart_main_region_INIT :
		{
			exseq_main_region_INIT(handle);
			break;
		}
		case Statechart_main_region_Selection :
		{
			exseq_main_region_Selection(handle);
			break;
		}
		case Statechart_main_region_Return_Credit :
		{
			exseq_main_region_Return_Credit(handle);
			break;
		}
		case Statechart_main_region_Return_Product_Calculate_the_new_cash_value_Display_Error :
		{
			exseq_main_region_Return_Product_Calculate_the_new_cash_value_Display_Error(handle);
			break;
		}
		case Statechart_main_region_Return_Product_Calculate_the_new_cash_value_Display_Normal :
		{
			exseq_main_region_Return_Product_Calculate_the_new_cash_value_Display_Normal(handle);
			break;
		}
		default: 
			/* do nothing */
			break;
	}
}

/* Default exit sequence for region Calculate the new cash value */
static void exseq_main_region_Return_Product_Calculate_the_new_cash_value(Statechart* handle)
{
	/* Default exit sequence for region Calculate the new cash value */
	/* Handle exit of all possible states (of Statechart.main_region.Return_Product.Calculate_the_new_cash_value) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case Statechart_main_region_Return_Product_Calculate_the_new_cash_value_Display_Error :
		{
			exseq_main_region_Return_Product_Calculate_the_new_cash_value_Display_Error(handle);
			break;
		}
		case Statechart_main_region_Return_Product_Calculate_the_new_cash_value_Display_Normal :
		{
			exseq_main_region_Return_Product_Calculate_the_new_cash_value_Display_Normal(handle);
			break;
		}
		default: 
			/* do nothing */
			break;
	}
}

/* The reactions of state null. */
static void react_main_region__choice_0(Statechart* handle)
{
	/* The reactions of state null. */
	if ((handle->internal.Product) > (0))
	{ 
		enseq_main_region_Return_Product_default(handle);
	}  else
	{
		enseq_main_region_Return_Credit_default(handle);
	}
}

/* The reactions of state null. */
static void react_main_region__choice_1(Statechart* handle)
{
	/* The reactions of state null. */
	if ((handle->internal.Cash) > (0))
	{ 
		enseq_main_region_Money_default(handle);
	}  else
	{
		enseq_main_region_INIT_default(handle);
	}
}

/* The reactions of state null. */
static void react_main_region_Return_Product_Calculate_the_new_cash_value__choice_0(Statechart* handle)
{
	/* The reactions of state null. */
	if (((handle->internal.Cash - handle->internal.Product)) >= (0))
	{ 
		statechart_internal_set_cash(handle, handle->internal.Cash - handle->internal.Product);
		enseq_main_region_Return_Product_Calculate_the_new_cash_value_Display_Normal_default(handle);
	}  else
	{
		enseq_main_region_Return_Product_Calculate_the_new_cash_value_Display_Error_default(handle);
	}
}

/* Default react sequence for initial entry  */
static void react_main_region__entry_Default(Statechart* handle)
{
	/* Default react sequence for initial entry  */
	enseq_main_region_INIT_default(handle);
}

/* Default react sequence for initial entry  */
static void react_main_region_Return_Product_Calculate_the_new_cash_value__entry_Default(Statechart* handle)
{
	/* Default react sequence for initial entry  */
	react_main_region_Return_Product_Calculate_the_new_cash_value__choice_0(handle);
}


static sc_integer react(Statechart* handle, const sc_integer transitioned_before)
{
	/* State machine reactions. */
	SC_UNUSED(handle);
	return transitioned_before;
}

static sc_integer main_region_Money_react(Statechart* handle, const sc_integer transitioned_before)
{
	/* The reactions of state Money. */
 			sc_integer transitioned_after = transitioned_before;
	if (handle->doCompletion == bool_false)
	{ 
		if ((transitioned_after) < (0))
		{ 
			if (handle->ifaceButton.One_Euro_raised == bool_true)
			{ 
				exseq_main_region_Money(handle);
				statechart_internal_set_cash(handle, handle->internal.Cash + 1);
				enseq_main_region_Money_default(handle);
				react(handle,0);
				transitioned_after = 0;
			}  else
			{
				if (handle->ifaceButton.Two_Euro_raised == bool_true)
				{ 
					exseq_main_region_Money(handle);
					statechart_internal_set_cash(handle, handle->internal.Cash + 2);
					enseq_main_region_Money_default(handle);
					react(handle,0);
					transitioned_after = 0;
				}  else
				{
					if (handle->ifaceButton.Select_raised == bool_true)
					{ 
						exseq_main_region_Money(handle);
						enseq_main_region_Selection_default(handle);
						react(handle,0);
						transitioned_after = 0;
					} 
				}
			}
		} 
		/* If no transition was taken */
		if ((transitioned_after) == (transitioned_before))
		{ 
			/* then execute local reactions. */
			transitioned_after = react(handle,transitioned_before);
		} 
	} return transitioned_after;
}

static sc_integer main_region_INIT_react(Statechart* handle, const sc_integer transitioned_before)
{
	/* The reactions of state INIT. */
 			sc_integer transitioned_after = transitioned_before;
	if (handle->doCompletion == bool_false)
	{ 
		if ((transitioned_after) < (0))
		{ 
			if (handle->ifaceButton.One_Euro_raised == bool_true)
			{ 
				exseq_main_region_INIT(handle);
				statechart_internal_set_cash(handle, handle->internal.Cash + 1);
				enseq_main_region_Money_default(handle);
				react(handle,0);
				transitioned_after = 0;
			}  else
			{
				if (handle->ifaceButton.Two_Euro_raised == bool_true)
				{ 
					exseq_main_region_INIT(handle);
					statechart_internal_set_cash(handle, handle->internal.Cash + 2);
					enseq_main_region_Money_default(handle);
					react(handle,0);
					transitioned_after = 0;
				}  else
				{
					if (handle->ifaceButton.Select_raised == bool_true)
					{ 
						exseq_main_region_INIT(handle);
						enseq_main_region_Selection_default(handle);
						react(handle,0);
						transitioned_after = 0;
					} 
				}
			}
		} 
		/* If no transition was taken */
		if ((transitioned_after) == (transitioned_before))
		{ 
			/* then execute local reactions. */
			transitioned_after = react(handle,transitioned_before);
		} 
	} return transitioned_after;
}

static sc_integer main_region_Selection_react(Statechart* handle, const sc_integer transitioned_before)
{
	/* The reactions of state Selection. */
 			sc_integer transitioned_after = transitioned_before;
	if (handle->doCompletion == bool_false)
	{ 
		if ((transitioned_after) < (0))
		{ 
			if (handle->ifaceButton.Select_raised == bool_true)
			{ 
				exseq_main_region_Selection(handle);
				statechart_internal_set_product(handle, (((handle->internal.Product + 1)) % 4));
				enseq_main_region_Selection_default(handle);
				react(handle,0);
				transitioned_after = 0;
			}  else
			{
				if (handle->ifaceButton.One_Euro_raised == bool_true)
				{ 
					exseq_main_region_Selection(handle);
					statechart_internal_set_cash(handle, handle->internal.Cash + 1);
					enseq_main_region_Money_default(handle);
					react(handle,0);
					transitioned_after = 0;
				}  else
				{
					if (handle->ifaceButton.Two_Euro_raised == bool_true)
					{ 
						exseq_main_region_Selection(handle);
						statechart_internal_set_cash(handle, handle->internal.Cash + 2);
						enseq_main_region_Money_default(handle);
						react(handle,0);
						transitioned_after = 0;
					}  else
					{
						if (handle->ifaceButton.Enter_raised == bool_true)
						{ 
							exseq_main_region_Selection(handle);
							react_main_region__choice_0(handle);
							transitioned_after = 0;
						} 
					}
				}
			}
		} 
		/* If no transition was taken */
		if ((transitioned_after) == (transitioned_before))
		{ 
			/* then execute local reactions. */
			transitioned_after = react(handle,transitioned_before);
		} 
	} return transitioned_after;
}

static sc_integer main_region_Return_Credit_react(Statechart* handle, const sc_integer transitioned_before)
{
	/* The reactions of state Return Credit. */
 			sc_integer transitioned_after = transitioned_before;
	if (handle->doCompletion == bool_true)
	{ 
		/* Default exit sequence for state Return Credit */
		handle->stateConfVector[0] = Statechart_last_state;
		/* 'default' enter sequence for state INIT */
		enact_main_region_INIT(handle);
		handle->stateConfVector[0] = Statechart_main_region_INIT;
		react(handle,0);
	}  else
	{
		/* Always execute local reactions. */
		transitioned_after = react(handle,transitioned_before);
	}
	return transitioned_after;
}

static sc_integer main_region_Return_Product_react(Statechart* handle, const sc_integer transitioned_before)
{
	/* The reactions of state Return Product. */
 			sc_integer transitioned_after = transitioned_before;
	if (handle->doCompletion == bool_false)
	{ 
		/* Always execute local reactions. */
		transitioned_after = react(handle,transitioned_before);
	} return transitioned_after;
}

static sc_integer main_region_Return_Product_Calculate_the_new_cash_value_Display_Error_react(Statechart* handle, const sc_integer transitioned_before)
{
	/* The reactions of state Display Error. */
 			sc_integer transitioned_after = transitioned_before;
	if (handle->doCompletion == bool_true)
	{ 
		/* Default exit sequence for state Display Error */
		handle->stateConfVector[0] = Statechart_last_state;
		/* The reactions of exit default. */
		effect_main_region_Return_Product_tr0(handle);
	}  else
	{
		/* Always execute local reactions. */
		transitioned_after = main_region_Return_Product_react(handle,transitioned_before);
	}
	return transitioned_after;
}

static sc_integer main_region_Return_Product_Calculate_the_new_cash_value_Display_Normal_react(Statechart* handle, const sc_integer transitioned_before)
{
	/* The reactions of state Display Normal. */
 			sc_integer transitioned_after = transitioned_before;
	if (handle->doCompletion == bool_true)
	{ 
		/* Default exit sequence for state Display Normal */
		handle->stateConfVector[0] = Statechart_last_state;
		/* The reactions of exit default. */
		effect_main_region_Return_Product_tr0(handle);
	}  else
	{
		/* Always execute local reactions. */
		transitioned_after = main_region_Return_Product_react(handle,transitioned_before);
	}
	return transitioned_after;
}




static void statechart_eventqueue_init(statechart_eventqueue * eq, statechart_event *buffer, sc_integer capacity)
{
	eq->events = buffer;
	eq->capacity = capacity;
	eq->push_index = 0;
	eq->pop_index = 0;
	eq->size = 0;
}

static sc_integer statechart_eventqueue_size(statechart_eventqueue * eq)
{
	return eq->size;
}

static statechart_event statechart_eventqueue_pop(statechart_eventqueue * eq)
{
	statechart_event event;
	if(statechart_eventqueue_size(eq) <= 0) {
		statechart_event_init(&event, Statechart_invalid_event);
	}
	else {
		event = eq->events[eq->pop_index];
		
		if(eq->pop_index < eq->capacity - 1) {
			eq->pop_index++;
		} 
		else {
			eq->pop_index = 0;
		}
		eq->size--;
	}
	return event;
}
static sc_boolean statechart_eventqueue_push(statechart_eventqueue * eq, statechart_event ev)
{
	if(statechart_eventqueue_size(eq) == eq->capacity) {
		return bool_false;
	}
	else {
		eq->events[eq->push_index] = ev;
		
		if(eq->push_index < eq->capacity - 1) {
			eq->push_index++;
		}
		else {
			eq->push_index = 0;
		}
		eq->size++;
		
		return bool_true;
	}
}
static void statechart_event_init(statechart_event * ev, StatechartEventID name)
{
	ev->name = name;
}

static void statechart_add_event_to_queue(statechart_eventqueue * eq, StatechartEventID name)
{
	statechart_event event;
	statechart_event_init(&event, name);
	statechart_eventqueue_push(eq, event);
}

static sc_boolean statechart_dispatch_event(Statechart* handle, const statechart_event * event) {
	switch(event->name) {
		case Statechart_Button_One_Euro:
		{
			handle->ifaceButton.One_Euro_raised = bool_true;
			return bool_true;
		}
		case Statechart_Button_Two_Euro:
		{
			handle->ifaceButton.Two_Euro_raised = bool_true;
			return bool_true;
		}
		case Statechart_Button_Select:
		{
			handle->ifaceButton.Select_raised = bool_true;
			return bool_true;
		}
		case Statechart_Button_Enter:
		{
			handle->ifaceButton.Enter_raised = bool_true;
			return bool_true;
		}
		default:
			return bool_false;
	}
}

static statechart_event statechart_get_next_event(Statechart* handle)
{
	statechart_event next_event;
	statechart_event_init(&next_event, Statechart_invalid_event);
	if(statechart_eventqueue_size(&(handle->in_event_queue)) > 0) {
		next_event = statechart_eventqueue_pop(&(handle->in_event_queue));
	}
	return next_event;
}

static sc_boolean statechart_dispatch_next_event(Statechart* handle)
{
	statechart_event nextEvent;
	nextEvent = statechart_get_next_event(handle);
	return statechart_dispatch_event(handle, &nextEvent);
}
