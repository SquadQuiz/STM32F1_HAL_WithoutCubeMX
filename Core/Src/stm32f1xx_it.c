/*
 * stm32f1xx_it.c
 *
 *  Created on: Dec 5, 2022
 *      Author: Squadkisz
 */

#include "main.h"
#include "stm32f1xx_it.h"
#include "adc.h"
#include "tim.h"
#include "rtc.h"
#include "uart.h"

/**
 * @brief System Tick Handler.
 */
void SysTick_Handler(void)
{
	HAL_IncTick();
}

/**
 * @brief GPIO EXTI0 IRQ Handler.
 */
void EXTI0_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

/**
 * @brief ADC 1_2 IRQ Handler.
 * @note Disabled when use ADC Multi-channel with DMA
 */
void ADC1_2_IRQHandler(void)
{
	HAL_ADC_IRQHandler(&adc1Handle);
}

/**
 * @brief DMA1 Channel 1 (ADC1) IRQ handler.
 */
void DMA1_Channel1_IRQHandler(void)
{
	HAL_DMA_IRQHandler(adc1Handle.DMA_Handle);
}

/**
 * @brief TIM3 IRQ Handler.
 */
void TIM3_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&htim3);
}

/**
 * @brief RTC Alarm Handler.
 */
void RTC_Alarm_IRQHandler(void)
{
	HAL_RTC_AlarmIRQHandler(&rtcHandle);
}

/**
 * @brief DMA Channel 4 (UART1 Tx) IRQ Handler.
 */
void DMA1_Channel4_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&dmaHandle_uart1_tx);
}

/**
 * @brief DMA Channel 5 (UART1 Rx) IRQ Handler.
 */
void DMA1_Channel5_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&dmaHandle_uart1_rx);
}

/**
 * @brief USART1 IRQ Handler.
 */
void USART1_IRQHandler(void)
{
	HAL_UART_IRQHandler(&huart1);
}