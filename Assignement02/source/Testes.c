#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "../header/Testes.h"
#include "../header/Uart.h"
#include "../header/unity.h"

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
       x = rxChar((unsigned char)('5'));
       printf("%d ",x);
    }
    
    printf("\nValues in RxBuffer: ");
    getRxBuf(y,getRxBufLen());
    for(int i=0;i<UART_RX_SIZE+2;i++){
       printf("%c ",y[i]);
    }
    
    printf("\nReceiver buffer length: %d",getRxBufLen());
    printf("\nResetRxChar");
    ResetRxChar();
    printf("\nReceiver buffer length: %d\n\n",getRxBufLen());

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
    printf("\n\nTESTE cmdProc :\n");
    ResetTxChar();
    ResetRxChar();
    
    rxChar('#');
    rxChar('L');
    //rxChar('t');
    //rxChar('-');
    //rxChar('2');
    //rxChar('0');
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
   
    printf("FIRST getTxBuf call:\n"
           "Length Transmisser Buffer (First): %d\n",getTxBufLen());
           
    y = getTxBuf(yt,getTxBufLen());
    if(y==0)
       printf("Values of TxBuffer (Second): %s\n\n",yt);
    else
       printf("TxBuffer is empty !\n\n");
       
    printf("SECOND getTxBuf call:\n"
           "Length Transmisser Buffer (First): %d\n",getTxBufLen());
    y = getTxBuf(yt,getTxBufLen());
    if(y==0)
       printf("Values of TxBuffer (Second): %s\n\n",yt);
    else
       printf("TxBuffer is empty !\n\n");
}


void Teste_Proc_Temp(void){

    unsigned char T[7] = {'#','P','t','+','7','0','!'};
    unsigned char rx[UART_RX_SIZE];
    unsigned char tx[UART_TX_SIZE];
    int x,temperature;
    
    printf("\nTESTE TEMPERATURE:\n");
    
    while(1){
       memset(rx, '\0', UART_RX_SIZE);
       memset(tx, '\0', UART_TX_SIZE);
       ResetTxChar();
       ResetRxChar();
       
       printf("\nWhat temperature you want to teste ?\n(Values accepted -99 to 99, Values correct -50 to 60, Else is exit values)\n");
       scanf("%d",&temperature);
       
       if(temperature >= 0 && temperature <100 ){
          T[3] = '+';
          numtoChar(&T[5],temperature,2);
       }
       else if (temperature <0 && temperature >-100){
          T[3] = '-';
          numtoChar(&T[5],-temperature,2);
       }
       else{
          printf("\nEND\n");
          return;
      }
       
       for(int i=0; i<sizeof(T); i++)
            rxChar(T[i]);
            
       getRxBuf(rx,UART_RX_SIZE);
       printf("\n------------------------------------------\n"
              "\nValues in RxBuffer : %s",rx);
    
       x = cmdProc();
       getTxBuf(tx,getTxBufLen());
       
       printf("\nValues of TxBuffer : %s",tx);
       if(x != END)
          printf("\nThe value of the temperature is incorrect !\n");
       else
          printf("\nThe temperature is %d ºC \n",getInstantTemp());
          
       printf("\n------------------------------------------\n");
    }
    
}


void Teste_Proc_Hum(void){

    unsigned char T[7] = {'#','P','h','0','0','0','!'};
    unsigned char rx[UART_RX_SIZE];
    unsigned char tx[UART_TX_SIZE];
    int x,humidity;
    
    printf("\nTESTE HUMIDITY:\n");
    
    while(1){
       ResetTxChar();
       ResetRxChar();
       memset(rx, '\0', UART_RX_SIZE);
       memset(tx, '\0', UART_TX_SIZE);
       
       printf("\nWhat humidity you want to teste ?\n(Values accepted 0 to 999, Values correct 0 to 100, Else is exit values)\n");
       scanf("%d",&humidity);
       
       if(humidity < 0 || humidity > 999 ){
          printf("\nEND\n");
          break;
       }
       
       numtoChar(&T[5],humidity,3);
       
       for(int i=0; i<sizeof(T); i++)
            rxChar(T[i]);
            
       getRxBuf(rx,UART_RX_SIZE);
       printf("\n------------------------------------------\n"
              "\nValues in RxBuffer : %s",rx);
    
       x = cmdProc();
       getTxBuf(tx,getTxBufLen());
       
       printf("\nValues of TxBuffer : %s",tx);
       if(x != END)
          printf("\nThe value of the humidity is incorrect !\n");
       else
          printf("\nThe humidity is %d '%'\n",getInstantHum());
       
       printf("\n------------------------------------------\n");
    }
}


void Teste_Proc_CO2(void){

    unsigned char T[9] = {'#','P','c','0','0','0','0','0','!'};
    unsigned char rx[UART_RX_SIZE];
    unsigned char tx[UART_TX_SIZE];
    int x,co2;
    
    printf("\nTESTE CO2:\n");
    
    while(1){
       ResetTxChar();
       ResetRxChar();
       memset(rx, '\0', UART_RX_SIZE);
       memset(tx, '\0', UART_TX_SIZE);
       
       printf("\nWhat CO2 you want to teste ?\n(Values accepted 0 to 99999, Values correct 400 to 20000, Else is exit values)\n");
       scanf("%d",&co2);
       
       if(co2 < 0 || co2 > 99999 ){
          printf("\nEND\n");
          break;
      }
       numtoChar(&T[7],co2,5);
       
       for(int i=0; i<sizeof(T); i++)
            rxChar(T[i]);
          
       getRxBuf(rx,UART_RX_SIZE);
       printf("\n------------------------------------------\n"
              "\nValues in RxBuffer : %s",rx);
    
       x = cmdProc();
       getTxBuf(tx,getTxBufLen());
       
       printf("\nValues of TxBuffer : %s",tx);
       if(x != END)
          printf("\nThe value of the CO2 is incorrect !\n");
       else
          printf("\nThe CO2 is %d ppm\n",getInstantCO2());
       
       printf("\n------------------------------------------\n");
    }
}

