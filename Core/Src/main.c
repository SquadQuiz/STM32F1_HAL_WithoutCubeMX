/*
 * main.c
 *
 *  Created on: Dec 5, 2022
 *      Author: Squadkisz
 */

#include "main.h"
#include "rcc.h"
#include "uart.h"
#include "gpio.h"
#include "exti.h"
#include "adc.h"

bool buttonInterrupt = false;

int main(void)
{

	HAL_Init();

	//* RCC Peripheral
	rcc_systemClockConfig();

	//* UART Peripheral
	uart_UART1_GPIO_config();
	uart_UART1_config();

	//* GPIO Peripheral
	gpio_LED_config();
	gpio_PB_config();
	gpio_SW_config();

	//* EXTI Peripheral
	exti_button_config();

	//* ADC Peripheral

	printf("Program is Starting...\n");

	int counter = 0;
	while(1)
	{
		counter++;
		printf("Hello (%.4f), Counter %d\n", 12.45885, counter);

		//* LED
		// gpio_LED_toggleOrange();
		// HAL_Delay(100);
		// gpio_LED_toggleRed();
		// HAL_Delay(100);

		//* Push Button
		// gpio_LED_writeOrange(gpio_PB_read());
		// HAL_Delay(250);
		// gpio_LED_toggleRed();
		// HAL_Delay(250);

		//* Switches
		gpio_LED_writeOrange(gpio_SW1_read());
		gpio_LED_writeRed(gpio_SW2_read());
		if(buttonInterrupt)
		{
			buttonInterrupt = false;
			printf("EXTI0 - Gernated Interrupt\n");
			//User Code....
			//Unmask
			HAL_Delay(10);
			EXTI->IMR &= ~(1UL << 0);
		}
		HAL_Delay(250);
	}

}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_0)
	{
		buttonInterrupt = true;
		//Mask Interrupt
		EXTI->IMR &= ~(1UL << 0);
	}
}