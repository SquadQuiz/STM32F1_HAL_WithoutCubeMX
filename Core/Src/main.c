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
#include "fatfs.h"
#include "sd_driver.h"
#include "usb_device.h"
#include "cmsis_os.h"

// Thread1
osThreadId thread1Handle;
void Thread1Callback(void const* argument);

// Thread2
osThreadId thread2Handle;
void Thread2Callback(void const* argument);


int main(void)
{
	//* HAL Library
	HAL_Init();

	//* RCC Peripheral
	rcc_systemClockConfig();

	//* UART Peripheral
	uart_UART1_GPIO_config();
	uart_UART1_config();

	//* GPIO Peripheral
	gpio_LED_config();
	gpio_PB_config();

	//* Timebase will use Timer2
	tim_TIM2_config();

	//* FreeRTOS Initialization

	// Thread1
	osThreadDef(Thread1, Thread1Callback, osPriorityNormal, 0, 128);
	thread1Handle = osThreadCreate(osThread(Thread1), NULL);

	// Thread2
	osThreadDef(Thread2, Thread2Callback, osPriorityNormal, 0, 128);
	thread2Handle = osThreadCreate(osThread(Thread2), NULL);

	// Start Scheduler
	osKernelStart();

	while (1)
	{

	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM2)
	{
		HAL_IncTick(); // now HAL_Delay() will use Timer2
	}
}

// Thread1 function
void Thread1Callback(void const* argument)
{
	// Super loop for thread1
	while(1)
	{
		gpio_LED_toggleGreen();
		printf("Thread1 Blinking!\n");
//		HAL_Delay(1000);
		osDelay(500);
	}
}

// Thread2 function
void Thread2Callback(void const* argument)
{
	// Super loop for thread2
	while(1)
	{
		gpio_LED_toggleGreen();
		printf("Thread2 ...!\n");
		osDelay(100);
	}
}