void Teste_Proc_All(void){

    unsigned char T[6][17] = {{'#','A','t','+','0','0','h','0','0','0','c','0','0','0','0','0','!'},
                              {'#','A','t','+','0','0','c','0','0','0','0','0','h','0','0','0','!'},
                              {'#','A','h','0','0','0','c','0','0','0','0','0','t','+','0','0','!'},
                              {'#','A','h','0','0','0','t','+','0','0','c','0','0','0','0','0','!'},
                              {'#','A','c','0','0','0','0','0','t','+','0','0','h','0','0','0','!'},
                              {'#','A','c','0','0','0','0','0','h','0','0','0','t','+','0','0','!'}};
    unsigned char T2[17];
    unsigned char rx[UART_RX_SIZE];
    unsigned char tx[UART_TX_SIZE];
    int temperature,humidity,co2,format;
    
    printf("\nWhat CO2 you want to teste ? (between 400 and 20000)\n");
    scanf("%d",&co2);
    printf("\nWhat humidity you want to teste ? (between 0 and 100)\n");
    scanf("%d",&humidity);
    printf("\nWhat temperature you want to teste ? (between -50 and 60)\n");
    scanf("%d",&temperature);
       
    while(1){
       ResetTxChar();
       ResetRxChar();
       memset(rx, '\0', UART_RX_SIZE);
       memset(tx, '\0', UART_TX_SIZE);
       
       do{
       printf("\nWhat format you want to teste ?\n"
              "0) exit\n"
              "1) Format temperature  humidity  CO2\n"
              "2) Format temperature  CO2  humidity\n"
              "3) Format humidity  CO2  temperature\n"
              "4) Format humidity  temperature  CO2\n"
              "5) Format CO2  temperature  humidity\n"
              "6) Format CO2  humidity  temperature\n");
       
       scanf("%d",&format);
       if(format>6 || format<0)
          printf("\n---- WRONG NUMBER TRY ANOTHER ONE ----\n");
       }while(format>6 || format<0);
       
       if(format==0)
          break;
          
       for(int i=0;i<17;i++){
           T2[i] = T[format-1][i];
       }
       
       for(int i=0;i<17;i++){
           if(T2[i] == 't'){
              if(temperature>0)
                 numtoChar(&T2[i+3],temperature,2);
              else{
                 T2[i+1] = '-';
                 numtoChar(&T2[i+3],-temperature,2);
              }
           }
           else if(T2[i] == 'h')
              numtoChar(&T2[i+3],humidity,3);
           else if(T2[i] == 'c')
              numtoChar(&T2[i+5],co2,5);
       }
       
       for(int i=0; i<17; i++){
           rxChar(T2[i]);
       }
    
       getRxBuf(rx,UART_RX_SIZE);
       printf("\n------------------------------------------\n"
              "\nValues in RxBuffer : %s",rx);
                 
    
       int x = cmdProc();
       getTxBuf(tx,getTxBufLen());
      
       printf("\nValues of TxBuffer : %s\n",tx);
       
       if(x != END){
          printf("\nOne of these values are wrong\n");
       }
       else{
       for(int i=0;i<17;i++){
           if(T2[i] == 't')
              printf("\nThe temperature is %d ºC",getInstantTemp());
           else if(T2[i] == 'h')
              printf("\nThe humidity is %d '%'",getInstantHum());
           else if(T2[i] == 'c')
              printf("\nThe CO2 is %d ppm",getInstantCO2());
       }
       }
       printf("\n\n------------------------------------------\n");
    }
}


void Teste_Proc_L(void){
    unsigned char T[3] = {'#','L','!'};
    unsigned char T2[7] = {'#','P','t','+','0','0','!'};
    unsigned char rx[UART_RX_SIZE];
    unsigned char tx[UART_TX_SIZE];
    unsigned int* temperature;
    unsigned int* humidity;
    unsigned int* co2;
    
    for(int i=0; i<3; i++) 
            rxChar(T[i]);
          
    getRxBuf(rx,UART_RX_SIZE);
    printf("\n------------------------------------------\n"
           "\nValues in RxBuffer : %s",rx);
    
    int x = cmdProc();
    getTxBuf(tx,getTxBufLen());
       
    printf("\nValues of TxBuffer : %s"
           "\nReturn of cmdProc  : %d"
          "\n------------------------------------------\n",tx,x);
              
    temperature = getTemp();
    humidity = getHum();
    co2 = getCO2();
       
    printf("Size of int: %zu bytes\n", sizeof(int));
    printf("%d %d",temperature+4,*(temperature+4));


}

void TESTE (void){
     unsigned char T[6][17] = {
        {'#','A','t','+','0','0','h','0','0','0','c','0','0','0','0','0','!'},
        {'#','A','t','+','0','0','c','0','0','0','0','0','h','0','0','0','!'},
        {'#','A','h','0','0','0','c','0','0','0','0','0','t','+','0','0','!'},
        {'#','A','h','0','0','0','t','+','0','0','c','0','0','0','0','0','!'},
        {'#','A','c','0','0','0','0','0','t','+','0','0','h','0','0','0','!'},
        {'#','A','c','0','0','0','0','0','h','0','0','0','t','+','0','0','!'}
    };
    unsigned char T2[17];
    
    for(int i=0;i<17;i++){
       T2[i] = T[2][i];
    }
    printf("\nTestes -> %s\n",T2);

}
