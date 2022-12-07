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

	//* EXTI Peripheral
	// exti_button_config();

	//* ADC Peripheral
	//* ADC Multi-channel
	adc_GPIO_config();
	adc_multiChannel_config();
	adc_dma_config();
	HAL_ADC_Start_DMA(&adc1Handle, (uint32_t *)adcValues, 3);
	//* ADC with Timer Trigger
	tim_TIM3_config(50);
	HAL_TIM_Base_Start(&htim3);
	//* ADC with ADWG IT
	adc_AWDG_config(ADC_SingleSelect_Potentiometer);

	printf("Program is Starting...\r\n");

	while(1)
	{
		//* Multi Channel ADC
		if (adcEOCFlag)
		{
			adcEOCFlag = false;
			//* Read/Get ADC Values
			printf("ADC Values : \r\n");
			printf(" PA1 Pot   = %d\r\n", adcValues[0]);
			printf(" PA2 Joy-X = %d\r\n", adcValues[1]);
			printf(" PA3 Joy-Y = %d\r\n", adcValues[2]);
			gpio_LED_toggleGreen();

			if (adcAWDGFlag)
			{
				adcAWDGFlag = false;
				printf("ADC Watchdog Threshold Triggered!\r\n");
				HAL_Delay(500);
			}
		}
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
 * @brief ADC Analog Watchdog Interrupt Callback Functiopn
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