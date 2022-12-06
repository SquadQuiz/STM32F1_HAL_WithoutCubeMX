/*
 * gpio.c
 *
 *  Created on: Dec 5, 2022
 *      Author: Squadkisz
 */

#include "gpio.h"

void gpio_LED_config(void)
{
	/*
	 * LED Green  -> PC13
	 * LED Red    -> PB13
	 * LED Orange -> PB14
	 */

	GPIO_InitTypeDef gpioInitStruct = {0};
	__HAL_RCC_GPIOB_CLK_ENABLE(); 									// Enable GPIOB Clock
	__HAL_RCC_GPIOC_CLK_ENABLE(); 									// Enable GPIOC Clock

	//* LED Green GPIO Initialization
	gpioInitStruct.Pin = GPIO_PIN_13;								// GPIO PC13
	gpioInitStruct.Mode = GPIO_MODE_OUTPUT_PP;			// Output Push-Pull
	gpioInitStruct.Pull = GPIO_NOPULL;							// Pin No Pull
	gpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW; 		// Speed Low
	HAL_GPIO_Init(GPIOC, &gpioInitStruct);

	//* LED Red/Orange GPIO Initialization
	gpioInitStruct.Pin = GPIO_PIN_13 | GPIO_PIN_14; // GPIO PB13,PB14
	gpioInitStruct.Mode = GPIO_MODE_OUTPUT_PP;			// Output Push-Pull
	gpioInitStruct.Pull = GPIO_NOPULL;							// Pin No Pull
	gpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;			// Speed Low
	HAL_GPIO_Init(GPIOB, &gpioInitStruct);
}

void gpio_LED_writeGreen(bool state)
{
	// LED Green  -> PC13
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, (GPIO_PinState)state);
}

void gpio_LED_writeOrange(bool state)
{
	// LED Orange  -> PB13
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, (GPIO_PinState)state);
}

void gpio_LED_writeRed(bool state)
{
	// LED Red  -> PB14
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, (GPIO_PinState)state);
}

void gpio_LED_toggleGreen(void)
{
	// LED Green  -> PC13
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
}

void gpio_LED_toggleOrange(void)
{
	// LED Orange  -> PB13
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
}

void gpio_LED_toggleRed(void)
{
	// LED Red  -> PB14
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
}

void gpio_PB_config(void)
{
	/*
	 * Push Button -> PA0
	 */
	GPIO_InitTypeDef gpioInitStruct = {0};
	__HAL_RCC_GPIOA_CLK_ENABLE();

	//* Push Button GPIO Initialization
	gpioInitStruct.Pin = GPIO_PIN_0;							// GPIO PA0
	gpioInitStruct.Mode = GPIO_MODE_INPUT;				// Input Mode
	gpioInitStruct.Pull = GPIO_NOPULL;						// No Pull
	gpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW; 	// Speed Low
	HAL_GPIO_Init(GPIOA, &gpioInitStruct);
}

bool gpio_PB_read(void)
{
	// return input port pin value
	return (bool)HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
}

void gpio_SW_config(void)
{
	/*
	 * Switch P1 -> PA8
	 * Switch P2 -> PA15
	 */
	GPIO_InitTypeDef gpioInitStruct = {0};
	__HAL_RCC_GPIOA_CLK_ENABLE();

	//* Switches GPIO Initialization
	gpioInitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_15; // GPIO PA8,PA15
	gpioInitStruct.Mode = GPIO_MODE_INPUT;				 // Input Mode
	gpioInitStruct.Pull = GPIO_NOPULL;						 // No Pull
	gpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;		 // Speed Low
	HAL_GPIO_Init(GPIOA, &gpioInitStruct);

	//? GPIOA15 -> (Defualt) JTAG Data pin -> Alternate function Remap
	__HAL_RCC_AFIO_CLK_ENABLE();
	__HAL_AFIO_REMAP_SWJ_DISABLE();
	//? JTAG Prog/DBG will be disabled (Prog by Enable Bootloader Pin)
}

bool gpio_SW1_read(void)
{
	// return input port pin value
	return (bool)HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8);
}

bool gpio_SW2_read(void)
{
	// return input port pin value
	return (bool)HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15);
}