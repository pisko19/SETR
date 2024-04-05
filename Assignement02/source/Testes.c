#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "../header/Testes.h"
#include "../header/Uart.h"
#include "../header/unity.h" 

#define CheckError 1 //Change this value if you want to make a checksum error

void setUp(void) {
    // Initialize resources before each test case
}

// Test fixture teardown function (optional)
void tearDown(void) {
    // Clean up resources after each test case
}


void Teste_RxChar(void) {
    unsigned char rxBuffer[UART_RX_SIZE];
    unsigned char expectedBuffer[UART_RX_SIZE];
    
    // Simulate receiving characters
    for (unsigned int i = 0; i < UART_RX_SIZE + 2; i++) {
        // Call rxChar with a dummy character
        int result = rxChar('5');
        // Assert the result
        if (i < UART_RX_SIZE) {
            // Expecting END as long as buffer is not full
            TEST_ASSERT_EQUAL_INT(END, result);
            // Fill expectedBuffer with dummy character '5'
            expectedBuffer[i] = '5';
        } else {
            // Expecting Size_Error when buffer is full
            TEST_ASSERT_EQUAL_INT(Size_Error, result);
        }
    }
    
    // Check the content of the RxBuffer
    getRxBuf(rxBuffer, getRxBufLen());
    TEST_ASSERT_EQUAL_STRING_LEN(expectedBuffer, rxBuffer, UART_RX_SIZE);
    
    // Reset RxBuffer
    ResetRxChar();
    // Check if RxBuffer is empty after reset
    TEST_ASSERT_EQUAL_INT(0, getRxBufLen());
}

void Teste_TxChar(void) {
    unsigned char txBuffer[UART_TX_SIZE];
    unsigned char expectedBuffer[UART_TX_SIZE];
    
    // Simulate transmitting characters
    for (int i = 0; i < UART_TX_SIZE + 2; i++) {
        // Call txChar with a dummy character
        int result = txChar('4');
        // Assert the result
        if (i < UART_TX_SIZE) {
            // Expecting END as long as buffer is not full
            TEST_ASSERT_EQUAL_INT(END, result);
            // Fill expectedBuffer with dummy character '4'
            expectedBuffer[i] = '4';
        } else {
            // Expecting Size_Error when buffer is full
            TEST_ASSERT_EQUAL_INT(Size_Error, result);
        }
    }
    
    // Check the content of the TxBuffer
    getTxBuf(txBuffer, getTxBufLen());
    TEST_ASSERT_EQUAL_STRING_LEN(expectedBuffer, txBuffer, UART_TX_SIZE);
    
    // Reset TxBuffer
    ResetTxChar();
    // Check if TxBuffer is empty after reset
    TEST_ASSERT_EQUAL_INT(0, getTxBufLen());
}

void Teste_Proc(void) {
    unsigned char testInput[10] = {'#', 'P', 't', '+', '2', '0', 'A', 'A', 'A', '!'};
    unsigned char expectedRxBuffer[] = {'#', 'P', 't', '+', '2', '0', 'A', 'A', 'A', '!'};
    unsigned char expectedTxBuffer[] = {'#', 'P', 't', '+', '2', '0', 'A', 'A', 'A', '0', '0', '0', '!', '\0'};
    
    // Initialize UART
    init();
    
    // Call rxChar with test input
    for (unsigned int i = 0; i < sizeof(testInput); i++) {
        rxChar(testInput[i]);
    }
    
    // Call cmdProc and assert its return value
    int result = cmdProc();
    TEST_ASSERT_EQUAL_INT(END, result); // Adjust this assertion as per your function's behavior
    // Check the content of RxBuffer
    unsigned char rxBuffer[UART_RX_SIZE];
    getRxBuf(rxBuffer, getRxBufLen());
    TEST_ASSERT_EQUAL_STRING_LEN(expectedRxBuffer, rxBuffer, sizeof(expectedRxBuffer));
    
    // Check the content of TxBuffer
    unsigned char txBuffer[UART_TX_SIZE];
    getTxBuf(txBuffer, getTxBufLen());
    TEST_ASSERT_EQUAL_STRING_LEN(expectedTxBuffer, txBuffer, sizeof(expectedTxBuffer));
    
}  

