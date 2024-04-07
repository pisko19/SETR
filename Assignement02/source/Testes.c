#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "../header/Testes.h"
#include "../header/Uart.h"
#include "../header/unity.h" 

#define CheckError 0 //Change this value if you want to make a checksum error

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
    unsigned char testInput[11] = {'#', 'P', 't', '+', '2', '0', 'A', 'A', 'A', '!','\0'};
    unsigned char expectedRxBuffer[] = {'#', 'P', 't', '+', '2', '0', 'A', 'A', 'A', '!','\0'};
    unsigned char expectedTxBuffer[] = {'#', 'P', 't', '+', '2', '0', 'A', 'A', 'A', '!','\0'};
    unsigned char rxBuffer[UART_RX_SIZE];
    unsigned char txBuffer[UART_TX_SIZE];
    int result;
    
    // Initialize UART
    init();
    numtoChar(&testInput[8],(CheckSum(&testInput[1],5)+CheckError),3);
    numtoChar(&expectedRxBuffer[8],(CheckSum(&expectedRxBuffer[1],5)+CheckError),3);
    numtoChar(&expectedTxBuffer[8],(CheckSum(&expectedTxBuffer[1],5)+CheckError),3);

    // Call rxChar with test input
    for (unsigned int i = 0; i < sizeof(testInput); i++) {
        result = rxChar(testInput[i]);
        if (i < UART_TX_SIZE) {
            // Expecting END as long as buffer is not full
            TEST_ASSERT_EQUAL_INT(END, result);
        } else {
            // Expecting Size_Error when buffer is full
            TEST_ASSERT_EQUAL_INT(Size_Error, result);
        }
    }
    
    // Check the content of RxBuffer
    getRxBuf(rxBuffer, getRxBufLen());
    TEST_ASSERT_EQUAL_STRING_LEN(expectedRxBuffer, rxBuffer, sizeof(expectedRxBuffer));
    
    // Call cmdProc and assert its return value
    result = cmdProc();
    getTxBuf(txBuffer, getTxBufLen());
    
    if(CheckError == 0){
       TEST_ASSERT_EQUAL_INT(END, result);
       TEST_ASSERT_EQUAL_STRING_LEN(expectedTxBuffer, txBuffer, sizeof(expectedTxBuffer));
    }
    else{
       TEST_ASSERT_EQUAL_INT(CheckSum_Error, result);
       TEST_ASSERT_EQUAL_STRING_LEN("", txBuffer, sizeof(expectedTxBuffer));
    }
}  

