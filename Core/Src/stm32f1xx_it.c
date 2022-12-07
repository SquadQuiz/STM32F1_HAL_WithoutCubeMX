/*
 * stm32f1xx_it.c
 *
 *  Created on: Dec 5, 2022
 *      Author: Squadkisz
 */

#include "main.h"
#include "stm32f1xx_it.h"
#include "adc.h"

void SysTick_Handler(void)
{
	HAL_IncTick();
}

void EXTI0_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

//* Disabled when use ADC Multi-channel with DMA
// void ADC1_2_IRQHandler(void)
// {
// 	HAL_ADC_IRQHandler(&adc1Handle);
// }

void DMA1_Channel1_IRQHandler(void)
{
	HAL_DMA_IRQHandler(adc1Handle.DMA_Handle);
}