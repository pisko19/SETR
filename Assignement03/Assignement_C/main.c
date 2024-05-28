/**
 * @file main.c
 * @brief Vending Machine Emulator using nRF52840 Development Kit
 *
 * This file contains the main program logic for emulating a vending machine. 
 * The emulator supports coin insertion, product selection, and credit return functionalities 
 * using four push-buttons for input and four LEDs for output. UART is used to communicate 
 * debug and status messages to a PC terminal.
 * 
 * @details The vending machine supports three products with different prices. Users can insert 
 * coins to accumulate credit, browse through the available products, and make purchases if they 
 * have enough credit. The system also allows users to return any remaining credit.
 * 
 * @author 
 * - Pedro Afonso (104206)
 * - Carlos Teixeira (103187)
 *
 *@date 19/05/2024
 * 
 */

#include "../src/sc_types.h"
#include "../src-gen/Statechart_required.h"
#include "../src-gen/Statechart.h"
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>

#define ERR_ABORT -1
#define Num_Leds 4
#define Num_Buts 4

#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)
#define LED3_NODE DT_ALIAS(led3)
#define BUT0_NODE DT_ALIAS(sw0)
#define BUT1_NODE DT_ALIAS(sw1)
#define BUT2_NODE DT_ALIAS(sw2)
#define BUT3_NODE DT_ALIAS(sw3)

static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);
static const struct gpio_dt_spec led3 = GPIO_DT_SPEC_GET(LED3_NODE, gpios);
static const struct gpio_dt_spec leds[Num_Leds] = {led0, led1, led2, led3};

static const struct gpio_dt_spec but0 = GPIO_DT_SPEC_GET(BUT0_NODE, gpios);
static const struct gpio_dt_spec but1 = GPIO_DT_SPEC_GET(BUT1_NODE, gpios);
static const struct gpio_dt_spec but2 = GPIO_DT_SPEC_GET(BUT2_NODE, gpios);
static const struct gpio_dt_spec but3 = GPIO_DT_SPEC_GET(BUT3_NODE, gpios);
static const struct gpio_dt_spec buts[Num_Buts] = {but0, but1, but2, but3};

static struct gpio_callback button0_cb_data;
static struct gpio_callback button1_cb_data;
static struct gpio_callback button2_cb_data;
static struct gpio_callback button3_cb_data;

static int ret = 0;
static Statechart StateMachine;

/**
 * @brief Check the readiness of LEDs and buttons
 * 
 * This function verifies that all LED and button devices are ready for use.
 * 
 * @return int 0 if all devices are ready, ERR_ABORT otherwise
 */
int Check_Function() {
    for (int i = 0; i < Num_Leds; i++) {
        if (!device_is_ready(leds[i].port)) {
            printk("Error: led%d device %s is not ready\n", i, leds[i].port->name);
            return ERR_ABORT;
        }
    }

    for (int i = 0; i < Num_Buts; i++) {
        if (!device_is_ready(buts[i].port)) {
            printk("Error: button%d device %s is not ready\n", i, buts[i].port->name);
            return ERR_ABORT;
        }
    }

    return 0;
}

/**
 * @brief Initialize the LEDs and buttons
 * 
 * This function configures the LEDs as output and the buttons as input with pull-up resistors.
 * It also sets up interrupts for the buttons.
 * 
 * @return int 0 if initialization is successful, ERR_ABORT otherwise
 */
int Init_Function() {
    for (int i = 0; i < Num_Leds; i++) {
        ret = gpio_pin_configure_dt(&leds[i], GPIO_OUTPUT_ACTIVE);
        if (ret < 0) {
            printk("Error: gpio_pin_configure_dt failed for led%d, error:%d", i, ret);
            return ERR_ABORT;
        }
    }

    for (int i = 0; i < Num_Buts; i++) {
        ret = gpio_pin_configure_dt(&buts[i], GPIO_INPUT | GPIO_PULL_UP);
        if (ret < 0) {
            printk("Error: gpio_pin_configure_dt failed for button%d, error:%d", i, ret);
            return ERR_ABORT;
        }

        ret = gpio_pin_interrupt_configure_dt(&buts[i], GPIO_INT_EDGE_TO_ACTIVE);
        if (ret < 0) {
            printk("Error: gpio_pin_interrupt_configure_dt failed for button%d, error:%d", i, ret);
            return ERR_ABORT;
        }
    }

    return 0;
}

