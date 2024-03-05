#include <stdio.h>
#include <stdlib.h>
#include "movavg.h"
#define MAVG_SIZE 3

/* This variable is private to the module. */
/* It is indirectly managed by the module interface functions */
static int vect[MAVG_SIZE]; 


/* Inits the data structures */
void mavg_init(void)
{ 
	printf("\t mavg_init: called\n");
	int i=0;
	
	for (i=0; i<MAVG_SIZE; i++) { 
		vect[i] = 0;
	}
	   
	return;		
	
}

/* Adds an element */
void mavg_add(int n)
{
	int i = 0;
	
	printf("\t mavg_add: called\n");
	for (i=1; i<MAVG_SIZE; i++) {
		vect[i-1] = vect[i];
	}
	
	vect[i-1] = n;
	
	printf("\t\t vect[] contents: {");
	for (i=0; i<MAVG_SIZE; i++) {
		printf(" %d ",vect[i]);
	}
	printf("}\n");
	
	return;
	
	
}

/* Returns the moving average */
float mavg_get(void)
{
	int i=0, sum=0;
	
	printf("\t mavg_get: called\n");
	for (i=0; i<MAVG_SIZE; i++) {
		sum += vect[i];
	}
	
	return ((float)sum / MAVG_SIZE) ; 
	
}

