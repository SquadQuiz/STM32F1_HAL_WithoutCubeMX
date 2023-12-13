/*
 * tim.h
 *
 *  Created on: Dec 7, 2022
 *      Author: SquadQuiz
 */

#include "tim.h"

//* Handle Typedef Global Variable
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

bool tim_TIM3_config(uint32_t msPeriod)
{
  __HAL_RCC_TIM3_CLK_ENABLE();                                      // Enable TIM3 Clock
  //* Timer Clock = 72 MHz

  // Audio sampling frequency as 44.1 KHz

  //* TIM3 Configuration
  htim3.Instance = TIM3;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;                      // Mode Counter Up
  htim3.Init.Period = 1632-1;                                       // 44.1 KHz
  htim3.Init.Prescaler = 0;                       									//
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
  /*
   * TIM3_CH1 -> PB13
   * TIM4_CH2 -> PB14
   */

  //* TIM4 Output Compare GPIO Configuration
  GPIO_InitTypeDef gpioConfig = {0};
  __HAL_RCC_GPIOB_CLK_ENABLE();                                       // Enable GPIOB Clock

  gpioConfig.Pin = GPIO_PIN_13 | GPIO_PIN_14;                         // GPIO PB13,PB14
  gpioConfig.Mode = GPIO_MODE_AF_PP;                                  // GPIO Alternate function push-pull
  gpioConfig.Speed = GPIO_SPEED_FREQ_LOW;                             // PinSpeed -> Low
  HAL_GPIO_Init(GPIOB, &gpioConfig);
}

bool tim_TIM1_OC_config(uint32_t msPeriod)
{
  __HAL_RCC_TIM1_CLK_ENABLE();

  //* TIM3 Configuration
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

  //* TIM3 Output Comppare Channel Settings
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

void tim_TIM3_PWM_GPIO_config(void)
{
  /*
  !Pin-Remapped
  * LED Red   -> PB4
  * LED Green -> PB5
  * LED Blue  -> PB0
  */
  
  //* TIM3 PWM GPIO Configuration
  GPIO_InitTypeDef gpioConfig = {0};
  __HAL_RCC_GPIOB_CLK_ENABLE();
  
  gpioConfig.Pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_0;
  gpioConfig.Mode = GPIO_MODE_AF_PP;
  gpioConfig.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &gpioConfig);
  //* GPIO Re-map -> TIM3 Partial Remap
  __HAL_RCC_AFIO_CLK_ENABLE();
  __HAL_AFIO_REMAP_TIM3_PARTIAL();
}

bool tim_TIM3_PWM_config(void)
{
  __HAL_RCC_TIM3_CLK_ENABLE();

  //* TIM3 PWM Configuration
  htim3.Instance = TIM3;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;                      // Mode Counter Up
  htim3.Init.Period = 200-1;                                        // 10 kHz 
  htim3.Init.Prescaler = 36-1;                                      // 2 MHz
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

  //* TIM3 PWM Configuration
  HAL_TIM_PWM_Init(&htim3);
  TIM_OC_InitTypeDef ocConfig = {0};
  ocConfig.OCMode = TIM_OCMODE_PWM1;
  ocConfig.Pulse = 0;
  ocConfig.OCPolarity = TIM_OCPOLARITY_HIGH;
  ocConfig.OCFastMode = TIM_OCFAST_DISABLE;

  //* TIM3 PWM CH1
  if(HAL_TIM_PWM_ConfigChannel(&htim3, &ocConfig, TIM_CHANNEL_1) != HAL_OK)
  {
    return false;
  }

  //* TIM3 PWM CH2
  if(HAL_TIM_PWM_ConfigChannel(&htim3, &ocConfig, TIM_CHANNEL_2) != HAL_OK)
  {
    return false;
  }

  //* TIM3 PWM CH3
  if(HAL_TIM_PWM_ConfigChannel(&htim3, &ocConfig, TIM_CHANNEL_3) != HAL_OK)
  {
    return false;
  }

  return true;
}

void tim_PWM_setDutyCycle_CH1(uint8_t duty_0_100)
{
  if(duty_0_100 > 100) duty_0_100 = 100;
  uint16_t ccrValue = (__HAL_TIM_GET_AUTORELOAD(&htim3) + 0.0f) * (duty_0_100 / 100.0f);
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, ccrValue);
}

void tim_PWM_setDutyCycle_CH2(uint8_t duty_0_100)
{
  if(duty_0_100 > 100) duty_0_100 = 100;
  uint16_t ccrValue = (__HAL_TIM_GET_AUTORELOAD(&htim3) + 0.0f) * (duty_0_100 / 100.0f);
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, ccrValue);
}

void tim_PWM_setDutyCycle_CH3(uint8_t duty_0_100)
{
  if(duty_0_100 > 100) duty_0_100 = 100;
  uint16_t ccrValue = (__HAL_TIM_GET_AUTORELOAD(&htim3) + 0.0f) * (duty_0_100 / 100.0f);
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, ccrValue);
}

