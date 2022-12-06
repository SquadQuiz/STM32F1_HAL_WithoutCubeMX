/*
 * gpio.h
 *
 *  Created on: Dec 5, 2022
 *      Author: Squadkisz
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include "main.h"

/**
 * @brief LEDs GPIO Configuration
 */
void gpio_LED_config(void);

/**
 * @brief Green LEDs WritePin->PC13
 * 
 * @param state true "LEDs On", false "LEDs Off"
 */
void gpio_LED_writeGreen(bool state);

/**
 * @brief Orange LEDs WritePin->PB13
 * 
 * @param state true "LEDs On", false "LEDs Off"
 */
void gpio_LED_writeOrange(bool state);

/**
 * @brief Red LEDs WritePin->PB14
 * 
 * @param state true "LEDs On", false "LEDs Off" 
 */
void gpio_LED_writeRed(bool state);

/**
 * @brief Green LEDs Toggle->PC13
 */
void gpio_LED_toggleGreen(void);

/**
 * @brief Orange LEDs Toggle->PB13
 */
void gpio_LED_toggleOrange(void);

/**
 * @brief Red LEDs Toggle->PB14
 */
void gpio_LED_toggleRed(void);

/**
 * @brief Push Button Configuration PA0
 * 
 */
void gpio_PB_config(void);

/**
  * @brief Push Button ReadPin State PA0
  * @retval The input port pin value.
  */
bool gpio_PB_read(void);

/**
 * @brief Switches 2P GPIO Configuration
 * Switch P1 -> PA8
 * Switch P2 -> PA15
 */
void gpio_SW_config(void);

/**
 * @brief Switch P1 ReadPin State PA8
 * 
 * @retval The input port pin value.
 */
bool gpio_SW1_read(void);

/**
 * @brief Switch P2 ReadPin State PA15
 * 
 * @retval The input port pin value.
 */
bool gpio_SW2_read(void);

#endif /* INC_GPIO_H_ */
