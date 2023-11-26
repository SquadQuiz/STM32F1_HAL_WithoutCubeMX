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
#include "i2c.h"
#include "TJ_MPU6050.h"
#include "crc.h"
#include "pwr.h"

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

	//* PWR 
	__HAL_RCC_PWR_CLK_ENABLE(); // Enable PWR Clock
	// Sleep mode example
	// Enable push button interrupt --> Wake-up
	exti_button_config();
	for (uint8_t i = 10; i > 0; i--)
	{
		printf("Entering Sleep mode in %d seconds\n", i);
		HAL_Delay(1000);
	}
	pwr_enterSleep();
	printf("Just woke-up on Sleep mode!\n");

	while (1)
	{
		gpio_LED_toggleGreen();
		HAL_Delay(250);
	}
}

