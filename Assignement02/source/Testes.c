#include <stdio.h>
#include <unistd.h>
#include "../header/Testes.h"
#include "../header/Uart.h"
#include "unity.h"

void setUp(void) {
    // Initialize resources before each test case
}

// Test fixture teardown function (optional)
void tearDown(void) {
    // Clean up resources after each test case
}

void Teste_RxChar(void){
    int x;
    unsigned char y[UART_TX_SIZE];
    
    printf("\nTESTE RxChar:\n\nReturn of rxChar:   ");
    for(unsigned int i=0;i<UART_RX_SIZE+2;i++){
       x = rxChar((unsigned char)(i+'0'));
       printf("%d ",x);
    }
    
    printf("\nValues in RxBuffer: ");
    getRxBuf(y,getRxBufLen());
    for(int i=0;i<UART_RX_SIZE+2;i++){
       printf("%c ",y[i]);
    }
    
    printf("\nReceiver buffer length: %d ",getRxBufLen());
    printf("\nResetRxChar");
    ResetRxChar();
    printf("\nReceiver buffer length: %d ",getRxBufLen());

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
    getTxBuf(y,getTxBufLen());
    for(int i=0;i<UART_TX_SIZE+2;i++){
       printf("%c ",y[i]);
    }
    
    printf("\nTransmisser buffer Length: %d ",getTxBufLen());
    printf("\nResetTxChar");
    ResetTxChar();
    printf("\nTransmisser buffer Length: %d\n\n",getTxBufLen());
}


void Teste_Proc(void){
    printf("\nTESTE cmdProc (1):\n");
    ResetTxChar();
    ResetRxChar();
    
    rxChar('#');
    rxChar('P');
    rxChar('t');
    rxChar('-');
    rxChar('2');
    rxChar('0');
    //rxChar('0');
    //rxChar('0');
    rxChar('!');
    
    int x;
    int y;
    unsigned char yr[UART_RX_SIZE];
    unsigned char yt[UART_TX_SIZE];
    
    printf("\nValues in RxBuffer: ");
    getRxBuf(yr,UART_RX_SIZE);
    for(int i=0;i<UART_RX_SIZE+2;i++){
       printf("%c",yr[i]);
    }
    
    printf("\nReturn of cmdProc: ");
    x=cmdProc();
    printf("%d\n\n",x);
   
    printf("Length Transmisser Buffer (First): %d\n",getTxBufLen());
    y = getTxBuf(yt,getTxBufLen());
    if(y==0)
       printf("Values of TxBuffer (Second): %s\n",yt);
    else
       printf("TxBuffer is empty !\n",yt);
       
    printf("\nLength Transmisser Buffer (Second): %d\n",getTxBufLen());
    y = getTxBuf(yt,getTxBufLen());
    if(y==0)
       printf("Values of TxBuffer (Second): %s\n",yt);
    else
       printf("TxBuffer is empty !\n",yt);
}


void Teste_Proc_Temp(void){

    unsigned char T[7] = {'#','P','t','+','7','0','!'};
    unsigned char teste[UART_TX_SIZE];
    unsigned char X[7] = {'7','1','2','3','4','5','6'};
    int j = 0;
    int tSleep = 1;
    int x;
    
    printf("\nTESTE TEMPERATURE:\n");
    
    while(j<sizeof(X)){
       ResetTxChar();
       ResetRxChar();
       sleep(tSleep);
       for(int i=0; i<sizeof(T); i++){
          if(i==4){
            rxChar(X[j]);
          }
          else{
            rxChar(T[i]);
          }
       }
       printf("\nValues in RxBuffer: ");
       getRxBuf(teste,UART_RX_SIZE);
       for(int i=0;i<UART_RX_SIZE+2;i++){
           printf("%c",teste[i]);
       }
    
       x = cmdProc();
       getTxBuf(teste,TxBufferLen);
       
       printf("\nValues of TxBuffer : %s",teste);
       if(x == ValueError)
          printf("\nThe value of the temperature is incorrect !\n");
       else
          printf("\nThe temperature is %d ºC\n",getInstantTemp());
       j++;
    }
    
    T[3] = '-';
    j=1;
    while(j<sizeof(X)-1){
       ResetTxChar();
       ResetRxChar();
       sleep(tSleep);
       for(int i=0; i<sizeof(T); i++){
          if(i==4){
            rxChar(X[j]);
            
          }
          else{
            rxChar(T[i]);
          }
       }
       printf("\nValues in RxBuffer: ");
       getRxBuf(teste,UART_RX_SIZE);
       for(int i=0;i<UART_RX_SIZE+2;i++){
           printf("%c",teste[i]);
       }
    
       x = cmdProc();
       getTxBuf(teste,TxBufferLen);
       printf("\nValues of TxBuffer : %s",teste);
       if(x == ValueError)
          printf("\nThe value of the temperature is incorrect !\n");
       else
          printf("\nThe temperature is %d ºC\n",getInstantTemp());
       j++;
    }
}


