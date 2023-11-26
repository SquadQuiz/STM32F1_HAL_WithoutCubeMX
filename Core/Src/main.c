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
#include "spi.h"
#include "rc522.h"

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
	// gpio_PB_config();
	// gpio_SW_config();

	//* SPI Peripheral
	spi_GPIO_config();
	spi_config();

	//SPI Test
	for (uint8_t i = 0; i < 0x40; i++) 
	{
		printf("Register[0x%02X] = 0x%02X\n", i, rc522_regRead8(i));
		HAL_Delay(10);
	}

	while (1)
	{
		
		gpio_LED_toggleGreen();
		HAL_Delay(500);
	}
}

