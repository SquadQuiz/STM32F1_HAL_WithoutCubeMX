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
#include "tim.h"
#include "rtc.h"

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

	uint8_t rxBuffer[10];
	printf("Send 10 bytes please\n");

	while (1)
	{
		if (HAL_UART_Receive(&huart1, rxBuffer, 10, HAL_MAX_DELAY) == HAL_OK) 
		{
			HAL_UART_Transmit(&huart1, rxBuffer, 10, 20);
		}
	}
}
