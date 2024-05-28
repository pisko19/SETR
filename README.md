/**
 @mainpage I/O Sensor/Actuator Module

 @brief This project implements a simple Input/Output sensor/actuator module using the Nordic nRF52840 DevKit with the Zephyr RTOS.

 @details This project aims to implement an I/O module with the nRF52840 DevKit, featuring UART communication with a PC. The system architecture follows a real-time model using a Real-Time Database (RTDB) to synchronize data between the UART command processor and the I/O modules.

 <b>Project Overview:</b>
 - <b>Purpose:</b> Implement an I/O module with the nRF52840 DevKit.
 - <b>Operating System:</b> Zephyr RTOS.
 - <b>Interface:</b> UART (USB VCom) to a PC for simplicity, with the possibility to switch to BLE in the future.

 <b>Inputs and Outputs:</b>
 - <b>Digital Inputs:</b> 4 buttons to select sensors.
 - <b>Digital Outputs:</b> 4 LEDs acting as actuators.
 - <b>Analog Input:</b> 1 (can be emulated using a potentiometer).

 <b>System Architecture:</b>
 The system follows a real-time model where a Real-Time Database (RTDB) is used to synchronize data between the UART command processor and the I/O modules:
 - <b>UART CMD Processor:</b> Handles communication between the PC and the RTDB via UART.
 - <b>RTDB:</b> Stores the status of LEDs, buttons, and the analog sensor.
 - <b>DIO_Update:</b> Periodically updates the digital input and output statuses in the RTDB.
 - <b>AN_Update:</b> Periodically updates the analog input status in the RTDB.

 <b>Functional Requirements:</b>
 - <b>Read Button Status:</b> The PC can request the status of any of the 4 buttons.
 - <b>Set LED Status:</b> The PC can set the status of any of the 4 LEDs.
 - <b>Read Analog Sensor Value:</b> The PC can request the raw ADC value and the converted value of the analog sensor.

 <b>Optional Functional Requirements:</b>
 - Configuration Commands: Allow the PC to configure parameters such as:
   - Frequency of digital I/O updates.
   - Frequency of analog input sampling.
   - Parameters for converting raw ADC values to a scaled value.

 <b>Command Structure:</b>
 Commands should be text-based to allow interaction via a terminal. The emphasis is on structuring the software according to the real-time model, with suitable activation modes and inter-process communication mechanisms.

 <b>Development Guidelines:</b>
 - Modular Architecture: Ensure the software is modular, especially to facilitate future transitions from UART to BLE.
 - Documentation and Testing: Properly document the code and include unit tests for key parts.
 - Communication Protocol: Develop a robust protocol for UART communication.

 <b>Real-Time Constraints:</b>
 - Asynchronous Operations: External read/write operations are asynchronous with respect to internal real-time periodic tasks.
 - Task Activation and Synchronization: Use suitable activation methods and synchronization protocols for tasks.

 <b>Safety Note:</b>
 - Voltage Limits: Ensure the input voltage does not exceed 3V to avoid damaging the devkit. Use the internal power supply for the analog sensor.

 <b>Next Steps:</b>
 - Define UART Commands: Create a set of text-based commands for reading inputs, setting outputs, and configuring parameters.
 - Develop Firmware: Implement the UART command processor, RTDB, DIO_Update, and AN_Update modules in the Zephyr RTOS.
 - Test: Ensure proper functionality and real-time performance through unit tests and integration tests.
 - Document: Provide detailed documentation of the code and system architecture.

 <b>File Structure:</b>
 - **main.c**: Main program file demonstrating usage of the I/O module and interaction with the hardware.
 - **RTDB.h**: Header file for the Real-Time Database (RTDB) used in the I/O module.
 - **RTDB.c**: Source file containing implementations of functions declared in RTDB.h.
 - **UART_CMD_Processor.h**: Header file containing prototypes for the UART command processor.
 - **UART_CMD_Processor.c**: Source file implementing the UART command processor.
 - **DIO_Update.h**: Header file for digital input/output update functions.
 - **DIO_Update.c**: Source file implementing the digital input/output update functions.
 - **AN_Update.h**: Header file for analog input update functions.
 - **AN_Update.c**: Source file implementing the analog input update functions.
 - **Test.h**: Header file for test functions.
 - **Test.c**: Source file containing test functions to verify the behavior of the I/O module.

 <b>Authors:</b>
 - Pedro Afonso (104206)
 - Carlos Teixeira (103187)

 <b>Bug Reports:</b>
 If you encounter any bugs or issues while using this I/O module, please report them [here](https://github.com/pisko19/SETR/issues).
 */

