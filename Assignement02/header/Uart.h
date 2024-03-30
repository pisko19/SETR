#ifndef Uart_H_
#define Uart_H_

#define UART_RX_SIZE 7
#define UART_TX_SIZE 7
#define SOS '#'
#define EOS '!'

// Acrescenta os chars para o buffer de receção e analise a ação para executar
int cmdProc(void);

// Acrescenta um char no buffer de receção
int rxChar(unsigned char character);

// Acrescenta um char no buffer de transmissão
int txChar(unsigned char character);

// Da reset ao buffer de receção
void ResetRxChar(void);

// Da Reset ao buffer de transmissão
void ResetTxChar(void);

// Transmite os valores do buffer de transmissão para uma string
void getTxBuf(unsigned char* buf,int len);

// Calcula o checksum de uma string
unsigned int CheckSum(unsigned char* buf, int nbytes);


#endif
