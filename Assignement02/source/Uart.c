#include <stdio.h>
#include <string.h>

#include "../header/Uart.h"

static unsigned int hum[MAX_SIZE];
static unsigned int co2[MAX_SIZE];
static unsigned int temp[MAX_SIZE];
static unsigned char RxBuffer[UART_RX_SIZE];
static unsigned char TxBuffer[UART_TX_SIZE];
static unsigned char RxBufferLen;
static unsigned char TxBufferLen;
static unsigned int tempIndex;
static unsigned int humIndex;
static unsigned int co2Index;

void init(void){
   tempIndex = 0;
   humIndex = 0;
   co2Index = 0;
   ResetRxChar();
   ResetTxChar();
   for(int i = 0;i<MAX_SIZE;i++){
      temp[i] = -100;
      hum[i] = -1;
      co2[i] = 0;
   }
}

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
  memset(RxBuffer, 0, UART_RX_SIZE);
  RxBufferLen = 0;
}

void ResetTxChar(void){
  memset(TxBuffer, 0, UART_TX_SIZE);
  TxBufferLen = 0;
}

int getTxBufLen(void){
  if(TxBufferLen <= UART_TX_SIZE)
     return TxBufferLen;
  else
     return Size_Error;
}

int getTxBuf(unsigned char *buf,int len){
  if(TxBufferLen == 0)
     return Size_Error;
     
  if(len > 0){
     memcpy(buf,TxBuffer,len);
     buf[len] = '\0';
     memmove(TxBuffer, TxBuffer+len, TxBufferLen-len);
     TxBufferLen-=len;
     TxBuffer[TxBufferLen] = '\0';
    
     return END;
  }
  else
     return Len_Error;
}

int getRxBufLen(void){
  if(RxBufferLen <= UART_RX_SIZE)
     return RxBufferLen;
  else
     return Size_Error;
}

int getRxBuf(unsigned char *buf,int len){
  if(RxBufferLen == 0)
     return Size_Error; 
  
  if(len > 0){
     memcpy(buf,RxBuffer,len);
     buf[len] = '\0';
     return END;
  }
  else
     return Len_Error;
}

void erraseRxBuf(int len){
  memmove(RxBuffer, RxBuffer+len, RxBufferLen-len);
  RxBufferLen-=len;
  RxBuffer[RxBufferLen] = '\0';

}

unsigned int CheckSum(unsigned char* buf, int nbytes){
  unsigned int sum = 0;
  
  for(unsigned char* i = buf;i < buf+nbytes;i++){
      sum += (unsigned int)(*i);
      //printf("\n%c %d",*i,(unsigned int)(*i));
  }
  
  return (sum%256);

}
void addValue(unsigned int *arr, unsigned int size, int value) {
    for(unsigned int i = size; i > 0; i--) {
        arr[i] = arr[i-1];
    }
    arr[0] = (unsigned int)value;
   
    if(size < MAX_SIZE-1) {
        size++;
    }
}

unsigned int getInstantTemp(void){
   return temp[0];
}

unsigned int* getTemp(void){
   return temp;
}

unsigned int getInstantHum(void){
   return hum[0];
}

unsigned int* getHum(void){
   return hum;
}

unsigned int getInstantCO2(void){
   return co2[0];
}

unsigned int* getCO2(void){
   return co2;
}

void numtoChar(unsigned char *array, int num, int len) {
    int index = 0;
    //printf("\nTESTE -> %d\n",*array);
    // Extract digits from num and store them in reverse order
    while (index < len) {
        *(array - index) = (num % 10) + '0';
        //printf("\nTESTE -> %d \n",*(array - index));
        num /= 10;
        index++;
    }
   
}