/*
void Teste_RxChar(void){
    int x;
    unsigned char y[UART_TX_SIZE];
    
    printf("\nTESTE RxChar:\n\nReturn of rxChar:   ");
    for(unsigned int i=0;i<UART_RX_SIZE+2;i++){
       x = rxChar((unsigned char)('5'));
       printf("%d",x);
    }
    
    getRxBuf(y,getRxBufLen());
    printf("\nValues in RxBuffer: %s",y);
    printf("\nReceiver buffer length: %d",getRxBufLen());
    printf("\nResetRxChar");
    ResetRxChar();
    printf("\nReceiver buffer length: %d\n\n",getRxBufLen());

}
*/
/*
void Teste_TxChar(void){
    int x;
    unsigned char y[UART_TX_SIZE];
    
    printf("\nTESTE TxChar:\n\nReturn of txChar:   ");
    for(int i=0;i<UART_TX_SIZE+2;i++){
       x = txChar('4');
       printf("%d",x);
    }
    
    getTxBuf(y,getTxBufLen());
    printf("\nValues in TxBuffer: %s ",y);
    printf("\nTransmisser buffer Length: %d\n\n",getTxBufLen());
    
}


void Teste_Proc(void){
    unsigned char T[10] = {'#','P','t','+','2','0','A','A','A','!'};
    int y;
    unsigned char yr[UART_RX_SIZE];
    unsigned char yt[UART_TX_SIZE];
    
    printf("\n\nTESTE cmdProc :\n\n");
    init();
    
    numtoChar(&T[8],(CheckSum(&T[1],5)+CheckError),3);
    for(unsigned int i=0; i<sizeof(T); i++)
            rxChar(T[i]);
    
    printf("Before cmdProc call:\n"
           "Length Receiver Buffer : %d\n",getRxBufLen());
           
    y = getRxBuf(yr,getRxBufLen());
    if(y==0)
       printf("Values of RxBuffer : %s\n",yr);
    else
       printf("RxBuffer is empty !\n");
    
    ErrorCode(cmdProc());
    
    printf("\nAfter cmdProc call:\n"
           "Length Receiver Buffer : %d\n",getRxBufLen());
    y = getRxBuf(yr,getRxBufLen());
    if(y==0)
       printf("Values of TxBuffer (Second): %s\n\n",yr);
    else
       printf("RxBuffer is empty !\n\n");
       
   
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

    unsigned char T[10] = {'#','P','t','+','7','0','A','A','A','!'};
    unsigned char rx[UART_RX_SIZE];
    unsigned char tx[UART_TX_SIZE];
    int x,temperature;
    
    printf("\nTESTE TEMPERATURE:\n");
    
    while(1){
       memset(rx, '\0', UART_RX_SIZE);
       memset(tx, '\0', UART_TX_SIZE);
       init();
       
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
      
      numtoChar(&T[8],(CheckSum(&T[1],5)+CheckError),3);
      for(unsigned int i=0; i<sizeof(T); i++)
            rxChar(T[i]);
            
      getRxBuf(rx,getRxBufLen());
      printf("\n------------------------------------------\n"
             "\nValues in RxBuffer : %s",rx);
    
      x = cmdProc();
      ErrorCode(x);
      getTxBuf(tx,getTxBufLen());
       
      printf("Values of TxBuffer : %s",tx);
      if(x != END)
         printf("\nThe value of the temperature is incorrect !\n");
      else
         printf("\nThe temperature is %d ºC \n",getInstantTemp());
         
      printf("\n------------------------------------------\n");
   }  
}


void Teste_Proc_Hum(void){

    unsigned char T[10] = {'#','P','h','0','0','0','A','A','A','!'};
    unsigned char rx[UART_RX_SIZE];
    unsigned char tx[UART_TX_SIZE];
    int x,humidity;
    
    printf("\nTESTE HUMIDITY:\n");
    
    while(1){
       memset(rx, '\0', UART_RX_SIZE);
       memset(tx, '\0', UART_TX_SIZE);
       init();
       
       printf("\nWhat humidity you want to teste ?\n(Values accepted 0 to 999, Values correct 0 to 100, Else is exit values)\n");
       scanf("%d",&humidity);
       
       if(humidity < 0 || humidity > 999 ){
          printf("\nEND\n");
          break;
       }
       
       numtoChar(&T[5],humidity,3);
       numtoChar(&T[8],(CheckSum(&T[1],5)+CheckError),3);
       for(unsigned int i=0; i<sizeof(T); i++)
            rxChar(T[i]);
            
       getRxBuf(rx,getRxBufLen());
       printf("\n------------------------------------------\n"
              "\nValues in RxBuffer : %s",rx);
    
       x = cmdProc();
       ErrorCode(x);
       getTxBuf(tx,getTxBufLen());
       
       printf("Values of TxBuffer : %s",tx);
       if(x != END)
          printf("\nThe value of the humidity is incorrect !\n");
       else
          printf("\nThe humidity is %d %%\n",getInstantHum());
       
       printf("\n------------------------------------------\n");
    }
}


void Teste_Proc_CO2(void){

    unsigned char T[12] = {'#','P','c','0','0','0','0','0','A','A','A','!'};
    unsigned char rx[UART_RX_SIZE];
    unsigned char tx[UART_TX_SIZE];
    int x,co2;
    
    printf("\nTESTE CO2:\n");
    
    while(1){
       memset(rx, '\0', UART_RX_SIZE);
       memset(tx, '\0', UART_TX_SIZE);
       init();
       
       printf("\nWhat CO2 you want to teste ?\n(Values accepted 0 to 99999, Values correct 400 to 20000, Else is exit values)\n");
       scanf("%d",&co2);
       
       if(co2 < 0 || co2 > 99999 ){
          printf("\nEND\n");
          break;
      }
       numtoChar(&T[7],co2,5);
       numtoChar(&T[10],(CheckSum(&T[1],7)+CheckError),3);
       for(unsigned int i=0; i<sizeof(T); i++)
            rxChar(T[i]);
          
       getRxBuf(rx,getRxBufLen());
       printf("\n------------------------------------------\n"
              "\nValues in RxBuffer : %s",rx);
    
       x = cmdProc();
       ErrorCode(x);
       getTxBuf(tx,getTxBufLen());
       
       printf("Values of TxBuffer : %s",tx);
       if(x != END)
          printf("\nThe value of the CO2 is incorrect !\n");
       else
          printf("\nThe CO2 is %d ppm\n",getInstantCO2());
       
       printf("\n------------------------------------------\n");
    }
}

void Teste_Proc_A(void){

    unsigned char T[6][20] = {{'#','A','t','+','0','0','h','0','0','0','c','0','0','0','0','0','A','A','A','!'},
                              {'#','A','t','+','0','0','c','0','0','0','0','0','h','0','0','0','A','A','A','!'},
                              {'#','A','h','0','0','0','c','0','0','0','0','0','t','+','0','0','A','A','A','!'},
                              {'#','A','h','0','0','0','t','+','0','0','c','0','0','0','0','0','A','A','A','!'},
                              {'#','A','c','0','0','0','0','0','t','+','0','0','h','0','0','0','A','A','A','!'},
                              {'#','A','c','0','0','0','0','0','h','0','0','0','t','+','0','0','A','A','A','!'}};
    unsigned char T2[20];
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
       memset(rx, '\0', UART_RX_SIZE);
       memset(tx, '\0', UART_TX_SIZE);
       init();
       
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
          
       for(int i=0;i<20;i++){
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
       
       numtoChar(&T2[18],(CheckSum(&T2[1],15)+CheckError),3);
       for(int i=0; i<20; i++){
           rxChar(T2[i]);
       }
       getRxBuf(rx,getRxBufLen());
       printf("\n------------------------------------------\n"
              "\nValues in RxBuffer : %s",rx);
                 
    
       int x = cmdProc();
       ErrorCode(x);
       getTxBuf(tx,getTxBufLen());
      
       printf("Values of TxBuffer : %s\n",tx);
       
       if(x != END){
          printf("\nOne of these values are wrong\n");
       }
       else{
       for(int i=0;i<17;i++){
           if(T2[i] == 't')
              printf("\nThe temperature is %d ºC",getInstantTemp());
           else if(T2[i] == 'h')
              printf("\nThe humidity is %d %% ",getInstantHum());
           else if(T2[i] == 'c')
              printf("\nThe CO2 is %d ppm",getInstantCO2());
       }
       }
       printf("\n\n------------------------------------------\n");
    }
}


void Teste_Proc_All(void){
    unsigned char T1[10] = {'#','P','t','+','0','0','A','A','A','!'};
    unsigned char T2[10] = {'#','P','h','0','0','0','A','A','A','!'};
    unsigned char T3[12] = {'#','P','c','0','0','0','0','0','A','A','A','!'};
    unsigned char T4[20] = {'#','A','t','+','0','0','h','0','0','0','c','0','0','0','0','0','A','A','A','!'};
    unsigned char T5[6] = {'#','L','A','A','A','!'};
    unsigned char T6[6] = {'#','R','A','A','A','!'};
    unsigned char rx[UART_RX_SIZE];
    unsigned char tx[UART_TX_SIZE];
    unsigned int* temperature;
    unsigned int* humidity;
    unsigned int* co2;
    int choice,temp,hum,CO2;
    int CheckErro = 0; // Modificar o valor caso queira que o checksum de erro
    
    init();
    while(choice!=0){
    memset(rx, '\0', UART_RX_SIZE);
    memset(tx, '\0', UART_TX_SIZE);
    printf("\n------------------------------------------\n"
           "\nWHAT DO YOU WANT TO DO ?"
           "\n0) EXIT"
           "\n1) Adding a temperature value"
           "\n2) Adding a humidity value"
           "\n3) Adding a CO2 value"
           "\n4) Adding all values"
           "\n5) Read the lastest 20 values of all type"
           "\n6) Rest all values\n");
    scanf("%d",&choice);
    printf("\n------------------------------------------\n");
    
    switch(choice){
       case 1:
          printf("\nWhat temperature you want to put ? (-50 to 60)\n");
          scanf("%d",&temp);
          if(temp>0){
              T1[3] = '+';
              numtoChar(&T1[5],temp,2);
          }
          else{
              T1[3] = '-';
              numtoChar(&T1[5],-temp,2);
          }
          numtoChar(&T1[8],(CheckSum(&T1[1],5)+CheckError),3);
          
          for(int i=0; i<10; i++) 
              rxChar(T1[i]);
          break;
          
        case 2:
          printf("\nWhat humidity you want to put ? (0 to 100)\n");
          scanf("%d",&hum);
          numtoChar(&T2[5],hum,3);
          numtoChar(&T2[8],(CheckSum(&T2[1],5)+CheckError),3);
          for(int i=0; i<10; i++) 
              rxChar(T2[i]);
          break;
          
        case 3:
          printf("\nWhat CO2 you want to put ? (400 to 20000)\n");
          scanf("%d",&CO2);
          numtoChar(&T3[7],CO2,5);
          numtoChar(&T3[10],(CheckSum(&T3[1],7)+CheckError),3);
          for(int i=0; i<12; i++) 
              rxChar(T3[i]);
          break;
          
        case 4:
          printf("\nWhat temperature you want to put ? (-50 to 60)\n");
          scanf("%d",&temp);
          if(temp>0)
              numtoChar(&T4[5],temp,2);
          else{
              T4[3] = '-';
              numtoChar(&T4[5],-temp,2);
          }
          
          printf("\nWhat humidity you want to put ? (0 to 100)\n");
          scanf("%d",&hum);
          numtoChar(&T4[9],hum,3);
          
          printf("\nWhat CO2 you want to put ? (400 to 20000)\n");
          scanf("%d",&CO2);
          numtoChar(&T4[15],CO2,5);
          
          numtoChar(&T4[18],(CheckSum(&T4[1],15)+CheckError),3);
          for(int i=0; i<20; i++) 
              rxChar(T4[i]);
              
          break;
          
        case 5:
          numtoChar(&T5[4],(CheckSum(&T5[1],1)+CheckError),3);
          for(int i=0; i<6; i++) 
              rxChar(T5[i]);
          break;
        
        case 6:
          numtoChar(&T6[4],(CheckSum(&T6[1],1)+CheckError),3);
          for(int i=0; i<6; i++) 
              rxChar(T6[i]);
          break;
    }
          
    getRxBuf(rx,getRxBufLen());
    printf("\nValues in RxBuffer : %s",rx);
    
    int x = cmdProc();
    ErrorCode(x);
    getTxBuf(tx,getTxBufLen());
       
    printf("Values of TxBuffer : %s",tx);
           
    if(x==END_L){          
    temperature = getTemp();
    humidity = getHum();
    co2 = getCO2();
    
    printf("\n\nLAST 20 TEMPERATURE VALUES\n");
    for(unsigned int* i = temperature; i<(temperature+MAX_SIZE); i++){
       printf("%d ",*i); 
    }
    printf("\n\nLAST 20 HUMIDITY VALUES\n");
    for(unsigned int* i = humidity; i<(humidity+MAX_SIZE); i++){
       printf("%d ",*i); 
    }
    printf("\n\nLAST 20 CO2 VALUES\n");
    for(unsigned int* i = co2; i<(co2+MAX_SIZE); i++){
       printf("%d ",*i); 
    }
    }
    
    printf("\n\n------------------------------------------\n");
    
    }

}

*/