void tim_PWM_setRGB(uint8_t red, uint8_t green, uint8_t blue)
{
  tim_PWM_setDutyCycle_CH1(100 * (red / 255.0f));
  tim_PWM_setDutyCycle_CH2(100 * (green / 255.0f));
  tim_PWM_setDutyCycle_CH3(100 * (blue / 255.0f));
}

void tim_TIM4_ENCODER_GPIO_config(void)
{
  /*
  * TIM4_CH1 -> PB6
  * TIM4_CH2 -> PB7
  */

  //* TIM4 Encoder GPIO Configuration
  GPIO_InitTypeDef gpioConfig = {0};
  __HAL_RCC_GPIOB_CLK_ENABLE();                                     // Enable GPIOB Clock
  
  gpioConfig.Pin = GPIO_PIN_6 | GPIO_PIN_7;                         // GPIO PB6,PB7
  gpioConfig.Mode = GPIO_MODE_INPUT;                                // GPIO Input mode
  gpioConfig.Pull = GPIO_NOPULL;                                    // No Pull-up
  HAL_GPIO_Init(GPIOB, &gpioConfig);
}

/**
 * @brief TIM4 Encoder Configuration
 * 
 * @return true, false
 */
bool tim_TIM4_ENCODER_config(void)
{
  __HAL_RCC_TIM4_CLK_ENABLE();                                      // Enable TIM4 Clock
  
  htim4.Instance = TIM4;                                            // TIM->TIM4
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;                      // Mode Counter Up
  htim4.Init.Period = 65536-1;                                      // Period = 16 bit
  htim4.Init.Prescaler = 0;                                         // Prescaler = 0
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;                // Clouck Division by 1
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;    // Disable Auto-reload 

  //* TIM4 Encoder Configuration
  TIM_Encoder_InitTypeDef encoderConfig = {0};
  encoderConfig.EncoderMode = TIM_ENCODERMODE_TI1;                  // Encoder mode TI1
  //* TIM4 Encoder CH1
  encoderConfig.IC1Polarity = TIM_ICPOLARITY_RISING;                // Input capture CH1 Rising
  encoderConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;            // Input Capture CH1 Direct
  encoderConfig.IC1Prescaler = TIM_ICPSC_DIV1;                      // Input Capture CH1 Pre-scaler
  encoderConfig.IC1Filter = 4;                                      // Input Capture CH1 Filter
  //* TIM4 Encoder CH2
  encoderConfig.IC2Polarity = TIM_ICPOLARITY_RISING;                // Input capture CH2 Rising
  encoderConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;            // Input Capture CH2 Direct
  encoderConfig.IC2Prescaler = TIM_ICPSC_DIV1;                      // Input Capture CH2 Pre-scaler
  encoderConfig.IC2Filter = 4;                                      // Input Capture CH2 Filter
  if(HAL_TIM_Encoder_Init(&htim4, &encoderConfig) != HAL_OK)
  {
    return false;
  }
  return true;
}

bool tim_TIM2_config(void)
{
	 __HAL_RCC_TIM2_CLK_ENABLE();                                      // Enable TIM3 Clock
	  //* Timer Clock = 72 MHz

	  //* TIM3 Configuration
	  htim2.Instance = TIM2;
	  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;                      // Mode Counter Up
	  htim2.Init.Period = 1000-1;                                       // 10 kHz = 0.1 ms or 100 us
	  htim2.Init.Prescaler = 72 - 1;                       							// (0.1 mS x 10) = 1 ms -> msPeriod ms
	  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;                // Division Clock with 1
	  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;    // Disable Auto-reload Preload
	  if(HAL_TIM_Base_Init(&htim2) != HAL_OK)                           // Init Timebase TIM3
	  {
	    return false;
	  }

	  //* Clock Source Configuration
	  TIM_ClockConfigTypeDef clockSrcConfig = {0};
	  clockSrcConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;            // Internal CLK from RCC
	  if(HAL_TIM_ConfigClockSource(&htim2, &clockSrcConfig) != HAL_OK)
	  {
	    return false;
	  }

	  //* TIM3 as TRGO mode **
	  TIM_MasterConfigTypeDef masterClockConfig = {0};
	  masterClockConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;          // Signal Trigger to ADC to do Conversion
	  masterClockConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;  // Disable Master/Slave mode
	  if(HAL_TIMEx_MasterConfigSynchronization(&htim2, &masterClockConfig) != HAL_OK)
	  {
	    return false;
	  }
	  //* Enable TIM3 Interrupt
	  HAL_NVIC_SetPriority(TIM2_IRQn, 5, 0);
	  HAL_NVIC_EnableIRQ(TIM2_IRQn);

	  HAL_TIM_Base_Start_IT(&htim2);
	  return true;
}
