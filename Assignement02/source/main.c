#include <stdio.h>
#include "../header/Testes.h"

int main(void) {
    printf("\n\n############################################################################################\n\n");
    Teste_RxChar();
    
    printf("\n\n############################################################################################\n\n");
    Teste_TxChar();
    
    printf("\n\n############################################################################################\n\n");
    Teste_Proc();
    
    printf("\n\n############################################################################################\n\n");
    Teste_Proc_Temp();
    
    printf("\n\n############################################################################################\n\n");
    Teste_Proc_Hum();
    
    printf("\n\n############################################################################################\n\n");
    Teste_Proc_CO2();
    
    printf("\n\n############################################################################################\n\n");
    Teste_Proc_All();
    
    //printf("\n\n############################################################################################\n\n");
    //TESTE();
    return 0;
}

