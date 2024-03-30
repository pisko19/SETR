#include <stdio.h>
#include "../source/Uart.c"
#include "../source/Testes.c"

int main(void) {
    
    Teste_RxChar();
    Teste_TxChar();
    Teste_Proc();
    return 0;
}

