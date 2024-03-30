#include <stdio.h>
#include <string.h>

#include "../header/Uart.h"

static unsigned char RxBuffer[UART_RX_SIZE];
static unsigned char TxBuffer[UART_TX_SIZE];
static unsigned char RxBufferLen = 0;
static unsigned char TxBufferLen = 0;

int rxChar(unsigned char character){

  if(RxBufferLen < UART_RX_SIZE){
     RxBuffer[RxBufferLen] = character;
     RxBufferLen++;
     return 0;
  }
  return -1;

}

int txChar(unsigned char character){

  if(TxBufferLen < UART_TX_SIZE){
     TxBuffer[TxBufferLen] = character;
     TxBufferLen++;
     return 0;
  }
  return -1;
}

void ResetRxChar(void){

  RxBufferLen = 0;
  return;

}

void ResetTxChar(void){

  TxBufferLen = 0;
  return;

}

void getTxBuf(unsigned char* buf,int len){

  if(&len > 0){
     memcpy(buf,TxBuffer,len);
  }
  return;
}

unsigned int CheckSum(unsigned char* buf, int nbytes){
  unsigned int sum = 0;
  
  for(unsigned char* i = buf;i < buf+2*nbytes;i=i+2){
      sum += (unsigned int)(*i);
  }
  
  return sum;

}

int cmdProc(void){

  int i;
  unsigned char* action;
  unsigned int check;
  
  if(RxBufferLen == 0){
     return -1;
  }
  
  for(i=0; i<RxBufferLen; i++){
     if(RxBuffer[i] == SOS){
        break;
     }
  }
  if(i < RxBufferLen){
    switch(RxBuffer[i+1]){
          case 'P':
              
              action = &RxBuffer[i+2];
              if (*action == 't'){
                 check = CheckSum(action,3);
                 if(check>154 && check<139){
                     return -3;
                 }
                 if(RxBuffer[i+6] != EOS){
                     return -4;
                 }
                 for(int i=0;i<RxBufferLen;i++){
                     txChar((unsigned char)(RxBuffer[i]));
                 }
              }
              return 0;
          case 'A':
          
          case 'L':
          
          case 'R':  
          
          default :
     
     
     }
  }
}

