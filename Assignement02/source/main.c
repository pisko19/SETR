#include <stdio.h>
#include "../header/Testes.h"

int main(void) {
   int choice = -1;
   do{
   printf("\n"
           "##########################################################################\n"
           "#                WHAT TEST YOU WANT TO MAKE ?                            #\n"
           "#                                                                        #\n"
           "#                0) EXIT                                                 #\n"
           "#                1) Test the RxChar                                      #\n"
           "#                2) Test the TxChar                                      #\n"
           "#                3) Test the cmdProc                                     #\n"
           "#                4) Test the cmdProc with temperature data               #\n"
           "#                5) Test the cmdProc with humidity data                  #\n"
           "#                6) Test the cmdProc with CO2 data                       #\n"
           "#                7) Test the cmdProc with all data                       #\n"
           "#                8) Test the cmdProc with all functions                  #\n"
           "#                                                                        #\n"
           "##########################################################################\n");
           
   
   scanf("%d",&choice);
    
   switch(choice){
        case(0):
        printf("\n\nEND OF THE TESTES\n\n");
        break;
        
    	case(1):
        Teste_RxChar();
        break;
    	
    	case(2): 
        Teste_TxChar();
        break;
    	
    	case(3):
        Teste_Proc();
        break;
        
      case(4):
        Teste_Proc_Temp();
        break;
        
      case(5):
        Teste_Proc_Hum();
        break;
        
      case(6):
        Teste_Proc_CO2();
        break;
      
      case(7):
        Teste_Proc_A();
        break;
        
      case(8):
        Teste_Proc_All();
        break;
   }
   }while(choice!=0);
    return 0;
}
