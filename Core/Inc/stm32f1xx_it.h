/*
 * stm32f1xx_it.h
 *
 *  Created on: Dec 5, 2022
 *      Author: Squadkisz
 */

#ifndef INC_STM32F1XX_IT_H_
#define INC_STM32F1XX_IT_H_

/**
 * @brief 
 */
void SysTick_Handler(void);

/**
 * @brief EXTI0 Callback function
 */
void EXTI0_IRQHandler(void);

#endif /* INC_STM32F1XX_IT_H_ */
