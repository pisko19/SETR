#ifndef Testes_H_
#define Testes_H_

/**
 * @file Testes.h
 * @brief Header file containing declarations of functions for testing the UART module.
 */

/**
 * @brief Performs a test for the rxChar function.
 */
void Teste_RxChar(void);

/**
 * @brief Performs a test for the txChar function.
 */
void Teste_TxChar(void);

/**
 * @brief Performs a test for the cmdProc function.
 */
void Teste_Proc(void);

/**
 * @brief Performs a test for the temperature processing functionality.
 */
void Teste_Proc_Temp(void);

/**
 * @brief Performs a test for the humidity processing functionality.
 */
void Teste_Proc_Hum(void);

/**
 * @brief Performs a test for the CO2 processing functionality.
 */
void Teste_Proc_CO2(void);

/**
 * @brief Performs a test for the combined processing functionality.
 */
void Teste_Proc_All(void);

/**
 * @brief Utility function to convert a number to a character array.
 * 
 * @param num The number to be converted.
 * @param array Pointer to the character array where the result will be stored.
 * @param len Length of the character array.
 */
void numtoChar(int num, char array[], int len);

#endif
