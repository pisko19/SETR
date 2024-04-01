#include <stdio.h>
#include <string.h>

#include "../header/Uart.h"

static unsigned char RxBuffer[UART_RX_SIZE];
static unsigned char TxBuffer[UART_TX_SIZE];
static unsigned char RxBufferLen = 0;
static unsigned char TxBufferLen = 0;
static int temp[MAX_SIZE];
static int hum[MAX_SIZE];
static int co2[MAX_SIZE];
static unsigned int tempIndex = 0;
static unsigned int humIndex = 0;
static unsigned int co2Index = 0;


int rxChar(unsigned char character){

  if(RxBufferLen < UART_RX_SIZE){
     RxBuffer[RxBufferLen] = character;
     RxBufferLen++;
     return END;
  }
  return Size_Error;

}

int txChar(unsigned char character){

  if(TxBufferLen < UART_TX_SIZE){
     TxBuffer[TxBufferLen] = character;
     TxBufferLen++;
     return END;
  }
  return Size_Error;
}

void ResetRxChar(void){

  memset(RxBuffer, 0, UART_RX_SIZE); // Reset RxBuffer
  RxBufferLen = 0; // Reset RxBufferLen
}

void ResetTxChar(void){

  memset(TxBuffer, 0, UART_RX_SIZE); // Reset RxBuffer
  TxBufferLen = 0; // Reset RxBufferLen

}

int getTxBuf(unsigned char *buf,int len){
  if(TxBufferLen == 0){
     return Len_Error; 
  }
  
  if(len > 0){
     memcpy(buf,TxBuffer,len);
     buf[len] = '\0';
     memmove(TxBuffer, TxBuffer+len, sizeof(TxBuffer)-len);
     TxBuffer[sizeof(TxBuffer)-len] = '\0';
     return END;
  }
  else{
     return Len_Error;
  }
  
}

unsigned int CheckSum(unsigned char* buf, int nbytes){
  unsigned int sum = 0;
  
  for(unsigned char* i = buf;i < buf+nbytes;i++){
      sum += (unsigned int)(*i);
      //printf("\n%c %d",*i,(unsigned int)(*i));
  }
  
  return sum;

}