void Teste_Proc_Temp(void){

    unsigned char testInput[11] = {'#','P','t','+','0','0','A','A','A','!','\0'};
    unsigned char expectedRxBuffer[] = {'#', 'P', 't', '+', '0', '0', 'A', 'A', 'A', '!','\0'};
    unsigned char expectedTxBuffer[] = {'#', 'P', 't', '+', '0', '0', 'A', 'A', 'A', '!','\0'};
    unsigned char rxBuffer[UART_RX_SIZE];
    unsigned char txBuffer[UART_TX_SIZE];
    int result,temperature;
    
    printf("\nTESTE TEMPERATURE:\n");
    
    while(1){
    memset(rxBuffer, '\0', UART_RX_SIZE);
    memset(txBuffer, '\0', UART_TX_SIZE);
    init();
       
    printf("\nWhat temperature you want to teste ? (100 to exit)\n");
    scanf("%d",&temperature);
    
    if(temperature == 100)
       break;
       
    if(temperature >= 0){
       // Adding the humidity value to the arrays
       testInput[3] = '+';
       expectedRxBuffer[3] = '+';
       expectedTxBuffer[3] = '+';
       numtoChar(&testInput[5],temperature,2);
       numtoChar(&expectedRxBuffer[5],temperature,2);
       numtoChar(&expectedTxBuffer[5],temperature,2);
    }
    else{
       // Adding the humidity value to the arrays
       testInput[3] = '-';
       expectedRxBuffer[3] = '-';
       expectedTxBuffer[3] = '-';
       numtoChar(&testInput[5],-temperature,2);
       numtoChar(&expectedRxBuffer[5],-temperature,2);
       numtoChar(&expectedTxBuffer[5],-temperature,2);
    }
      
    // Adding the checksum to the arrays
    numtoChar(&testInput[8],(CheckSum(&testInput[1],5)+CheckError),3);
    numtoChar(&expectedRxBuffer[8],(CheckSum(&expectedRxBuffer[1],5)+CheckError),3);
    numtoChar(&expectedTxBuffer[8],(CheckSum(&expectedTxBuffer[1],5)+CheckError),3);
      
    for (unsigned int i = 0; i < sizeof(testInput); i++) {
      result = rxChar(testInput[i]);
      if (i < UART_TX_SIZE) {
          // Expecting END as long as buffer is not full
          TEST_ASSERT_EQUAL_INT(END, result);
      } else {
          // Expecting Size_Error when buffer is full
          TEST_ASSERT_EQUAL_INT(Size_Error, result);
      }
    }
            
    getRxBuf(rxBuffer, getRxBufLen());
    TEST_ASSERT_EQUAL_STRING_LEN(expectedRxBuffer, rxBuffer, sizeof(expectedRxBuffer));
    
    result = cmdProc();
    getTxBuf(txBuffer, getTxBufLen());
    
    if(CheckError == 0){
       if(temperature >=-50 && temperature <=60){
           TEST_ASSERT_EQUAL_INT(END, result);
           TEST_ASSERT_EQUAL_STRING_LEN(expectedTxBuffer, txBuffer, sizeof(expectedTxBuffer));
           TEST_ASSERT_EQUAL_INT(temperature,(int)getInstantTemp());
       }   
       else{ 
           TEST_ASSERT_EQUAL_INT(ValueError, result);
           TEST_ASSERT_EQUAL_STRING_LEN("", txBuffer, sizeof(expectedTxBuffer));
           TEST_ASSERT_EQUAL_INT(-100,(int)getInstantTemp());
       }
    }
    else {
       TEST_ASSERT_EQUAL_INT(CheckSum_Error, result);
       TEST_ASSERT_EQUAL_STRING_LEN("", txBuffer, sizeof(expectedTxBuffer));
    }
         
    printf("\n------------------------------------------\n"
           "\nValues in RxBuffer : %s",rxBuffer);
              
    ErrorCode(result);
    
    printf("Values of TxBuffer : %s\n",txBuffer);
    if(result != END)
        printf("\nThe value of the temperature is incorrect !\n");
    else
        printf("\nThe temperature is %d ºC \n",getInstantTemp());
         
    printf("\n------------------------------------------\n");
    }  
}

void Teste_Proc_Hum(void){

    unsigned char testInput[11] = {'#','P','h','0','0','0','A','A','A','!','\0'};
    unsigned char expectedRxBuffer[] = {'#', 'P', 'h', '0', '0', '0', 'A', 'A', 'A', '!','\0'};
    unsigned char expectedTxBuffer[] = {'#', 'P', 'h', '0', '0', '0', 'A', 'A', 'A', '!','\0'};
    unsigned char rxBuffer[UART_RX_SIZE];
    unsigned char txBuffer[UART_TX_SIZE];
    int result,humidity;
    
    printf("\n\nTESTE HUMIDITY:\n");
    
    while(1){
       memset(rxBuffer, '\0', UART_RX_SIZE);
       memset(txBuffer, '\0', UART_TX_SIZE);
       init();
       
       printf("\nWhat humidity you want to teste ? (-1 to exit)\n");
       scanf("%d",&humidity);
       
       if(humidity == -1)
       break;
       
       // Adding the humidity value to the arrays
       numtoChar(&testInput[5],humidity,3);
       numtoChar(&expectedRxBuffer[5],humidity,3);
       numtoChar(&expectedTxBuffer[5],humidity,3);
       
       // Adding the checksum to the arrays
       numtoChar(&testInput[8],(CheckSum(&testInput[1],5)+CheckError),3);
       numtoChar(&expectedRxBuffer[8],(CheckSum(&expectedRxBuffer[1],5)+CheckError),3);
       numtoChar(&expectedTxBuffer[8],(CheckSum(&expectedTxBuffer[1],5)+CheckError),3);
        
       for (unsigned int i = 0; i < sizeof(testInput); i++) {
           result = rxChar(testInput[i]);
           if (i < UART_TX_SIZE) {
               // Expecting END as long as buffer is not full
               TEST_ASSERT_EQUAL_INT(END, result);
           } else {
               // Expecting Size_Error when buffer is full
               TEST_ASSERT_EQUAL_INT(Size_Error, result);
           }
       }
            
       getRxBuf(rxBuffer, getRxBufLen());
       TEST_ASSERT_EQUAL_STRING_LEN(expectedRxBuffer, rxBuffer, sizeof(expectedRxBuffer));
    
       result = cmdProc();
       getTxBuf(txBuffer, getTxBufLen());
       
       if(CheckError == 0){
          if(humidity >=0 && humidity <=100){
             TEST_ASSERT_EQUAL_INT(END, result);
             TEST_ASSERT_EQUAL_STRING_LEN(expectedTxBuffer, txBuffer, sizeof(expectedTxBuffer));
             TEST_ASSERT_EQUAL_INT(humidity,(int)getInstantHum());
          }   
          else{ 
             TEST_ASSERT_EQUAL_INT(ValueError, result);
             TEST_ASSERT_EQUAL_STRING_LEN("", txBuffer, sizeof(expectedTxBuffer));
             TEST_ASSERT_EQUAL_INT(-1,(int)getInstantHum());
          }
       }
       else {
          TEST_ASSERT_EQUAL_INT(CheckSum_Error, result);
          TEST_ASSERT_EQUAL_STRING_LEN("", txBuffer, sizeof(expectedTxBuffer));
       }
       
       printf("\n------------------------------------------\n"
              "\nValues in RxBuffer : %s",rxBuffer);
              
       ErrorCode(result);
    
       printf("Values of TxBuffer : %s\n",txBuffer);
       if(result != END)
          printf("\nThe value of the humidity is incorrect !\n");
       else
          printf("\nThe humidity is %d %% \n",getInstantHum());
         
       printf("\n------------------------------------------\n");
    }  
}

