/*
 * adc.c
 *
 *  Created on: Dec 6, 2022
 *      Author: SquadQuiz
 */

#include "adc.h"

//* ADC1 Handle Typedef Global Variable
ADC_HandleTypeDef adc1Handle;

void adc_GPIO_config(void)
{
  /*
   * Potentiometer -> PA1
   * Joystick-X    -> PA2
   * Joystick-Y    -> PA3
  */  

  GPIO_InitTypeDef gpioInitStruct = {0};
  __HAL_RCC_GPIOA_CLK_ENABLE();                               // Enable GPIOA Clock

  //* ADC GPIO Initialization
  gpioInitStruct.Pin = GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;  // GPIO PA1,PA2,PA3
  gpioInitStruct.Mode = GPIO_MODE_ANALOG;                     // Analog Mode
  gpioInitStruct.Pull = GPIO_NOPULL;                          // No Pull
  HAL_GPIO_Init(GPIOA, &gpioInitStruct);
}

bool adc_singleChannel_config(ADC_SingleSelect_e channel)
{
  __HAL_RCC_ADC1_CLK_ENABLE();                                // Enable ADC1 Clock

  //* ADC Configuration
  adc1Handle.Instance = ADC1;                                 // adc1Handle -> ADC1
  adc1Handle.Init.DataAlign = ADC_DATAALIGN_RIGHT;            // Data Align Right
  adc1Handle.Init.ScanConvMode = ADC_SCAN_DISABLE;            // Disable Scan mode
  adc1Handle.Init.ContinuousConvMode = DISABLE;               // Disable Continuous Conversion
  adc1Handle.Init.NbrOfConversion = 1;                        // Number of conversion = 1
  adc1Handle.Init.DiscontinuousConvMode = DISABLE;            // Disable Discontinuous Conversion
  adc1Handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;      // External Trigger Software Start
  if(HAL_ADC_Init(&adc1Handle) != HAL_OK)
  {
    return false;
  }

  //* ADC Channel Configuration
  ADC_ChannelConfTypeDef channelConfig = {0};                 
  channelConfig.Channel = channel;                            // Pot,Joy-X,Joy-Y
  channelConfig.Rank = 1;                                     // Rank = 1
  channelConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES_5;     // Sampling Time = 28.5 Cycles
  //* ADC Clock = 12 MHz 
  //? Tconv = Sampling time + 12.5 Cycles
  //? Tconv = 28.5 + 12.5 = 41 Cycles
  //* --> 41 * (1/12) = 41 * (0.083) = 3.416 uS
  if(HAL_ADC_ConfigChannel(&adc1Handle, &channelConfig) != HAL_OK)
  {
    return false;
  }

  return true;
}