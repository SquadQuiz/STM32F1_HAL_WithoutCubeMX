/*
 * tim.h
 *
 *  Created on: Dec 7, 2022
 *      Author: SquadQuiz
 */

#include "tim.h"

//* Handle Typedef Global Variable
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim1;

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
  //* Enable TIM3 Interrupt
  HAL_NVIC_SetPriority(TIM3_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(TIM3_IRQn);
  return true;
}

void tim_TIM1_OC_GPIO_config(void)
{
  GPIO_InitTypeDef gpioConfig = {0};
  __HAL_RCC_GPIOB_CLK_ENABLE();                                       // Enable GPIOB Clock
  //*PB13, PB14
  gpioConfig.Pin = GPIO_PIN_13 | GPIO_PIN_14;                         // GPIO PB13,PB14
  gpioConfig.Mode = GPIO_MODE_AF_PP;                                  // GPIO Alternate function push-pull
  gpioConfig.Speed = GPIO_SPEED_FREQ_LOW;                             // PinSpeed -> Low
  HAL_GPIO_Init(GPIOB, &gpioConfig);
}

bool tim_TIM1_OC_config(uint32_t msPeriod)
{
  __HAL_RCC_TIM1_CLK_ENABLE();

  htim1.Instance = TIM1;                                              // Enable TIM1 Clock
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;                        // Mode Counter-mode Up
  htim1.Init.Period = 7200-1;                                         // Period
  htim1.Init.Prescaler = (msPeriod*10) - 1;                           // (0.1 mS x 10) = 1 ms -> msPeriod ms
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;                  // Division Clock with 1
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;      // Auto-reload Disable
  if(HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    return false;
  }

  if(HAL_TIM_OC_Init(&htim1) != HAL_OK)
  {
    return false;
  }

  //* Output Comppare Channel Settings
  TIM_OC_InitTypeDef ocConfig = {0};
  ocConfig.OCMode = TIM_OCMODE_TOGGLE;                                // TIM OC Toggle
  ocConfig.Pulse = 2000-1;                                            // Pulse = 2000
  ocConfig.OCPolarity = TIM_OCPOLARITY_HIGH;                          // Polarity High
  ocConfig.OCNPolarity = TIM_OCPOLARITY_HIGH;                         // Polarity High
  ocConfig.OCFastMode = TIM_OCFAST_DISABLE;                           // OC Fast Disable
  ocConfig.OCIdleState = TIM_OCIDLESTATE_RESET;                       // OC Idlestate Reset
  ocConfig.OCNIdleState = TIM_OCIDLESTATE_RESET;                      // OC Idlestate Reset
  if(HAL_TIM_OC_ConfigChannel(&htim1, &ocConfig, TIM_CHANNEL_1) != HAL_OK)
  {
    return false;
  }

  ocConfig.Pulse = 5000-1;
  if(HAL_TIM_OC_ConfigChannel(&htim1, &ocConfig, TIM_CHANNEL_2) != HAL_OK)
  {
    return false;
  }

  return true;
}