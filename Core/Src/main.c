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

	//* Flash Periheral
	FLASH_EraseInitTypeDef eraseDef;
	eraseDef.PageAddress = 0x08007C00; // PAGE 31 (1KB Per Page)
	eraseDef.NbPages = 1; // 1 Page 
	eraseDef.TypeErase = FLASH_TYPEERASE_PAGES;
	uint32_t pageErr = 0;

	// 1 Unlock Flash
	HAL_FLASH_Unlock();
	// 2 Erase Flash
	HAL_FLASHEx_Erase(&eraseDef, &pageErr);
	// 3 Program Flash/Write
	uint16_t dataWrite[2] = { 0x1234, 0x4321 };
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, 0x08007C00, dataWrite[0]); // uint16_t = HALFWORD
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, 0x08007C00 + 2, dataWrite[1]); // offset 2 
	// 4 Lock Flash
	HAL_FLASH_Lock();
	// 5 Read
	uint16_t readData[2];
	readData[0] = *(__IO uint16_t*)(0x08007C00);
	readData[1] = *(__IO uint16_t*)(0x08007C00 + 2);
	printf("Flash Read data: 0x%04X, 0x%04X\n", readData[0], readData[1]);

	while (1)
	{
		gpio_LED_toggleGreen();
		HAL_Delay(250);
	}
}