void Teste_Proc_CO2(void){

    unsigned char testInput[13] = {'#', 'P', 'c', '0', '0', '0', '0', '0', 'A', 'A', 'A', '!', '\0'};
    unsigned char expectedRxBuffer[] = {'#', 'P', 'c', '0', '0', '0', '0', '0', 'A', 'A', 'A', '!', '\0'};
    unsigned char expectedTxBuffer[] = {'#', 'P', 'c', '0', '0', '0', '0', '0', 'A', 'A', 'A', '!', '\0'};
    unsigned char rxBuffer[UART_RX_SIZE];
    unsigned char txBuffer[UART_TX_SIZE];
    int result,co2;
    
    printf("\n\nTESTE CO2:\n");
    
    while(1){
       memset(rxBuffer, '\0', UART_RX_SIZE);
       memset(txBuffer, '\0', UART_TX_SIZE);
       init();
       
       printf("\nWhat CO2 you want to teste ? (-1 to exit)\n");
       scanf("%d",&co2);
       
       if(co2 == -1)
       break;
       
       // Adding the CO2 value to the arrays
       numtoChar(&testInput[7],co2,5);
       numtoChar(&expectedRxBuffer[7],co2,5);
       numtoChar(&expectedTxBuffer[7],co2,5);
       
       // Adding the checksum to the arrays
       numtoChar(&testInput[10],(CheckSum(&testInput[1],7)+CheckError),3);
       numtoChar(&expectedRxBuffer[10],(CheckSum(&expectedRxBuffer[1],7)+CheckError),3);
       numtoChar(&expectedTxBuffer[10],(CheckSum(&expectedTxBuffer[1],7)+CheckError),3);
        
       for (unsigned int i = 0; i < sizeof(testInput); i++) {
           result = rxChar(testInput[i]);
           if (i < UART_TX_SIZE) {
               // Expecting END as long as buffer is not full
               TEST_ASSERT_EQUAL_INT(END, result);
           } else {
               // Expecting Size_Error when buffer is full
               TEST_ASSERT_EQUAL_INT(Size_Error, result);
           }
       }
            
       getRxBuf(rxBuffer, getRxBufLen());
       TEST_ASSERT_EQUAL_STRING_LEN(expectedRxBuffer, rxBuffer, sizeof(expectedRxBuffer));
    
       result = cmdProc();
       getTxBuf(txBuffer, getTxBufLen());
       
       if(CheckError == 0){
          if(co2 >=400 && co2 <=20000){
             TEST_ASSERT_EQUAL_INT(END, result);
             TEST_ASSERT_EQUAL_STRING_LEN(expectedTxBuffer, txBuffer, sizeof(expectedTxBuffer));
             TEST_ASSERT_EQUAL_INT(co2,(int)getInstantCO2());
          }   
          else{ 
           TEST_ASSERT_EQUAL_INT(ValueError, result);
           TEST_ASSERT_EQUAL_STRING_LEN("", txBuffer, sizeof(expectedTxBuffer));
           TEST_ASSERT_EQUAL_INT(0,(int)getInstantCO2());
          }
       }
       else {
          TEST_ASSERT_EQUAL_INT(CheckSum_Error, result);
          TEST_ASSERT_EQUAL_STRING_LEN("", txBuffer, sizeof(expectedTxBuffer));
       }
       
       printf("\n------------------------------------------\n"
              "\nValues in RxBuffer : %s",rxBuffer);
       ErrorCode(result);
    
       printf("Values of TxBuffer : %s\n",txBuffer);
       if(result != END)
          printf("\nThe value of the CO2 is incorrect !\n");
       else
          printf("\nThe CO2 is %d ppm \n",getInstantCO2());
         
       printf("\n------------------------------------------\n");
    }  
}

