#include <stdio.h>
#include <stdint.h>
#include "Functions.h"

void statechart_display( Statechart* handle, const sc_integer Type){

   switch(Type){
   	case 0:
   	    printf("\033[;H\n\r"
                "############################################\n\r"
                "#                                          #\n\r"
                "#                  AMOUNT                  #\n\r"
                "#                 --------                 #\n\r"
                "#                   %3d €                  #\n\r"
                "#                                          #\n\r"
                "############################################\n",handle->internal.Cash);
            break;
         
        case 1:
            printf("\033[;H\n\r"
                "############################################\n\r"
                "#                                          #\n\r"
                "#             Product Selection            #\n\r"
                "#                 --------                 #\n\r"
                "#               Product ->%3d              #\n\r"
                "#                Price ->%4d              #\n\r"
                "#                                          #\n\r"
                "############################################\n",handle->internal.Product);
            break;
   }
}

