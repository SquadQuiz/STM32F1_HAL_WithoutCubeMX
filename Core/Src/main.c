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

bool buttonInterrupt = false;
bool adcEOCFlag = false;
bool adcAWDGFlag = false;

uint16_t adcValues[3];

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

	//* TIM Peripheral
	//* TIM3 PWM
	tim_TIM3_PWM_GPIO_config();
	tim_TIM3_PWM_config();
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	// tim_PWM_setDutyCycle_CH1(50);
	// tim_PWM_setDutyCycle_CH2(30);
	// tim_PWM_setDutyCycle_CH3(100);
	uint8_t dutyCounter = 0;

	while(1)
	{
		//** Smooth blinking 2 LED
		if(dutyCounter == 100)
		{
			tim_PWM_setDutyCycle_CH1(0);
			for(dutyCounter = 100; dutyCounter != 0; dutyCounter--)
			{
				tim_PWM_setDutyCycle_CH2(dutyCounter);
				HAL_Delay(10);
			}
			tim_PWM_setDutyCycle_CH2(0);
			dutyCounter = 0;
		}
		tim_PWM_setDutyCycle_CH1(dutyCounter);
		dutyCounter++;
		HAL_Delay(10);
	}
}

/**
 * @brief GPIO EXTI Callback Function
 * 
 * @param GPIO_Pin 
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_0)
	{
		buttonInterrupt = true;
		//Mask Interrupt
		EXTI->IMR &= ~(1UL << 0);
	}
}

/**
 * @brief ADC Conversion Complete Callback Function
 * 
 * @param hadc Pointer to ADC Handle Typedef 
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	adcEOCFlag = true;
}

/**
 * @brief ADC Analog Watchdog Interrupt Callback Function
 * 
 * @param hadc 
 */
void HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef *hadc)
{
	if(hadc->Instance == ADC1)
	{
		adcAWDGFlag = true;
	}
}

/**
 * @brief TIM Period Elaseed Interrupt Callback Function
 * 
 * @param htim 
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM3)
	{
		// gpio_LED_toggleGreen();
	}
}