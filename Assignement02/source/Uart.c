#include <stdio.h>
#include <string.h>
#include <math.h>
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
  }
  
  return (sum%256);

}
void addValue(unsigned int *arr, unsigned int* size, int value) {
    for(unsigned int i = *size; i > 0; i--) {
        arr[i] = arr[i-1];
    }
    arr[0] = (unsigned int)value;
   
    if(*size < MAX_SIZE-1) {
        (*size)++;
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

void ErrorCode(int x){
   printf("\nReturn of cmdProc  : %d ",x);
   switch(x){
      case 1:
         printf("(No error: read 20 values)\n");
         break;
      case 0:
         printf("(No error: end)\n");
         break;
      case -1:
         printf("(Error: One introduced value is wrong)\n");
         break;
      case -2:
         printf("(Error: Inexistence of the End of Sentence (EOS) '!' )\n");
         break;
      case -3:
         printf("(Error: Inexistence of the Start of Sentence (SOS) '#' )\n");
         break;
      case -4:
         printf("(Error: Argument lenght of get functions is incorret)\n");
         break;
      case -5:
         printf("(Error: Receiver or transmission lenght is wrong)\n");
         break;
      case -6:
         printf("(Error: Comand isn't 't', 'h' or 'c' )\n");
         break;
      case -7:
         printf("(Error: Checksum isn´t the same)\n");
         break;
   }
}
void numtoChar(unsigned char *array, int num, int len) {
    int index = 0;
    while (index < len) {
        *(array - index) = (num % 10) + '0';
        num /= 10;
        index++;
    }
   
}

unsigned int CharToNum(unsigned char *array, int len){ 
  int index = 0;  
  int sum = 0;
  int x;
  
  while(index < len){
    x = ((*(array-index))-'0') * pow(10,index);
    sum += x;
    index++;
  }
  return sum;
}
int cmdProc(void){

  int i;
  unsigned char* action;
  unsigned int check;
  
  if(RxBufferLen == 0)
     return Size_Error;
  
  for(i=0; i<=RxBufferLen; i++){
     if(RxBuffer[i] == SOS)
        break;
  }
  
  if(i < RxBufferLen){
    switch(RxBuffer[i+1]){
          case 'P':
              // See what is the category (temperature, humidity, CO2)
              action = &RxBuffer[i+2];
              
              // Case Temperature
              if (*action == 't'){
                 if(RxBuffer[i+9] != EOS){
                    erraseRxBuf(RxBufferLen);
                    return EOS_Error;
                 }
                 
                 check = CheckSum(&RxBuffer[i+1],5);
                 
<<<<<<< HEAD
                 if(check != CharToNum(&RxBuffer[RxBufferLen-3],3))
=======
                 if(check != CharToNum(&RxBuffer[RxBufferLen-2],3))
>>>>>>> 50432ae3a1e50a0b2656ec02e584ceb7ad56ec6f
                    return CheckSum_Error;
                    
                 int x = CharToNum(&RxBuffer[i+5],2);
                 
                 if(RxBuffer[i+3] == '-')
                    x = -x;
                 
                 if(x > 60 || x < -50){
                    erraseRxBuf(RxBufferLen);
                    return ValueError;
                 }  
                 
                 addValue(temp,&tempIndex,x);
                 
                 for(int i=0;i<RxBufferLen;i++)
                    txChar((unsigned char)(RxBuffer[i]));  
                 
<<<<<<< HEAD
                 numtoChar(&TxBuffer[TxBufferLen-3],check,3);
=======
                 numtoChar(&TxBuffer[TxBufferLen-2],check,3);
>>>>>>> 50432ae3a1e50a0b2656ec02e584ceb7ad56ec6f
                 
                 erraseRxBuf(RxBufferLen);
                 return END;
              }
              
              // CASE HUMIDITY
              else if (*action == 'h'){
                 if(RxBuffer[i+9] != EOS){
                    erraseRxBuf(RxBufferLen);
                    return EOS_Error;
                 }
                 
                 check = CheckSum(&RxBuffer[i+1],5);
                  
<<<<<<< HEAD
                 if(check != CharToNum(&RxBuffer[RxBufferLen-3],3))
=======
                 if(check != CharToNum(&RxBuffer[RxBufferLen-2],3))
>>>>>>> 50432ae3a1e50a0b2656ec02e584ceb7ad56ec6f
                    return CheckSum_Error;
                    
                 int x = CharToNum(&RxBuffer[i+5],3);
                 
                 if(x > 100 || x < 0){
                    erraseRxBuf(RxBufferLen);
                    return ValueError;
                 }
                 
                 addValue(hum,&humIndex,x);
                 
                 for(int i=0;i<RxBufferLen;i++)
                    txChar((unsigned char)(RxBuffer[i]));  
                 
<<<<<<< HEAD
                 numtoChar(&TxBuffer[TxBufferLen-3],check,3);
=======
                 numtoChar(&TxBuffer[TxBufferLen-2],check,3);
>>>>>>> 50432ae3a1e50a0b2656ec02e584ceb7ad56ec6f
                 
                 erraseRxBuf(RxBufferLen);
                 return END;
              }
              
              // Case CO2
              else if (*action == 'c'){
                 if(RxBuffer[i+11] != EOS){
                    erraseRxBuf(RxBufferLen);
                    return EOS_Error;
                 }
                 check = CheckSum(&RxBuffer[i+1],7);
                 
<<<<<<< HEAD
                 if(check != CharToNum(&RxBuffer[RxBufferLen-3],3))
=======
                 if(check != CharToNum(&RxBuffer[RxBufferLen-2],3))
>>>>>>> 50432ae3a1e50a0b2656ec02e584ceb7ad56ec6f
                    return CheckSum_Error;
                    
                 int x = CharToNum(&RxBuffer[i+7],5);
                 
                 if(x > 20000 || x < 400){
                    erraseRxBuf(RxBufferLen);
                    return ValueError;
                 }
                 
                 addValue(co2,&co2Index,x);  
                 
                 for(int i=0;i<RxBufferLen;i++)
                    txChar((unsigned char)(RxBuffer[i]));  
                 
<<<<<<< HEAD
                 numtoChar(&TxBuffer[TxBufferLen-3],check,3);
=======
                 numtoChar(&TxBuffer[TxBufferLen-2],check,3);
>>>>>>> 50432ae3a1e50a0b2656ec02e584ceb7ad56ec6f
                 
                 erraseRxBuf(RxBufferLen);
                 return END;
              }
              
              else{
                 erraseRxBuf(RxBufferLen);
                 return CMD_Error;
              }
              
          case 'A':
<<<<<<< HEAD
              int T,H,C;
=======
>>>>>>> 50432ae3a1e50a0b2656ec02e584ceb7ad56ec6f
              if(RxBuffer[i+19] != EOS){
                 erraseRxBuf(RxBufferLen);
                 return EOS_Error;
              }   
              
              check = CheckSum(&RxBuffer[i+1],15);
<<<<<<< HEAD
              if(check != CharToNum(&RxBuffer[RxBufferLen-3],3))
=======
              if(check != CharToNum(&RxBuffer[RxBufferLen-2],3))
>>>>>>> 50432ae3a1e50a0b2656ec02e584ceb7ad56ec6f
                 return CheckSum_Error;
                 
              action = &RxBuffer[i+2];
              while(*action != '!'){
                 if(*action == 't'){
                   
<<<<<<< HEAD
                   T = 10*(*(action+2) - '0') + *(action+3) - '0';
                 
                   if(*(action+1) == '-')
                      T = -T;
                 
                   if(T > 60 || T < -50){
                      erraseRxBuf(RxBufferLen);
                      return ValueError;
                   } 
=======
                   int x = 10*(*(action+2) - '0') + *(action+3) - '0';
                 
                   if(*(action+1) == '-')
                      x = -x;
                 
                   if(x > 60 || x < -50){
                      erraseRxBuf(RxBufferLen);
                      return ValueError;
                   }   
                   addValue(temp,&tempIndex,x);
                 
>>>>>>> 50432ae3a1e50a0b2656ec02e584ceb7ad56ec6f
                   action += 4;
                 }
                 else if(*action == 'h'){
                   
<<<<<<< HEAD
                   H = 100*(*(action+1) - '0') + 10*(*(action+2) - '0') + *(action+3) - '0';
                 
                   if(H > 100 || H < 0){
                      erraseRxBuf(RxBufferLen);
                      return ValueError;
                   }
=======
                   int x = 100*(*(action+1) - '0') + 10*(*(action+2) - '0') + *(action+3) - '0';
                 
                   if(x > 100 || x < 0){
                      erraseRxBuf(RxBufferLen);
                      return ValueError;
                   }
                   addValue(hum,&humIndex,x);
                 
>>>>>>> 50432ae3a1e50a0b2656ec02e584ceb7ad56ec6f
                   action += 4;
                    
                 }
                 else if(*action == 'c'){
                   
<<<<<<< HEAD
                   C = 10000*(*(action+1) - '0') + 1000*(*(action+2) - '0') + 100*(*(action+3) - '0') + 10*(*(action+4) - '0') + *(action+5) - '0';
                   
                   if(C > 20000 || C < 400){
                      erraseRxBuf(RxBufferLen);
                      return ValueError;
                   }
                   action += 6;
=======
                   int x = 10000*(*(action+1) - '0') + 1000*(*(action+2) - '0') + 100*(*(action+3) - '0') + 10*(*(action+4) - '0') + *(action+5) - '0';
                   
                   if(x > 20000 || x < 400){
                      erraseRxBuf(RxBufferLen);
                      return ValueError;
                   }
                   addValue(co2,&co2Index,x);  
                 
                   action += 6;
                
>>>>>>> 50432ae3a1e50a0b2656ec02e584ceb7ad56ec6f
                 }
                 else{
                   action += 3;
                   //Acrescentar condição de erro
                }
               }
               
<<<<<<< HEAD
               addValue(temp,&tempIndex,T);
               addValue(hum,&humIndex,H);
               addValue(co2,&co2Index,C);  
                
               for(int i=0;i<RxBufferLen;i++)
                    txChar((unsigned char)(RxBuffer[i]));  
                 
               numtoChar(&TxBuffer[TxBufferLen-3],check,3);
=======
               for(int i=0;i<RxBufferLen;i++)
                    txChar((unsigned char)(RxBuffer[i]));  
                 
               numtoChar(&TxBuffer[TxBufferLen-2],check,3);
>>>>>>> 50432ae3a1e50a0b2656ec02e584ceb7ad56ec6f
                
               erraseRxBuf(RxBufferLen);
               return END;
          
          
          case 'L':
               check = CheckSum(&RxBuffer[i+1],1);
<<<<<<< HEAD
               if(check != CharToNum(&RxBuffer[RxBufferLen-3],3))
=======
               if(check != CharToNum(&RxBuffer[RxBufferLen-2],3))
>>>>>>> 50432ae3a1e50a0b2656ec02e584ceb7ad56ec6f
                  return CheckSum_Error;
             
               for(int i=0;i<RxBufferLen;i++)
                   txChar((unsigned char)(RxBuffer[i]));  
                 
<<<<<<< HEAD
               numtoChar(&TxBuffer[TxBufferLen-3],check,3);
=======
               numtoChar(&TxBuffer[TxBufferLen-2],check,3);
>>>>>>> 50432ae3a1e50a0b2656ec02e584ceb7ad56ec6f
                 
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
<<<<<<< HEAD
               if(check != CharToNum(&RxBuffer[RxBufferLen-3],3))
=======
               if(check != CharToNum(&RxBuffer[RxBufferLen-2],3))
>>>>>>> 50432ae3a1e50a0b2656ec02e584ceb7ad56ec6f
                  return CheckSum_Error;
              
               for(int i=0;i<RxBufferLen;i++)
                   txChar((unsigned char)(RxBuffer[i]));  
                 
<<<<<<< HEAD
               numtoChar(&TxBuffer[TxBufferLen-3],check,3);
=======
               numtoChar(&TxBuffer[TxBufferLen-2],check,3);
>>>>>>> 50432ae3a1e50a0b2656ec02e584ceb7ad56ec6f
               erraseRxBuf(RxBufferLen);
               return END;
             
          default :
               erraseRxBuf(RxBufferLen);
               return CMD_Error; 
     }
  }
  else
     return SOS_Error;
  
}
