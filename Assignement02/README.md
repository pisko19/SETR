/**
 @mainpage Smart Sensor UART Module
 
 @brief This module provides functionality for processing commands received via UART (Universal Asynchronous Receiver-Transmitter) for a smart sensor.
 
 @details The module is designed to handle commands sent to the smart sensor over UART communication. Each command follows a specific structure, starting with a '#' symbol, followed by a command indication, data (if applicable), and a checksum for error detection. The module supports various commands such as reading real-time sensor values, retrieving historical data, and resetting the sensor's history.
 
 <b>Specifications:</b>
 - <b>Command Structure:</b>
   - '#' CMD DATA CS '!'
   - # : Start of Frame symbol
   - ! : End of Frame symbol
   - CMD : Command indication (one byte)
   - DATA : Variable size, command arguments
   - CS : Checksum, sum of numerical value of CMD and DATA[i] bytes (one byte)
 - <b>Supported Commands:</b>
   - A: Reads the real-time values of the variables provided by the sensor
   - P: Reads the real-time value of one of the sensors
   - L: Returns the last 20 samples of each variable
   - R: Resets the history
 - <b>Sensor Emulation:</b>
   - Since no physical sensors are utilized, the sensor outputs are emulated. Random values alone are not suitable for emulation due to their lack of realism. Alternate strategies for emulating sensor data should be employed to provide more meaningful simulation.
 
 <b>File Structure:</b>
 - <b>Uart.h:</b> Header file containing declarations of structures and functions for UART communication.
 - <b>Uart.c:</b> Source file containing implementations of functions declared in Uart.h.
 - <b>main.c:</b> Main program file demonstrating usage of the UART module and interaction with the smart sensor.
 - <b>Testes.h:</b> Header file containing declarations of functions for testing the UART functionality.
 - <b>Testes.c:</b> Source file containing implementations of functions declared in Testes.h for testing the UART functionality.
 
 <b>Usage:</b>
 To use this UART module in your C program, include the header file Uart.h in your source code. You can then call the provided functions to interact with the smart sensor via UART communication.
 
 <b>Test Scenarios:</b>
 The module includes test scenarios in the main.c file to demonstrate the functionality of the UART module. Additionally, the Testes.h and Testes.c files provide test functions for verifying the behavior of the UART library. These functions perform various operations such as sending commands, receiving responses, and testing error conditions.
 
<b>Author:</b>
 - Pedro Afonso (104206)
 - Carlos Teixeira (103187)
 
 <b>Bug Reports:</b>
 If you encounter any bugs or issues while using this UART module, please report them
 <a href="https://github.com/pisko19/SETR/issues">here</a>.

