#include <stdio.h>
#include "../header/Testes.h"

void Teste_RxChar(void){
    int x;
    unsigned char y;
    
    printf("\nTESTE RxChar:\n\nReturn of rxChar:   ");
    for(int i=0;i<UART_RX_SIZE+2;i++){
       x = rxChar('5');
       printf("%d ",x);
    }
    printf("\nValues of RxBuffer: ");
    for (int i=0; i<UART_RX_SIZE+2; i++){
       y=RxBuffer[i];
       printf("%s",&y);
    }
    printf("\nLength: %d ",RxBufferLen);
    printf("\nResetRxChar\n");
    ResetRxChar();
    printf("Length: %d\n\n",RxBufferLen);

}

void Teste_TxChar(void){
    int x;
    unsigned char y[UART_TX_SIZE];
    
    printf("\nTESTE TxChar:\n\nReturn of txChar:   ");
    for(int i=0;i<UART_TX_SIZE+2;i++){
       x = txChar('4');
       printf("%d ",x);
    }
    printf("\nValues in TxBuffer: ");
    getTxBuf(y,UART_TX_SIZE);
    printf("%s",y);
    
    printf("\nLength: %d ",TxBufferLen);
    printf("\nResetTxChar\n");
    ResetTxChar();
    printf("Length: %d\n\n",TxBufferLen);
}

void Teste_Proc(void){
    printf("\nTESTE Completo:\n");
    ResetTxChar();
    ResetRxChar();
    
    rxChar('#');
    rxChar('P');
    rxChar('t');
    rxChar('+');
    rxChar('4');
    rxChar('2');
    rxChar('!');
    
    int x;
    unsigned char y;
    printf("\nValues of RxBuffer: ");
    for (int i=0; i<UART_RX_SIZE; i++){
       y=RxBuffer[i];
       printf("%s",&y);
    }
    printf("\n");
    x=cmdProc();
    printf("%d\n",x);
    
    unsigned char teste[UART_TX_SIZE];
    getTxBuf(teste,UART_TX_SIZE);
    printf("%s\n",teste);
}