int cmdProc(void){

  int i;
  unsigned char* action;
  unsigned int check;
  unsigned char copy[RxBufferLen];
  
  if(RxBufferLen == 0)
     return Len_Error;
  
  for(i=0; i<RxBufferLen; i++){
     if(RxBuffer[i] == SOS)
        break;
     else
        return SOS_Error;
  }
  
  if(i < RxBufferLen){
    switch(RxBuffer[i+1]){
          case 'P':
              // See what is the category (temperature, humidity, CO2)
              action = &RxBuffer[i+2];
              
              // Case Temperature
              if (*action == 't'){
                 check = CheckSum(&RxBuffer[i+1],5);
                 
                 int x = 10*(RxBuffer[i+4] - '0') + RxBuffer[i+5] - '0';
                 
                 if(RxBuffer[i+3] == '-')
                    x = -x;
                 
                 if(x > 60 || x < -50)
                    return ValueError;
                    
                 if(RxBuffer[i+6] != EOS)
                    return EOS_Error;
                 
                 addValue(temp,tempIndex,x);
                 
                 for(int i=0;i<RxBufferLen;i++){
                    if(i==RxBufferLen-1){
                       txChar('0');
                       txChar('0');
                       txChar('0');
                    }
                    else {
                      txChar((unsigned char)(RxBuffer[i]));
                    }
                 }
                 txChar((unsigned char)(RxBuffer[RxBufferLen-1]));
                 numtoChar(&TxBuffer[TxBufferLen-2],check,3);
                 
                 erraseRxBuf(RxBufferLen);
                 return END;
              }
              
              // CASE HUMIDITY
              else if (*action == 'h'){
                 check = CheckSum(&RxBuffer[i+1],5);
                 
                 int x = 100*(RxBuffer[i+3] - '0') + 10*(RxBuffer[i+4] - '0') + RxBuffer[i+5] - '0';
                 
                 if(x > 100 || x < 0)
                    return ValueError;
                 
                 if(RxBuffer[i+6] != EOS)
                    return EOS_Error;
                 
                 addValue(hum,humIndex,x);
                 
                 for(int i=0;i<RxBufferLen;i++){
                    if(i==RxBufferLen-1){
                       txChar('0');
                       txChar('0');
                       txChar('0');
                    }
                    else {
                      txChar((unsigned char)(RxBuffer[i]));
                    }
                 }
                 txChar((unsigned char)(RxBuffer[RxBufferLen-1]));
                 numtoChar(&TxBuffer[TxBufferLen-2],check,3);
                 
                 erraseRxBuf(RxBufferLen);
                 return END;
              }
              
              // Case CO2
              else if (*action == 'c'){
                 check = CheckSum(&RxBuffer[i+1],7);
                 
                 int x = 10000*(RxBuffer[i+3] - '0') + 1000*(RxBuffer[i+4] - '0') + 100*(RxBuffer[i+5] - '0') + 10*(RxBuffer[i+6] - '0') + RxBuffer[i+7] - '0';
                 
                 if(x > 20000 || x < 400)
                    return ValueError;
                 
                 if(RxBuffer[i+8] != EOS)
                    return EOS_Error;
                 
                 addValue(co2,co2Index,x);  
                 
                 for(int i=0;i<RxBufferLen;i++){
                    if(i==RxBufferLen-1){
                       txChar('0');
                       txChar('0');
                       txChar('0');
                    }
                    else {
                      txChar((unsigned char)(RxBuffer[i]));
                    }
                 }
                 txChar((unsigned char)(RxBuffer[RxBufferLen-1]));
                 numtoChar(&TxBuffer[TxBufferLen-2],check,3);
                 
                 erraseRxBuf(RxBufferLen);
                 return END;
              }
              
              else
                 return CMD_Error;
              
          case 'A':
              if(RxBuffer[i+16] != EOS)
                 return EOS_Error;
                 
              action = &RxBuffer[i+2];
              while(*action != '!'){
                 if(*action == 't'){
                   
                   int x = 10*(*(action+2) - '0') + *(action+3) - '0';
                 
                   if(*(action+1) == '-')
                      x = -x;
                 
                 if(x > 60 || x < -50)
                    return ValueError;
                    
                   addValue(temp,tempIndex,x);
                 
                   action += 4;
                 }
                 else if(*action == 'h'){
                   
                   int x = 100*(*(action+1) - '0') + 10*(*(action+2) - '0') + *(action+3) - '0';
                 
                   if(x > 100 || x < 0)
                      return ValueError;
                   
                   addValue(hum,humIndex,x);
                 
                   action += 4;
                    
                 }
                 else if(*action == 'c'){
                   
                   int x = 10000*(*(action+1) - '0') + 1000*(*(action+2) - '0') + 100*(*(action+3) - '0') + 10*(*(action+4) - '0') + *(action+5) - '0';
                   
                   if(x > 20000 || x < 400)
                      return ValueError;
                   
                   addValue(co2,co2Index,x);  
                 
                   action += 6;
                
                 }
                 else
                   return CMD_Error;
              
               }
               check = CheckSum(&RxBuffer[i+1],15);
               for(int i=0;i<RxBufferLen;i++){
                    if(i==RxBufferLen-1){
                       txChar('0');
                       txChar('0');
                       txChar('0');
                    }
                    else {
                      txChar((unsigned char)(RxBuffer[i]));
                    }
                 }
                 txChar((unsigned char)(RxBuffer[RxBufferLen-1]));
                 numtoChar(&TxBuffer[TxBufferLen-2],check,3);
                 
                 erraseRxBuf(RxBufferLen);
               return END;
          
          
          case 'L':
             check = CheckSum(&RxBuffer[i+1],1);
             for(int i=0;i<RxBufferLen;i++){
                    if(i==RxBufferLen-1){
                       txChar('0');
                       txChar('0');
                       txChar('0');
                    }
                    else {
                      txChar((unsigned char)(RxBuffer[i]));
                    }
                 }
             txChar((unsigned char)(RxBuffer[RxBufferLen-1]));
             numtoChar(&TxBuffer[TxBufferLen-2],check,3);
             erraseRxBuf(RxBufferLen);
             return END_L;
             
             
          case 'R':  
              tempIndex = 0;
              humIndex = 0;
              co2Index = 0;
              for(int i = 0;i<20;i++){
                  temp[i] = -100;
                  hum[i] = -1;
                  co2[i] = 0;
              }
              check = CheckSum(&RxBuffer[i+1],1);
              for(int i=0;i<RxBufferLen;i++){
                    if(i==RxBufferLen-1){
                       txChar('0');
                       txChar('0');
                       txChar('0');
                    }
                    else {
                      txChar((unsigned char)(RxBuffer[i]));
                    }
                 }
               txChar((unsigned char)(RxBuffer[RxBufferLen-1]));
               numtoChar(&TxBuffer[TxBufferLen-2],check,3);
               erraseRxBuf(RxBufferLen);
             return END;
             
          default :
             // Add default behavior here if needed
             return CMD_Error;
     }
  }
  else
     return Len_Error;
  
}