/**
 * @brief Set the LED states based on the input value
 * 
 * This function sets the state of the LEDs based on the value passed to it.
 * The value corresponds to different states of the vending machine.
 * 
 * @param handle Pointer to the statechart handle
 * @param Leds Integer value representing the LED state
 */
void statechart_setLeds(Statechart* handle, const sc_integer Leds) {
    switch (Leds) {
        case 0:
            for (int i = 0; i < Num_Leds; i++) {
                ret = gpio_pin_set_dt(&leds[i], 0);
                if (ret < 0) {
                    printk("Error: gpio_pin_set_dt failed for led%d, error:%d", i, ret);
                    return;
                }
            }
            break;
        case 1:
            for (int i = 0; i < Num_Leds; i++) {
                if (i < 2) {
                    ret = gpio_pin_set_dt(&leds[i], 1 - i);
                } else {
                    ret = gpio_pin_set_dt(&leds[i], 0);
                }
                if (ret < 0) {
                    printk("Error: gpio_pin_set_dt failed for led%d, error:%d", i, ret);
                    return;
                }
            }
            break;
        case 2:
            for (int i = 0; i < Num_Leds; i++) {
                if (i < 2) {
                    ret = gpio_pin_set_dt(&leds[i], i);
                } else {
                    ret = gpio_pin_set_dt(&leds[i], 0);
                }
                if (ret < 0) {
                    printk("Error: gpio_pin_set_dt failed for led%d, error:%d", i, ret);
                    return;
                }
            }
            break;
        case 3:
            for (int i = 0; i < Num_Leds; i++) {
                if (i < 2) {
                    ret = gpio_pin_set_dt(&leds[i], 1);
                } else {
                    ret = gpio_pin_set_dt(&leds[i], 0);
                }
                if (ret < 0) {
                    printk("Error: gpio_pin_set_dt failed for led%d, error:%d", i, ret);
                    return;
                }
            }
            break;
        case 4:
            for (int i = 0; i < Num_Leds; i++) {
                if (i < 2) {
                    ret = gpio_pin_set_dt(&leds[i], 0);
                } else {
                    ret = gpio_pin_set_dt(&leds[i], i % 2);
                }
                if (ret < 0) {
                    printk("Error: gpio_pin_set_dt failed for led%d, error:%d", i, ret);
                    return;
                }
            }
            break;
        case 5:
            for (int i = 0; i < Num_Leds; i++) {
                if (i < 2) {
                    ret = gpio_pin_set_dt(&leds[i], 0);
                } else {
                    ret = gpio_pin_set_dt(&leds[i], i % 3);
                }
                if (ret < 0) {
                    printk("Error: gpio_pin_set_dt failed for led%d, error:%d", i, ret);
                    return;
                }
            }
            break;
    }
}

/**
 * @brief Button 0 callback function
 * 
 * This function is called when button 0 is pressed. It raises the one Euro event in the statechart.
 * 
 * @param dev Pointer to the device structure
 * @param cb Pointer to the callback structure
 * @param pins Pin mask of the triggered interrupt
 */
void button0Pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins) {
    statechart_Button_raise_one_Euro(&StateMachine);
}

/**
 * @brief Button 1 callback function
 * 
 * This function is called when button 1 is pressed. It raises the two Euro event in the statechart.
 * 
 * @param dev Pointer to the device structure
 * @param cb Pointer to the callback structure
 * @param pins Pin mask of the triggered interrupt
 */
void button1Pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins) {
    statechart_Button_raise_two_Euro(&StateMachine);
}

/**
 * @brief Button 2 callback function
 * 
 * This function is called when button 2 is pressed. It raises the select event in the statechart.
 * 
 * @param dev Pointer to the device structure
 * @param cb Pointer to the callback structure
 * @param pins Pin mask of the triggered interrupt
 */