void Teste_Proc_A(void){

    unsigned char T[6][21] = {{'#','A','t','+','0','0','h','0','0','0','c','0','0','0','0','0','A','A','A','!','\0'},
                              {'#','A','t','+','0','0','c','0','0','0','0','0','h','0','0','0','A','A','A','!','\0'},
                              {'#','A','h','0','0','0','c','0','0','0','0','0','t','+','0','0','A','A','A','!','\0'},
                              {'#','A','h','0','0','0','t','+','0','0','c','0','0','0','0','0','A','A','A','!','\0'},
                              {'#','A','c','0','0','0','0','0','t','+','0','0','h','0','0','0','A','A','A','!','\0'},
                              {'#','A','c','0','0','0','0','0','h','0','0','0','t','+','0','0','A','A','A','!','\0'}};
    unsigned char testInput[21];
    unsigned char expectedRxBuffer[21];
    unsigned char expectedTxBuffer[21];
    
    unsigned char rxBuffer[UART_RX_SIZE];
    unsigned char txBuffer[UART_TX_SIZE];
    int temperature,humidity,co2,format,result;
    
    printf("\nWhat CO2 you want to teste ? (between 400 and 20000)\n");
    scanf("%d",&co2);
    printf("\nWhat humidity you want to teste ? (between 0 and 100)\n");
    scanf("%d",&humidity);
    printf("\nWhat temperature you want to teste ? (between -50 and 60)\n");
    scanf("%d",&temperature);
       
       
    while(1){
       memset(rxBuffer, '\0', UART_RX_SIZE);
       memset(txBuffer, '\0', UART_TX_SIZE);
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
          
       for(unsigned int i=0;i<sizeof(testInput);i++){
           testInput[i] = T[format-1][i];
           expectedRxBuffer[i] = T[format-1][i];
           expectedTxBuffer[i] = T[format-1][i];
       }
       TEST_ASSERT_EQUAL_STRING_LEN(expectedRxBuffer, T[format-1], sizeof(expectedTxBuffer));
       TEST_ASSERT_EQUAL_STRING_LEN(expectedTxBuffer, T[format-1], sizeof(expectedTxBuffer));
       TEST_ASSERT_EQUAL_STRING_LEN(testInput, T[format-1], sizeof(expectedTxBuffer));
       
       for(unsigned int i=0;i<sizeof(testInput);i++){
           if(testInput[i] == 't'){
              if(temperature>0){
                 numtoChar(&testInput[i+3],temperature,2);
                 numtoChar(&expectedRxBuffer[i+3],temperature,2);
                 numtoChar(&expectedTxBuffer[i+3],temperature,2);
              }
              else{
                 testInput[i+1] = '-';
                 numtoChar(&testInput[i+3],-temperature,2);
                 numtoChar(&expectedRxBuffer[i+3],-temperature,2);
                 numtoChar(&expectedTxBuffer[i+3],-temperature,2);
              }
           }
           else if(testInput[i] == 'h'){
              numtoChar(&testInput[i+3],humidity,3);
              numtoChar(&expectedRxBuffer[i+3],humidity,3);
              numtoChar(&expectedTxBuffer[i+3],humidity,3);
           }  
           else if(testInput[i] == 'c'){
              numtoChar(&testInput[i+5],co2,5);
              numtoChar(&expectedRxBuffer[i+5],co2,5);
              numtoChar(&expectedTxBuffer[i+5],co2,5);
           }
       }
       
       numtoChar(&testInput[18],(CheckSum(&testInput[1],15)+CheckError),3);
       numtoChar(&expectedRxBuffer[18],(CheckSum(&expectedRxBuffer[1],15)+CheckError),3);
       numtoChar(&expectedTxBuffer[18],(CheckSum(&expectedTxBuffer[1],15)+CheckError),3);
       
       for (unsigned int i = 0; i < sizeof(testInput); i++) {
           result = rxChar(testInput[i]);
           if (i < UART_TX_SIZE) {
               // Expecting END as long as buffer is not full
               TEST_ASSERT_EQUAL_INT(END, result);
           } else {
               // Expecting Size_Error when buffer is full
               TEST_ASSERT_EQUAL_INT(Size_Error, result);
           }
       }
       
       getRxBuf(rxBuffer, getRxBufLen());
       TEST_ASSERT_EQUAL_STRING_LEN(expectedRxBuffer, rxBuffer, sizeof(expectedRxBuffer));
    
       result = cmdProc();
       
       getTxBuf(txBuffer,getTxBufLen());
       
       if(CheckError == 0){
          if(temperature >=-50 && temperature <= 60 && humidity >=0 && humidity <= 100 && co2 >=400 && co2 <=20000){
             TEST_ASSERT_EQUAL_INT(END, result);
             TEST_ASSERT_EQUAL_STRING_LEN(expectedTxBuffer, txBuffer, sizeof(expectedTxBuffer));
             TEST_ASSERT_EQUAL_INT(co2,(int)getInstantCO2());
             TEST_ASSERT_EQUAL_INT(humidity,(int)getInstantHum());
             TEST_ASSERT_EQUAL_INT(temperature,(int)getInstantTemp());
          }
          else{
             TEST_ASSERT_EQUAL_INT(ValueError, result);
             TEST_ASSERT_EQUAL_STRING_LEN("", txBuffer, sizeof(expectedTxBuffer));
             TEST_ASSERT_EQUAL_INT(0,(int)getInstantCO2());
             TEST_ASSERT_EQUAL_INT(-1,(int)getInstantHum());
             TEST_ASSERT_EQUAL_INT(-100,(int)getInstantTemp());
          }
       }
       else {
          TEST_ASSERT_EQUAL_INT(CheckSum_Error, result);
          TEST_ASSERT_EQUAL_STRING_LEN("", txBuffer, sizeof(expectedTxBuffer));
       }
       
       printf("\n------------------------------------------\n"
              "\nValues in RxBuffer : %s",rxBuffer);
                        
       ErrorCode(result);
      
       printf("Values of TxBuffer : %s\n",txBuffer);
       
       if(result != END){
          printf("\nOne of these values are wrong\n");
       }
       else{
       for(unsigned int i=0;i<sizeof(testInput);i++){
           if(testInput[i] == 't')
              printf("\nThe temperature is %d ºC",getInstantTemp());
              
           else if(testInput[i] == 'h')
              printf("\nThe humidity is %d %% ",getInstantHum());
              
           else if(testInput[i] == 'c')
              printf("\nThe CO2 is %d ppm",getInstantCO2());
       }
       }
       printf("\n\n------------------------------------------\n");
    }
}


