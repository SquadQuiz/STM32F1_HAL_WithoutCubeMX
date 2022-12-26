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
	//* TIM4 Encoder Mode
	tim_TIM4_ENCODER_GPIO_config();
	tim_TIM4_ENCODER_config();
	printf("Starting TIM Encoder...\r\n");
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_1);
	
	int encoderCount;
	uint8_t encoderDir;

	printf("Program Starting\r\n");

	while(1)
	{
		encoderCount = __HAL_TIM_GET_COUNTER(&htim4); // TIM4->CNT Register
		encoderDir = (TIM4->CR1 & TIM_CR1_DIR) == 0 ? 0:1;
		printf("Encoder Counter = %d\r\n", encoderCount);
		printf("Direction: %s\r\n", encoderDir == 0 ? "CCW" : "CW");
		HAL_Delay(250);
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