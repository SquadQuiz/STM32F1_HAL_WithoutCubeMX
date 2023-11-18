/*
 * stm32f1xx_it.h
 *
 *  Created on: Dec 5, 2022
 *      Author: Squadkisz
 */

#ifndef INC_STM32F1XX_IT_H_
#define INC_STM32F1XX_IT_H_

/**
 * @brief System Tick
 */
void SysTick_Handler(void);

/**
 * @brief EXTI0 Callback 
 */
void EXTI0_IRQHandler(void);

/**
 * @brief ADC Callback
 */
void ADC1_2_IRQHandler(void);

/**
 * @brief ADC1 -> DMA1 Callback
 */
void DMA1_Channel1_IRQHandler(void);

/**
 * @brief TIM3 Callback
 */
void TIM3_IRQHandler(void);

/**
 * @brief RTC Alarm Callback.
 * 
 */
void RTC_Alarm_IRQHandler(void);

#endif /* INC_STM32F1XX_IT_H_ */