void addValue(int *arr, int *size, int value){
   
   for(int i = *size; i>0; i--){
      arr[i] = arr[i-1];
   }
   arr[0] = value;
   
   if(*size < MAX_SIZE-1){
      (*size)++;
   }


}
int cmdProc(void){

  int i;
  unsigned char* action;
  unsigned int check;
  
  if(RxBufferLen == 0){
     return Len_Error;
  }
  
  for(i=0; i<RxBufferLen; i++){
     if(RxBuffer[i] == SOS){
        break;
     }
  }
  if(i < RxBufferLen){
    switch(RxBuffer[i+1]){
          case 'P':
              // See what is the category (temperature, humidity, CO2)
              action = &RxBuffer[i+2];
              
              // Case Temperature
              if (*action == 't'){
                 // Calculate the CheckSum
                 check = CheckSum(&RxBuffer[i+1],5);
                 
                 // Calculate the temperature
                 int x = 10*(RxBuffer[i+4] - '0') + RxBuffer[i+5] - '0';
                 
                 // Verify if is negative
                 if(RxBuffer[i+3] == '-')
                    x = -x;
                 
                 // Verify the value range
                 if(x > 60 || x < -50)
                    return ValueError;
             
                 // Verify the existence of the End of Sentence 
                 if(RxBuffer[i+6] != EOS)
                    return EOS_Error;
                 
                 // Add the temperature to the temperature array
                 addValue(&temp,&tempIndex,x);
                 
                 // Send the chars to the TxBuffer with the CheckSum byte
                 for(int i=0;i<RxBufferLen;i++){
                    if(i==RxBufferLen-1){  
                    txChar((unsigned char)(check));
                    }
                    else {
                      txChar((unsigned char)(RxBuffer[i]));
                    }
                 }
                 
                 txChar((unsigned char)(RxBuffer[RxBufferLen-1]));
                 return END;
              }
              // Case Humidity
              else if (*action == 'h'){
                 // Calculate the CheckSum
                 check = CheckSum(&RxBuffer[i+1],5);
                 
                 // Calculate the humidity
                 int x = 100*(RxBuffer[i+3] - '0') + 10*(RxBuffer[i+4] - '0') + RxBuffer[i+5] - '0';
                 
                 // Verify the value range
                 if(x > 100 || x < 0)
                    return ValueError;
                 
                 // Verify the existence of the End of Sentence
                 if(RxBuffer[i+6] != EOS)
                    return EOS_Error;
                 
                 // Add the humidity to the humidity array
                 addValue(&hum,&humIndex,x);
                 
                 // Send the chars to the TxBuffer with the CheckSum byte
                 for(int i=0;i<RxBufferLen;i++){
                    if(i==RxBufferLen-1){  
                    txChar((unsigned char)(check));
                    }
                    else {
                      txChar((unsigned char)(RxBuffer[i]));
                    }
                 }
                 txChar((unsigned char)(RxBuffer[RxBufferLen-1]));
                 return END;
              }
              
              // Case CO2
              else if (*action == 'c'){
                 // Calculate the CheckSum
                 check = CheckSum(&RxBuffer[i+1],7);
                 
                 // Calculate the CO2
                 int x = 10000*(RxBuffer[i+3] - '0') + 1000*(RxBuffer[i+4] - '0') + 100*(RxBuffer[i+5] - '0') + 10*(RxBuffer[i+6] - '0') + RxBuffer[i+7] - '0';
                 
                 // Verify the value range
                 if(x > 20000 || x < 400)
                    return ValueError;
                 
                 // Verify the existence of the End of Sentence
                 if(RxBuffer[i+8] != EOS)
                    return EOS_Error;
                 
                 // Add the CO2 to the CO2 array
                 addValue(&co2,&co2Index,x);     
                 
                 // Send the chars to the TxBuffer with the CheckSum byte
                 for(int i=0;i<RxBufferLen;i++){
                    if(i==RxBufferLen-1){  
                    txChar((unsigned char)(check));
                    }
                    else {
                      txChar((unsigned char)(RxBuffer[i]));
                    }
                 }
                 txChar((unsigned char)(RxBuffer[RxBufferLen-1]));
                 return END;
              }
              
              else
                 return CMD_Error;
              
          case 'A':
              // Verify the existence of the End of Sentence
              if(RxBuffer[i+16] != EOS)
                 return EOS_Error;
                 
              action = &RxBuffer[i+2];
              while(*action != '!'){
                 if(*action == 't'){
                   
                   // Calculate the temperature
                   int x = 10*(*(action+2) - '0') + *(action+3) - '0';
                 
                   // Verify if is negative
                   if(*(action+1) == '-')
                      x = -x;
                 
                   // Verify the value range
                 if(x > 60 || x < -50)
                    return ValueError;
                    
                   // Add the temperature to the temperature array
                   addValue(&temp,&tempIndex,x);
                 
                   action += 4;
                 }
                 else if(*action == 'h'){
                   
                   // Calculate the humidity
                   int x = 100*(*(action+1) - '0') + 10*(*(action+2) - '0') + *(action+3) - '0';
                 
                   // Verify the value range
                   if(x > 100 || x < 0)
                      return ValueError;
                   
                   // Add the humidity to the humidity array
                   addValue(&hum,&humIndex,x);
                 
                   action += 4;
                    
                 }
                 else if(*action == 'c'){
                   
                   // Calculate the CO2
                   int x = 10000*(*(action+1) - '0') + 1000*(*(action+2) - '0') + 100*(*(action+3) - '0') + 10*(*(action+4) - '0') + *(action+5) - '0';
                   
                   // Verify the value range
                   if(x > 20000 || x < 400)
                      return ValueError;
                   
                   // Add the CO2 to the CO2 array
                   addValue(&co2,&co2Index,x);  
                 
                   action += 6;
                
                 }
                 else
                   return CMD_Error;
              
             }
             check = CheckSum(&RxBuffer[i+1],15);
             for(int i=0;i<RxBufferLen;i++){
                    if(i==RxBufferLen-1){  
                    txChar((unsigned char)(check));
                    }
                    else {
                      txChar((unsigned char)(RxBuffer[i]));
                    }
                 }
             txChar((unsigned char)(RxBuffer[RxBufferLen-1]));
             return END;
          
          case 'L':
             
          case 'R':  
          
          default :
     
     
     }
  }
}

