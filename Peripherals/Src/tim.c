/*
 * tim.h
 *
 *  Created on: Dec 7, 2022
 *      Author: SquadQuiz
 */

#include "tim.h"

//* Handle Typedef Global Variable
TIM_HandleTypeDef htim3;

bool tim_TIM3_config(uint32_t msPeriod)
{
  __HAL_RCC_TIM3_CLK_ENABLE();                                      // Enable TIM3 Clock
  //* Timer Clock = 72 MHz

  //* TIM3 Configuration
  htim3.Instance = TIM3;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;                      // Mode Counter Up
  htim3.Init.Period = 7200-1;                                       // 10 kHz = 0.1 ms or 100 us
  htim3.Init.Prescaler = (msPeriod * 10) - 1;                       // (0.1 mS x 10) = 1 ms -> msPeriod ms
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;                // Division Clock with 1
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;    // Disable Auto-reload Preload
  if(HAL_TIM_Base_Init(&htim3) != HAL_OK)                           // Init Timebase TIM3
  {
    return false;
  }

  //* Clock Source Configuration
  TIM_ClockConfigTypeDef clockSrcConfig = {0};
  clockSrcConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;            // Internal CLK from RCC
  if(HAL_TIM_ConfigClockSource(&htim3, &clockSrcConfig) != HAL_OK)
  {
    return false;
  }

  //* TIM3 as TRGO mode **
  TIM_MasterConfigTypeDef masterClockConfig = {0};
  masterClockConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;          // Signal Trigger to ADC to do Conversion
  masterClockConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;  // Disable Master/Slave mode
  if(HAL_TIMEx_MasterConfigSynchronization(&htim3, &masterClockConfig) != HAL_OK)
  {
    return false;
  }

  return true;
}