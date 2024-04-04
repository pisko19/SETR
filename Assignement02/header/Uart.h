/**
 * \file Uart.h
 * \brief Header file containing declarations of structures and functions for UART communication.
 *
 * This file provides the necessary structures and functions to work with UART communication in a microcontroller project.
 * It includes declarations for functions to process commands received via UART, as well as functions to manage receive and
 * transmit buffers. Additionally, macros are defined for maximum buffer sizes and error codes.
 *
 * \author Pedro Afonso, 104206
 * \author Carlos Teixeira 103187
 * \date 01/04/2024
 *
 * \defgroup Uart UART Communication
 * \brief Functions and structures for UART communication.
 * @{
 */

#ifndef Uart_H_
#define Uart_H_

#define MAX_SIZE 20 /**< Maximum size of arrays */
#define UART_RX_SIZE 30 /**< Size of the UART receive buffer */
#define UART_TX_SIZE 30 /**< Size of the UART transmit buffer */
#define SOS '#' /**< Start of Sentence symbol */
#define EOS '!' /**< End of Sentence symbol */

#define END 0 /**< End of function status code */
#define ValueError -1 /**< Value error status code */
#define EOS_Error -2 /**< End of Sentence error status code */
#define SOS_Error -3 /**< Start of Sentence error status code */
#define Len_Error -4 /**< Length error status code */
#define Size_Error -5 /**< Size error status code */
#define CMD_Error -6 /**< Command error status code */

static unsigned int hum[MAX_SIZE];
static unsigned int co2[MAX_SIZE];
static unsigned int temp[MAX_SIZE];
static unsigned char RxBuffer[UART_RX_SIZE];
static unsigned char TxBuffer[UART_TX_SIZE];
static unsigned char RxBufferLen = 0;
static unsigned char TxBufferLen = 0;
static unsigned int tempIndex = 0;
static unsigned int humIndex = 0;
static unsigned int co2Index = 0;

/**
 * @brief Process a received command.
 *
 * This function processes a command received via UART, one character at a time.
 *
 * @return Status code:
 *         - END if successful.
 *         - ValueError if there is a value error.
 *         - EOS_Error if there is an End of Frame symbol error.
 *         - Len_Error if there is a length error.
 *         - Size_Error if there is a size error.
 *         - CMD_Error if there is a command error.
 */
int cmdProc(void);

/**
 * @brief Add a character to the receive buffer.
 *
 * This function adds a character to the receive buffer.
 *
 * @param character The character to be added to the receive buffer.
 *
 * @return Status code:
 *         - END if successful.
 *         - Size_Error if the receive buffer is full.
 */
int rxChar(unsigned char character);

/**
 * @brief Add a character to the transmit buffer.
 *
 * This function adds a character to the transmit buffer.
 *
 * @param character The character to be added to the transmit buffer.
 *
 * @return Status code:
 *         - END if successful.
 *         - Size_Error if the transmit buffer is full.
 */
int txChar(unsigned char character);


/**
 * @brief Reset the receive buffer.
 *
 * This function resets the receive buffer.
 */
void ResetRxChar(void);

/**
 * @brief Reset the transmit buffer.
 *
 * This function resets the transmit buffer.
 */
void ResetTxChar(void);

/**
 * @brief Get the transmit buffer.
 *
 * This function copies the transmit buffer contents to a specified buffer.
 *
 * @param buf Pointer to the buffer to store the transmit buffer contents.
 * @param len Length of the buffer.
 *
 * @return Status code:
 *         - END if successful.
 *         - Len_Error if the transmit buffer is empty.
 */
int getTxBuf(unsigned char* buf, int len);

/**
 * @brief Get the transmit buffer lenght.
 *
 * This function return the transmit buffer lenght.
 *
 * @return Status code:
 *         - TxBufferLen if successful.
 *         - Size_Error if the transmit buffer length is bigger than UART_TX_SIZE.
 */
int getTxBufLen(void);

/**
 * @brief Get the receiver buffer.
 *
 * This function copies the receiver buffer contents to a specified buffer.
 *
 * @param buf Pointer to the buffer to store the receiver buffer contents.
 * @param len Length of the buffer.
 *
 * @return Status code:
 *         - END if successful.
 *         - Len_Error if the receiver buffer is empty.
 */
int getRxBuf(unsigned char* buf, int len);

/**
 * @brief Get the receiver buffer lenght.
 *
 * This function return the receiver buffer lenght.
 *
 * @return Status code:
 *         - RxBufferLen if successful.
 *         - Size_Error if the transmit buffer length is bigger than UART_TX_SIZE.
 */
int getRxBufLen(void);

/**
 * @brief Calculate the checksum of a string.
 *
 * This function calculates the checksum of a string.
 *
 * @param buf Pointer to the string.
 * @param nbytes Number of bytes in the string.
 *
 * @return The checksum value.
 */
unsigned int CheckSum(unsigned char* buf, int nbytes);

/**
 * @brief Add a value to an array with shifting.
 *
 * This function adds a value to an array with shifting.
 *
 * @param arr Pointer to the array.
 * @param size Pointer to the size of the array.
 * @param value The value to be added.
 */
void addValue(int *arr, int *size, int value);

/**
 * @brief Get the instant temperature.
 *
 * This function returns the instant temperature.
 *
 * @return The instant temperature.
 */
unsigned int getInstantTemp(void);

/**
 * @brief Get the temperature array.
 *
 * This function returns he pointer for the temperature array
 *
 * @return The pointer for the temperature array.
 */
unsigned int* getTemp(void);

/**
 * @brief Get the instant humidity.
 *
 * This function returns the instant humidity.
 *
 * @return The instant temperature.
 */
unsigned int getInstantHum(void);

/**
 * @brief Get the humidity array.
 *
 * This function returns he pointer for the humidity array
 *
 * @return The pointer for the humidity array.
 */
unsigned int* getHum(void);

/**
 * @brief Get the instant CO2.
 *
 * This function returns the instant CO2.
 *
 * @return The instant temperature.
 */
unsigned int getInstantCO2(void);

/**
 * @brief Get the CO2 array.
 *
 * This function returns he pointer for the CO2 array
 *
 * @return The pointer for the CO2 array.
 */
unsigned int* getCO2(void);

/**
 * @brief Utility function to convert a number to a character array. This function was based on chatGPT.
 * 
 * @param array Pointer to the character array where the result will be stored.
 * @param num The number to be converted.
 * @param len Length of the character array.
 */
void numtoChar(unsigned char array [], int num, int len);

#endif /* Uart_H_ */

/** @} */ // End of Uart group