void button2Pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins) {
    statechart_Button_raise_select(&StateMachine);
}

/**
 * @brief Button 3 callback function
 * 
 * This function is called when button 3 is pressed. It raises the enter event in the statechart.
 * 
 * @param dev Pointer to the device structure
 * @param cb Pointer to the callback structure
 * @param pins Pin mask of the triggered interrupt
 */
void button3Pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins) {
    statechart_Button_raise_enter(&StateMachine);
}

/**
 * @brief Display the statechart information on the terminal
 * 
 * This function displays various information related to the statechart on the terminal based on the 
 * input type. It can display the current amount, product selection, credit return, and other messages.
 * 
 * @param handle Pointer to the statechart handle
 * @param Type Integer value representing the type of information to display
 */
void statechart_display(Statechart* handle, const sc_integer Type) {
    switch (Type) {
        case 0:
            printk("\n\r"
                   "############################################\n\r"
                   "#                                          #\n\r"
                   "#                  AMOUNT                  #\n\r"
                   "#                 --------                 #\n\r"
                   "#                  %3d €                   #\n\r"
                   "#                                          #\n\r"
                   "############################################\n", handle->internal.Cash);
            break;
        case 1:
            printk("\n\r"
                   "############################################\n\r"
                   "#                                          #\n\r"
                   "#             Product Selection            #\n\r"
                   "#                 --------                 #\n\r"
                   "#               Product ->%3d              #\n\r"
                   "#                Price ->%3d €             #\n\r"
                   "#                                          #\n\r"
                   "############################################\n", handle->internal.Product, handle->internal.Product);
            break;
        case 2:
            printk("\n\r"
                   "############################################\n\r"
                   "#                                          #\n\r"
                   "#             Return the Credit            #\n\r"
                   "#                 --------                 #\n\r"
                   "#               Credit ->%3d €             #\n\r"
                   "#                                          #\n\r"
                   "############################################\n", handle->internal.Cash);
            break;
        case 3:
            printk("\n\r"
                   "############################################\n\r"
                   "#                                          #\n\r"
                   "#           Product Selected               #\n\r"
                   "#                 --------                 #\n\r"
                   "#               Product ->%3d              #\n\r"
                   "#                Price ->%3d €             #\n\r"
                   "#              New Amount ->%3d €          #\n\r"
                   "#                                          #\n\r"
                   "############################################\n", handle->internal.Product, handle->internal.Product, handle->internal.Cash);
            break;
        case 4:
            printk("\n\r"
                   "############################################\n\r"
                   "#                                          #\n\r"
                   "#     Not Enough Cash For The Product      #\n\r"
                   "#     Product->%3d    Cash->%3d            #\n\r"
                   "#                                          #\n\r"
                   "############################################\n", handle->internal.Product, handle->internal.Cash);
            break;
        default:
            return;
    }
}

/**
 * @brief Main function
 * 
 * This function initializes the LEDs and buttons, sets up the callbacks for the buttons, and starts 
 * the statechart. It checks the readiness of the devices and configures them accordingly.
 * 
 * @return int 0 if the program executes successfully, ERR_ABORT otherwise
 */
int main() {
    ret = Check_Function();
    if (ret < 0) {
        return ERR_ABORT;
    }

    ret = Init_Function();
    if (ret < 0) {
        return ERR_ABORT;
    }

    gpio_init_callback(&button0_cb_data, button0Pressed, BIT(but0.pin));
    gpio_add_callback(but0.port, &button0_cb_data);

    gpio_init_callback(&button1_cb_data, button1Pressed, BIT(but1.pin));
    gpio_add_callback(but1.port, &button1_cb_data);

    gpio_init_callback(&button2_cb_data, button2Pressed, BIT(but2.pin));
    gpio_add_callback(but2.port, &button2_cb_data);

    gpio_init_callback(&button3_cb_data, button3Pressed, BIT(but3.pin));
    gpio_add_callback(but3.port, &button3_cb_data);

    statechart_init(&StateMachine);
    statechart_enter(&StateMachine);

    return 0;
}