void Teste_Proc_Hum(void){

    char T[7] = {'#','P','h','0','0','0','!'};
    unsigned char teste[UART_TX_SIZE];
    unsigned char y;
    int X = 0;
    int j = 0;
    int tSleep = 1;
    int x;
    
    printf("\nTESTE HUMIDITY:\n");
    
    while(j<9){
       ResetTxChar();
       ResetRxChar();
       sleep(tSleep);
       numtoChar(X+j*15,T,3);
       
       for(int i=0; i<sizeof(T); i++)
            rxChar(T[i]);
            
       printf("\nValues in RxBuffer: ");
       getRxBuf(teste,UART_RX_SIZE);
       for(int i=0;i<UART_RX_SIZE+2;i++){
           printf("%c",teste[i]);
       }
    
       x = cmdProc();
       getTxBuf(teste,TxBufferLen);
       printf("\nValues of TxBuffer : %s",teste);
       if(x == ValueError)
          printf("\nThe value of the humidity is incorrect !\n");
       else
          printf("\nThe humidity is %d % \n",getInstantHum());
       j++;
    }
}


void Teste_Proc_CO2(void){

    char T[9] = {'#','P','c','0','0','0','0','0','!'};
    unsigned char teste[UART_TX_SIZE];
    unsigned char y;
    int X = 200;
    int j = 0;
    int tSleep = 1;
    int x;
    
    printf("\nTESTE CO2:\n");
    
    while(j<10){
       ResetTxChar();
       ResetRxChar();
       sleep(tSleep);
       numtoChar(X+j*2500,T,5);
       
       for(int i=0; i<sizeof(T); i++)
            rxChar(T[i]);
          
       printf("\nValues in RxBuffer: ");
       getRxBuf(teste,UART_RX_SIZE);
       for(int i=0;i<UART_RX_SIZE+2;i++){
           printf("%c",teste[i]);
       }
    
       x = cmdProc();
       getTxBuf(teste,TxBufferLen);
       printf("\nValues of TxBuffer : %s",teste);
       if(x == ValueError)
          printf("\nThe value of the CO2 is incorrect !\n");
       else
          printf("\nThe CO2 is %d ppm\n",getInstantCO2());
       j++;
    }
}

void Teste_Proc_All(void){

    char T[17] = {'#','A','t','-','3','7','h','0','5','8','c','1','7','4','2','0','!'};
    unsigned char y;
    unsigned char teste[UART_TX_SIZE];
    
    ResetTxChar();
    ResetRxChar();
    for(int i=0; i<sizeof(T); i++){
        rxChar(T[i]);
            
    }
    
    printf("\nValues in RxBuffer: ");
    getRxBuf(teste,UART_RX_SIZE);
    for(int i=0;i<UART_RX_SIZE+2;i++){
        printf("%c",teste[i]);
    }
    
    int x = cmdProc();
    getTxBuf(teste,TxBufferLen);
    printf("\nValues of TxBuffer : %s\n",teste);
    if(x == ValueError){
       printf("\nThe value of the CO2 is incorrect !");
       printf("\nThe value of the humidity is incorrect !");
       printf("\nThe value of the temperature is incorrect !");}
    else{
       printf("\nThe CO2 is %d ppm",getInstantCO2());
       printf("\nThe humidity is %d %",getInstantHum());
       printf("\nThe temperature is %d ºC\n",getInstantTemp());}

}


void numtoChar(int num, char array[], int len) {
    char digits[len]; // Initialize digits array with size len
    for (int i = 0; i < len; i++)
        digits[i] = '0'; // Initialize digits array with zeros
    
    int index = len - 1; // Index for digits array

    // Extract digits from num and store them in reverse order
    while (num > 0 && index >= 0) {
        digits[index] = (num % 10) + '0';
        num /= 10;
        index--;
    }
    
    // Copy digits to array
    for (int i = 0; i < len; i++) 
        array[i+3] = digits[i];
   
}

void TESTE (void){
    unsigned char T[17] = {'#','A','t','-','3','7','h','0','5','8','c','1','7','4','2','0','!'};
    unsigned char y;
    unsigned char teste[UART_TX_SIZE];
    
    ResetTxChar();
    ResetRxChar();
    for(int i=0; i<sizeof(T); i++){
        rxChar(T[i]);
            
    }
    printf("\nValues of RxBuffer : ");
    for(int i=0; i<UART_RX_SIZE; i++){
        y=RxBuffer[i];
        printf("%c",y);
    }
    int x = cmdProc();
    getTxBuf(teste,TxBufferLen);
    printf("\nValues of TxBuffer : %s",teste);
    if(x == ValueError){
       printf("\nThe value of the CO2 is incorrect !\n");
       printf("\nThe value of the humidity is incorrect !\n");
       printf("\nThe value of the temperature is incorrect !\n");}
    else{
       printf("\nThe CO2 is %d ppm\n",co2[0]);
       printf("\nThe humidity is %d %\n",hum[0]);
       printf("\nThe temperature is %d ºC\n",temp[0]);}

}
