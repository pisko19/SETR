/**
 @mainpage Vending Machine Emulator
 
 @brief This module emulates a simple vending machine using the nRF52840 development kit with functionality for coin insertion, product selection, and credit return.
 
 @details The Vending Machine Emulator project simulates the behavior of a vending machine, allowing users to insert coins, browse products, purchase products, and return remaining credit. The system uses four push-buttons for user input and four LEDs for output indications. Debug and status messages are communicated via UART to a PC terminal.

 <b>Specifications:</b>
 - <b>Push-Button Functionality:</b>
   - Button 1: Insert 1 EUR coin
   - Button 2: Insert 2 EUR coin
   - Button 3: Browse products/options
   - Button 4: Enter to validate a choice
 - <b>LED Functionality:</b>
   - LED 1 and 2: Indicate the active product/option
   - LED 3: Dispense product
   - LED 4: Display available credit
 - <b>Operation Description:</b>
   - Users insert coins, which accumulate as credit.
   - Users can browse through three products and one option to return credit using the browse button.
   - Products/options cycle in a loop (e.g., after the last product, the first product becomes active).
   - The Enter button validates selections, dispensing products if enough credit is available or returning credit.
   - Each product has a specific price (Product 1: 1 EUR, Product 2: 2 EUR, Product 3: 3 EUR).
   - Users must press Enter after dispensing a product or returning credit to complete the operation.

 - <b>Product/Option Coding by LEDs:</b>
   - Off-Off: Return credit
   - Off-On: Product 1 (1 EUR)
   - On-Off: Product 2 (2 EUR)
   - On-On: Product 3 (3 EUR)

 - <b>Information Display:</b>
   - Current product and credit are displayed via UART on a PC terminal.
   - Messages indicate successful purchases or credit returns.
   
 <b>File Structure:</b>
 - <b>main.c:</b> Main program file demonstrating usage of the vending machine module and interaction with the hardware.
 - <b>Statechart.h</b> Header file for the state machine used in the vending machine emulation.
 - <b>statechart.c:</b> Source file containing implementations of functions declared in statechart.h for the state machine used in the vending machine emulation.
 - <b>Statechart_required.h:</b> Header file containing prototypes for functions required by the state machine implementation.
 
 <b>Usage:</b>
 To use this vending machine emulator in your C program, include the header file statechart.h in your source code. You can then call the provided functions to interact with the vending machine via button inputs and LED outputs. Additionally, ensure that statechart_required.h is included to access the required function prototypes for the state machine implementation.
 
 <b>Test Scenarios:</b>
 The module includes test scenarios in the main.c file to demonstrate the functionality of the vending machine emulator. Additionally, the Test.h and Test.c files provide test functions for verifying the behavior of the vending machine. These functions perform various operations such as inserting coins, browsing products, making purchases, and returning credit.

<b>Author:</b>
 - Pedro Afonso (104206)
 - Carlos Teixeira (103187)
 
 <b>Bug Reports:</b>
 If you encounter any bugs or issues while using this vending machine emulator, please report them
 <a href="https://github.com/pisko19/SETR/issues">here</a>.
 */

