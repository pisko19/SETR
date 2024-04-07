#include <stdio.h>
#include "../header/Testes.h"
#include "../header/unity.h"

int main(void) {

  UNITY_BEGIN();
  //RUN_TEST(Teste_RxChar);
  //RUN_TEST(Teste_TxChar);
  //RUN_TEST(Teste_Proc);
  //RUN_TEST(Teste_Proc_Temp);
  //RUN_TEST(Teste_Proc_Hum);
  //RUN_TEST(Teste_Proc_CO2);




  
   int choice = -1;
   do{
   printf("\n\n"
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
        RUN_TEST(Teste_RxChar);
        break;
    	
    	case(2): 
        RUN_TEST(Teste_TxChar);
        break;
    	
    	case(3):
        RUN_TEST(Teste_Proc);
        break;
        
      case(4):
        RUN_TEST(Teste_Proc_Temp);
        break;
        
      case(5):
        RUN_TEST(Teste_Proc_Hum);
        break;
        
      case(6):
        RUN_TEST(Teste_Proc_CO2);
        break;
      
      case(7):
        RUN_TEST(Teste_Proc_A);
        break;
        
      case(8):
        //Teste_Proc_All();
        break;
   }
   }while(choice!=0);
    return UNITY_END();
  
}
