/* Simple app development with CMake 
*  Ilustrates how to create and use libraries
*  Paulo Pedreiras, Mar/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include "movavg.h"

#define MAXN 10 /* Limit the sequence to test */

int main(void)
{
	int x; // Variable not used. Will generate an error if "-Wall -Werror" are set
	
	int i=0;
	
	printf("Simple Project - Modular SW development illustration");
	
	mavg_init();
	   
	for(i=0; i<MAXN; i++) {
		mavg_add(i);
		printf("i=%d: movag is %f\n\r",i,mavg_get());
	}
	
	return 0;
	
}
