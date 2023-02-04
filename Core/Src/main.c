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

	//* RTC Peripheral
	rtc_config();

	//* Time initialze
	ClockTime_t timDef;
	timDef.hrs24 = 16;
	timDef.minutes = 53;
	timDef.seconds = 24;
	rtc_setTime(&timDef); // set RTC time.

	//* Date intialize
	ClockDate_t dateDef;
	// dateDef.dayOfWk = 0; // don't need to set this
	dateDef.day = 18;
	dateDef.month = 12;
	dateDef.year = 2020;
	rtc_setDate(&dateDef); // set RTC date.

	printf("Program is Starting\r\n");

	while (1)
	{
		rtc_getTimeDate(&timDef, &dateDef);																								 // get time and date from RTC module.
		printf("Weekdate: %s \r\n", daysOfWkString[dateDef.dayOfWk - 1]);									 // displaying weekday.
		printf("Date: %02u-%02u-%04u\r\n", dateDef.day, dateDef.month, dateDef.year);			 // displaying date: (date/mounth/year)
		printf("Time : %02u:%02u:%02u\r\n", timDef.hrs24, timDef.minutes, timDef.seconds); // displaying time (second/minute/hour)
		HAL_Delay(1000);																																	 // add delay to display every second.
	}
}
