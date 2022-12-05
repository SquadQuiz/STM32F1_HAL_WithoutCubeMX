/*
 * gpio.c
 *
 *  Created on: Dec 5, 2022
 *      Author: Squadkisz
 */

#include "gpio.h"

/**
 * @brief LEDs GPIO Configuration
 */
void gpio_LED_config(void)
{
	/*
	 * LED Green -> PC13
	 */
	
	GPIO_InitTypeDef gpioInitStruct = {0};
	__HAL_RCC_GPIOC_CLK_ENABLE();

	gpioInitStruct.Pin = GPIO_PIN_13;						// GPIOC-13
	gpioInitStruct.Mode = GPIO_MODE_OUTPUT_PP;	// Output Push-Pull
	gpioInitStruct.Pull = GPIO_NOPULL;					// Pin No Pull
	gpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW; // Speed Low
	HAL_GPIO_Init(GPIOC, &gpioInitStruct);
}

void gpio_LED_writeLED(bool state)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, (GPIO_PinState)state);
}

void gpio_LED_toggleLED(void)
{
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
}
