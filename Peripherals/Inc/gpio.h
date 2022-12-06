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
 * @brief LEDs WritePin
 * 
 * @param state 
 */
void gpio_LED_writeLED(bool state);

/**
 * @brief LEDs Toggle
 */
void gpio_LED_toggleLED(void);

/**
 * @brief USER Button Configuration PA0
 * 
 */
void gpio_PB_config(void);

/**
  * @brief  USER Button ReadPin State
  * @retval The input port pin value.
  */
bool gpio_PB_read(void);



#endif /* INC_GPIO_H_ */
