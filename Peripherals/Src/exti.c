/*
 * exti.c
 *
 *  Created on: Dec 6, 2022
 *      Author: amornsak-ra
 */

#include "exti.h"

void exti_button_config(void)
{
  /*
  * Push Button Interrupt Pin -> PA0
  */

  GPIO_InitTypeDef gpioInitStruct = {0};
  __HAL_RCC_GPIOA_CLK_ENABLE();                 // Enable GPIOA Clock

  //* Push Button GPIO Initialization
  gpioInitStruct.Pin = GPIO_PIN_0;              // GPIO PA0
  gpioInitStruct.Mode = GPIO_MODE_IT_RISING;    // Interrupt Rising mode
  gpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;   // Speed low
  HAL_GPIO_Init(GPIOA, &gpioInitStruct);

  //* Enable Interrupt Pin
  HAL_NVIC_SetPriority(EXTI0_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}
