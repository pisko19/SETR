#ifndef Testes_H_
#define Testes_H_


#define CheckError 0 //Change this value if you want to make a checksum error

/**
 * @file Testes.h
 * @brief Header file containing declarations of functions for testing the UART module.
 * \author Pedro Afonso, 104206
 * \author Carlos Teixeira 103187
 * \date 01/04/2024
 * \brief Functions and structures for testing UART communication.
 */

/**
 * @brief Performs a test for the rxChar function using UNITY.
 * @par Test 1 – Data Transmission
 * @par Objective:
 * Verify the UART's operational capability in transmitting data accurately to an external device.
 * @par Method:
 * This test involves sending data through the UART interface and validating that the transmitted data aligns with the expected output.
 * @par Expected Outcome:
 * Ensure that data transmitted via the UART is precise and devoid of errors.
 */
void Teste_RxChar(void);

/**
 * @brief Performs a test for the txChar function using UNITY.
 * @par Test 2 – Data Reception
 * @par Objective:
 * Validate the UART's proficiency in receiving data from an external device.
 * @par Method:
 * Data from an external device is sent to the microcontroller through UART, and the received data is compared against the expected input.
 * @par Expected Outcome:
 * Confirm that the UART can accurately receive and process incoming data.
 */
void Teste_TxChar(void);

/**
 * @brief Performs a test for the cmdProc function using UNITY.
 * @par Test 3 – Data Processing Accuracy
 * @par Objective:
 * Determine whether the UART correctly processes received data.
 * @par Method:
 * Intentional errors are introduced into transmitted data, and the UART's ability to detect and handle these errors is evaluated.
 * @par Expected Outcome:
 * Ensure that the UART can effectively identify and manage error conditions without compromising data integrity.
 */
void Teste_Proc(void);

/**
 * @brief Performs a test for the temperature processing functionality using UNITY.
 * @par Test 4 – Temperature Data Handling
 * @par Objective:
 * Verify the UART's capability to handle temperature data and provide accurate temperature readings.
 * @par Method:
 * Send temperature data to the UART and verify that it interprets the information correctly, returning the expected temperature value.
 * @par Expected Outcome:
 * Confirm that the UART can process temperature data accurately and provide correct temperature readings.
 */
void Teste_Proc_Temp(void);

/**
 * @brief Performs a test for the humidity processing functionality using UNITY.
 * @par Test 5 – Humidity Data Handling
 * @par Objective:
 * Assess the UART's ability to handle humidity data and provide accurate humidity readings.
 * @par Method:
 * Similar to Test 4, humidity data is sent to the UART to ensure it interprets and returns the correct humidity value.
 * @par Expected Outcome:
 * Ensure that the UART can accurately process humidity data and provide correct humidity readings.
 */
void Teste_Proc_Hum(void);

/**
 * @brief Performs a test for the CO2 processing functionality using UNITY.
 * @par Test 6 – CO2 Data Handling
 * @par Objective:
 * Validate the UART's capability to handle CO2 data and provide accurate CO2 level readings.
 * @par Method:
 * CO2 data is transmitted to the UART to verify its correct interpretation and return of the CO2 level.
 * @par Expected Outcome:
 * Confirm that the UART accurately processes CO2 data and provides correct CO2 level readings.
 */
void Teste_Proc_CO2(void);

/**
 * @brief Performs a test for the combined processing functionality using UNITY.
 * @par Test 7 – Mixed Data Handling
 * @par Objective:
 * Evaluate the UART's functionality in handling all three types of data (temperature, humidity, CO2) regardless of the order they are received.
 * @par Method:
 * Send mixed data (temperature, humidity, CO2) to the UART in varying sequences and verify its ability to interpret and process each type correctly.
 * @par Expected Outcome:
 * Ensure that the UART can handle mixed data inputs effectively, regardless of their order.
 */
void Teste_Proc_A(void);

/**
 * @brief Performs a test for all the functionality using UNITY.
 * @par Test 8 – Comprehensive Testing
 * @par Objective:
 * Perform an extensive test covering all previous tests (1-7), along with additional evaluations of the UART's ability to retrieve the last 20 samples of each data type and reset them.
 * @par Method:
 * Execute tests 1-7 sequentially, followed by retrieving the last 20 samples of each data type and resetting them, and verify the UART's performance.
 * @par Expected Outcome:
 * Confirm that all previous tests are successful, and validate the UART's ability to manage historical data and reset functionality.
 */
void Teste_Proc_All(void);

#endif
