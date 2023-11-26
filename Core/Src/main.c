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

	//* CRC Peripheral
	crc_config();
	uint32_t crcBuf[2] = {0x00110022, 0x00330044};
	uint32_t crcValue = HAL_CRC_Calculate(&crcHandle, crcBuf, 2);
	printf("CRC Value = 0x%08X\n", crcValue);

	while (1)
	{
		
	}
}

