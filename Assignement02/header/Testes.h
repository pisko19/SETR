#ifndef Testes_H_
#define Testes_H_

/**
 * @file Testes.h
 * @brief Header file containing declarations of functions for testing the UART module.
 * \author Pedro Afonso, 104206
 * \author Carlos Teixeira 103187
 * \date 01/04/2024
 * \brief Functions and structures for testing UART communication.
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
void Teste_Proc_A(void);

/**
 * @brief Performs a test for returning the lastest 20 values of the combined processing functionality.
 */
void Teste_Proc_L(void);

void TESTE(void);

#endif
