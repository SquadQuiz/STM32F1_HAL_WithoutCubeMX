/*
 * stm32f1xx_it.c
 *
 *  Created on: Dec 5, 2022
 *      Author: Squadkisz
 */

#include "main.h"
#include "stm32f1xx_it.h"

void SysTick_Handler(void)
{
	HAL_IncTick();
}