void Teste_Proc_All(void){
    
    unsigned char testInput1[11] = {'#','P','t','+','0','0','A','A','A','!','\0'};
    unsigned char testInput2[11] = {'#','P','h','0','0','0','A','A','A','!','\0'};
    unsigned char testInput3[13] = {'#','P','c','0','0','0','0','0','A','A','A','!','\0'};
    unsigned char testInput4[21] = {'#','A','t','+','0','0','h','0','0','0','c','0','0','0','0','0','A','A','A','!','\0'};
    unsigned char testInput5[7] = {'#','L','A','A','A','!','\0'};
    unsigned char testInput6[7] = {'#','R','A','A','A','!','\0'};
    
    unsigned char expectedRxBuffer[21];
    unsigned char expectedTxBuffer[21];
    int expectedTemperature[20] = {-100,-100,-100,-100,-100,-100,-100,-100,-100,-100,-100,-100,-100,-100,-100,-100,-100,-100,-100,-100};
    int expectedHumidity[20] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int expectedCO2[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    
    unsigned char rxBuffer[UART_RX_SIZE];
    unsigned char txBuffer[UART_TX_SIZE];
    int* temperature;
    int* humidity;
    int* co2;
    int choice,result,temp,hum,CO2;
    unsigned int tempLenght,humLenght,CO2Lenght;
    
    choice = -1;
    tempLenght = 0;
    humLenght = 0;
    CO2Lenght = 0;
    
    init();
    while(choice!=0){
    memset(rxBuffer, '\0', UART_RX_SIZE);
    memset(txBuffer, '\0', UART_TX_SIZE);
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
       // JUST TEMPERATURE VALUE
       case 1:
          printf("\nWhat temperature you want to put ? (-50 to 60)\n");
          scanf("%d",&temp);
          if(temp>0){
              testInput1[3] = '+';
              numtoChar(&testInput1[5],temp,2);
          }
          else{
              testInput1[3] = '-';
              numtoChar(&testInput1[5],-temp,2);
          }
          numtoChar(&testInput1[8],(CheckSum(&testInput1[1],5)+CheckError),3);
          
          for(unsigned int i=0; i<sizeof(testInput1); i++){
              expectedRxBuffer[i] = testInput1[i];
              expectedTxBuffer[i] = testInput1[i];
              rxChar(testInput1[i]);
          }
          getRxBuf(rxBuffer,getRxBufLen());
          TEST_ASSERT_EQUAL_STRING_LEN(expectedRxBuffer, rxBuffer, sizeof(expectedRxBuffer));
          result = cmdProc();
          getTxBuf(txBuffer,getTxBufLen());
          
          if(CheckError == 0){
             if(temp>=-50 && temp<=60){
                addValue(expectedTemperature,&tempLenght,temp); 
                TEST_ASSERT_EQUAL_INT(END, result);
                TEST_ASSERT_EQUAL_STRING_LEN(expectedTxBuffer, txBuffer, sizeof(expectedTxBuffer));
             }   
             else{
                TEST_ASSERT_EQUAL_INT(ValueError, result);
                TEST_ASSERT_EQUAL_STRING_LEN("", txBuffer, sizeof(expectedTxBuffer));
             }
             TEST_ASSERT_EQUAL_INT(expectedTemperature[0],getInstantTemp());
          }
          else {
             TEST_ASSERT_EQUAL_INT(CheckSum_Error, result);
             TEST_ASSERT_EQUAL_STRING_LEN("", txBuffer, sizeof(expectedTxBuffer));
          }
          break;
        
        // JUST HUMIDITY VALUE  
        case 2:
          printf("\nWhat humidity you want to put ? (0 to 100)\n");
          scanf("%d",&hum);
          numtoChar(&testInput2[5],hum,3);
          numtoChar(&testInput2[8],(CheckSum(&testInput2[1],5)+CheckError),3);
          for(unsigned int i=0; i<sizeof(testInput2); i++) {
              expectedRxBuffer[i] = testInput2[i];
              expectedTxBuffer[i] = testInput2[i];
              rxChar(testInput2[i]);
          }
          getRxBuf(rxBuffer,getRxBufLen());
          TEST_ASSERT_EQUAL_STRING_LEN(expectedRxBuffer, rxBuffer, sizeof(expectedRxBuffer));
          result = cmdProc();
          getTxBuf(txBuffer,getTxBufLen());
          
          if(CheckError == 0){
             if(hum>=0 && hum<=100){
                addValue(expectedHumidity,&humLenght,hum); 
                TEST_ASSERT_EQUAL_INT(END, result);
                TEST_ASSERT_EQUAL_STRING_LEN(expectedTxBuffer, txBuffer, sizeof(expectedTxBuffer));
             }   
             else{
                TEST_ASSERT_EQUAL_INT(ValueError, result);
                TEST_ASSERT_EQUAL_STRING_LEN("", txBuffer, sizeof(expectedTxBuffer));
             }
             TEST_ASSERT_EQUAL_INT(expectedHumidity[0],getInstantHum());
          }
          else {
             TEST_ASSERT_EQUAL_INT(CheckSum_Error, result);
             TEST_ASSERT_EQUAL_STRING_LEN("", txBuffer, sizeof(expectedTxBuffer));
          }
          break;
          
        // JUST CO2 VALUE
        case 3:
          printf("\nWhat CO2 you want to put ? (400 to 20000)\n");
          scanf("%d",&CO2);
          numtoChar(&testInput3[7],CO2,5);
          numtoChar(&testInput3[10],(CheckSum(&testInput3[1],7)+CheckError),3);
          for(unsigned int i=0; i<sizeof(testInput3); i++){
              expectedRxBuffer[i] = testInput3[i];
              expectedTxBuffer[i] = testInput3[i];
              rxChar(testInput3[i]);
          }
          getRxBuf(rxBuffer,getRxBufLen());
          TEST_ASSERT_EQUAL_STRING_LEN(expectedRxBuffer, rxBuffer, sizeof(expectedRxBuffer));
          result = cmdProc();
          getTxBuf(txBuffer,getTxBufLen());
          
          if(CheckError == 0){
             if(CO2>=400 && CO2<=20000){
                addValue(expectedCO2,&CO2Lenght,CO2); 
                TEST_ASSERT_EQUAL_INT(END, result);
                TEST_ASSERT_EQUAL_STRING_LEN(expectedTxBuffer, txBuffer, sizeof(expectedTxBuffer));
             }   
             else{
                TEST_ASSERT_EQUAL_INT(ValueError, result);
                TEST_ASSERT_EQUAL_STRING_LEN("", txBuffer, sizeof(expectedTxBuffer));
             }
             TEST_ASSERT_EQUAL_INT(expectedCO2[0],getInstantCO2());
          }
          else {
             TEST_ASSERT_EQUAL_INT(CheckSum_Error, result);
             TEST_ASSERT_EQUAL_STRING_LEN("", txBuffer, sizeof(expectedTxBuffer));
          }
          break;
          
        // ALL 3 TYPE OF VALUES
        case 4:
          printf("\nWhat temperature you want to put ? (-50 to 60)\n");
          scanf("%d",&temp);
          if(temp>0)
              numtoChar(&testInput4[5],temp,2);
          else{
              testInput4[3] = '-';
              numtoChar(&testInput4[5],-temp,2);
          }
          
          printf("\nWhat humidity you want to put ? (0 to 100)\n");
          scanf("%d",&hum);
          numtoChar(&testInput4[9],hum,3);
          
          printf("\nWhat CO2 you want to put ? (400 to 20000)\n");
          scanf("%d",&CO2);
          numtoChar(&testInput4[15],CO2,5);
          
          numtoChar(&testInput4[18],(CheckSum(&testInput4[1],15)+CheckError),3);
          for(unsigned int i=0; i<sizeof(testInput4); i++){
              expectedRxBuffer[i] = testInput4[i];
              expectedTxBuffer[i] = testInput4[i];
              rxChar(testInput4[i]);
          }    
          
          getRxBuf(rxBuffer,getRxBufLen());
          TEST_ASSERT_EQUAL_STRING_LEN(expectedRxBuffer, rxBuffer, sizeof(expectedRxBuffer));
          result = cmdProc();
          getTxBuf(txBuffer,getTxBufLen());
          
          if(CheckError == 0){
             if(temp >=-50 && temp <= 60 && hum >=0 && hum<= 100 && CO2 >=400 && CO2 <=20000){
                addValue(expectedCO2,&CO2Lenght,CO2); 
                addValue(expectedHumidity,&humLenght,hum); 
                addValue(expectedTemperature,&tempLenght,temp); 
                TEST_ASSERT_EQUAL_INT(END, result);
                TEST_ASSERT_EQUAL_STRING_LEN(expectedTxBuffer, txBuffer, sizeof(expectedTxBuffer));
             }
             else{
                TEST_ASSERT_EQUAL_INT(ValueError, result);
                TEST_ASSERT_EQUAL_STRING_LEN("", txBuffer, sizeof(expectedTxBuffer));
             }
             TEST_ASSERT_EQUAL_INT(expectedTemperature[0],getInstantTemp());
             TEST_ASSERT_EQUAL_INT(expectedHumidity[0],getInstantHum());
             TEST_ASSERT_EQUAL_INT(expectedCO2[0],getInstantCO2());
          }
          else {
             TEST_ASSERT_EQUAL_INT(CheckSum_Error, result);
             TEST_ASSERT_EQUAL_STRING_LEN("", txBuffer, sizeof(expectedTxBuffer));
          }
          break;
          
        // THE LAST 20 VALUES OF ALL TYPE OF VALUES
        case 5:
          numtoChar(&testInput5[4],(CheckSum(&testInput5[1],1)+CheckError),3);
          for(unsigned int i=0; i<sizeof(testInput5); i++){
              expectedRxBuffer[i] = testInput5[i];
              expectedTxBuffer[i] = testInput5[i];
              rxChar(testInput5[i]);
          }
          
          getRxBuf(rxBuffer,getRxBufLen());
          TEST_ASSERT_EQUAL_STRING_LEN(expectedRxBuffer, rxBuffer, sizeof(expectedRxBuffer));
          result = cmdProc();
          getTxBuf(txBuffer,getTxBufLen());
          
          if(CheckError == 0){
             TEST_ASSERT_EQUAL_INT(END_L, result);
             TEST_ASSERT_EQUAL_STRING_LEN(expectedTxBuffer, txBuffer, sizeof(expectedTxBuffer));
          }
          else {
             TEST_ASSERT_EQUAL_INT(CheckSum_Error, result);
             TEST_ASSERT_EQUAL_STRING_LEN("", txBuffer, sizeof(expectedTxBuffer));
          }
          temperature = getTemp();
          humidity = getHum();
          co2 = getCO2();
          
          for(int *i = temperature, *j = humidity, *k = co2,
              *i2 = expectedTemperature, *j2 = expectedHumidity, *k2 = expectedCO2
              ; i<(temperature+MAX_SIZE); i++,j++,k++,i2++,j2++,k2++){
              
              TEST_ASSERT_EQUAL_INT(*i2, *i); 
              TEST_ASSERT_EQUAL_INT(*j2, *j); 
              TEST_ASSERT_EQUAL_INT(*k2, *k); 
          }
          
          break;
        
        case 6:
          numtoChar(&testInput6[4],(CheckSum(&testInput6[1],1)+CheckError),3);
          for(unsigned int i=0; i<sizeof(testInput6); i++){
              expectedRxBuffer[i] = testInput6[i];
              expectedTxBuffer[i] = testInput6[i];
              rxChar(testInput6[i]);
          }
          
          getRxBuf(rxBuffer,getRxBufLen());
          TEST_ASSERT_EQUAL_STRING_LEN(expectedRxBuffer, rxBuffer, sizeof(expectedRxBuffer));
          result = cmdProc();
          getTxBuf(txBuffer,getTxBufLen());
          
          if(CheckError == 0){
             TEST_ASSERT_EQUAL_INT(END, result);
             TEST_ASSERT_EQUAL_STRING_LEN(expectedTxBuffer, txBuffer, sizeof(expectedTxBuffer));
          }
          else {
             TEST_ASSERT_EQUAL_INT(CheckSum_Error, result);
             TEST_ASSERT_EQUAL_STRING_LEN("", txBuffer, sizeof(expectedTxBuffer));
          }
          temperature = getTemp();
          humidity = getHum();
          co2 = getCO2();
          
          for(int i = 0;i<20;i++){
             expectedTemperature[i] = -100;
             expectedHumidity[i] = -1;
             expectedCO2[i] = 0;
          }
          
          for(int *i = temperature, *j = humidity, *k = co2,
             *i2 = expectedTemperature, *j2 = expectedHumidity, *k2 = expectedCO2
             ; i<(temperature+MAX_SIZE); i++,j++,k++,i2++,j2++,k2++){
              
             TEST_ASSERT_EQUAL_INT(*i2, *i); 
             TEST_ASSERT_EQUAL_INT(*j2, *j); 
             TEST_ASSERT_EQUAL_INT(*k2, *k); 
          }
          break;
    }
    
    printf("\nValues in RxBuffer : %s",rxBuffer);
    ErrorCode(result);
    printf("Values of TxBuffer : %s",txBuffer);
           
    if(result==END_L){
       printf("\n\nLAST 20 TEMPERATURE VALUES (ºC):\n");
       for(int* i = temperature; i<(temperature+MAX_SIZE); i++){
          if(*i != -100){
             printf("%d ",*i); 
          }
       }
       printf("\n\nLAST 20 HUMIDITY VALUES (%%):\n");
       for(int* i = humidity; i<(humidity+MAX_SIZE); i++){
          if(*i != -1){
             printf("%d ",*i); 
          }
       }
       printf("\n\nLAST 20 CO2 VALUES (ppm):\n");
       for(int* i = co2; i<(co2+MAX_SIZE); i++){
          if(*i != 0){
             printf("%d ",*i); 
          }
       }
    }
    
    printf("\n\n------------------------------------------\n");
    
    }
}
