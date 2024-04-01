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
#define SOS '#' /**< Start of Frame symbol */
#define EOS '!' /**< End of Frame symbol */

#define END 0 /**< End of function status code */
#define ValueError -1 /**< Value error status code */
#define EOS_Error -2 /**< End of Frame error status code */
#define Len_Error -3 /**< Length error status code */
#define Size_Error -4 /**< Size error status code */
#define CMD_Error -5 /**< Command error status code */

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

extern unsigned int temp[];
extern unsigned int hum[];
extern unsigned int co2[];
extern unsigned int tempIndex;
extern unsigned int humIndex;
extern unsigned int co2Index;



#endif /* Uart_H_ */

/** @} */ // End of Uart group

