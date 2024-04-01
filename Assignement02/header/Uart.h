#ifndef Uart_H_
#define Uart_H_

#define MAX_SIZE 20
#define UART_RX_SIZE 30
#define UART_TX_SIZE 30
#define SOS '#'
#define EOS '!'
#define END 0
#define ValueError -1
#define EOS_Error -2
#define Len_Error -3
#define Size_Error -4
#define CMD_Error -5

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
int getTxBuf(unsigned char* buf,int len);

// Calcula o checksum de uma string
unsigned int CheckSum(unsigned char* buf, int nbytes);

// Acresenta um valor na primeira posição do array com shift para 
// a direita dos restantes valores
void addValue(int *arr, int *size, int value);


#endif
