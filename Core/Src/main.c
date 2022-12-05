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

	printf("Program is Starting...\n");

	int counter = 0;
	while(1)
	{
		counter++;
		printf("Hello (%.4f), Counter %d\n", 12.45885, counter);
		HAL_Delay(100);
		gpio_LED_toggleLED();
		HAL_Delay(100);
	}

}
