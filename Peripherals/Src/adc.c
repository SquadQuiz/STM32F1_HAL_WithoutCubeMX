/*
 * adc.c
 *
 *  Created on: Dec 6, 2022
 *      Author: SquadQuiz
 */

#include "adc.h"

//* ADC1 Handle Typedef Global Variable
ADC_HandleTypeDef adc1Handle;
DMA_HandleTypeDef dmaHandle;

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

void adc_Interrupt_config(void)
{
  __HAL_ADC_ENABLE_IT(&adc1Handle, ADC_IT_EOC);               // Enable ADC Interrupt mode
  HAL_NVIC_SetPriority(ADC1_2_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(ADC1_2_IRQn);
}

bool adc_multiChannel_config(void)
{
  __HAL_RCC_ADC1_CLK_ENABLE();                                // Ebable ADC1 Clock
  //* ADC Configuration
  adc1Handle.Instance = ADC1;                                 // adc1Handle -> ADC1
  adc1Handle.Init.DataAlign = ADC_DATAALIGN_RIGHT;            // Data Align Right
  adc1Handle.Init.ScanConvMode = ADC_SCAN_ENABLE;             // Enable Scan mode
  adc1Handle.Init.ContinuousConvMode = DISABLE;               // Disable Continuous Conversion
  adc1Handle.Init.NbrOfConversion = 3;                        // Number of conversion = 3 
  adc1Handle.Init.DiscontinuousConvMode = DISABLE;            // Disable Discontinuous Conversion
  adc1Handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;      // External Trigger Software Start
  if(HAL_ADC_Init(&adc1Handle) != HAL_OK)
  {
    return false;
  }

  //* ADC Channel Configuration

  //* Channel1 PA1
  ADC_ChannelConfTypeDef channelConfig = {0};   
  channelConfig.Channel = ADC_CHANNEL_1;                      // Pot
  channelConfig.Rank = 1;                                     // Rank = 1
  channelConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES_5;     // Sampling Time = 28.5 Cycles
  if(HAL_ADC_ConfigChannel(&adc1Handle, &channelConfig) != HAL_OK)
  {
    return false;
  }

  //* Channel2 PA2
  channelConfig.Channel = ADC_CHANNEL_2;                      // Joy-X
  channelConfig.Rank = 2;                                     // Rank = 1
  channelConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES_5;     // Sampling Time = 28.5 Cycles
  if(HAL_ADC_ConfigChannel(&adc1Handle, &channelConfig) != HAL_OK)
  {
    return false;
  }
  
  //* Channel3 PA3
  channelConfig.Channel = ADC_CHANNEL_3;                      // Joy-Y
  channelConfig.Rank = 3;                                     // Rank = 1
  channelConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES_5;     // Sampling Time = 28.5 Cycles
  if(HAL_ADC_ConfigChannel(&adc1Handle, &channelConfig) != HAL_OK)
  {
    return false;
  }
  
  return true;
}

void adc_dma_config(void)
{
  __HAL_RCC_DMA1_CLK_ENABLE();                                  // Enable DMA1 Clock
  dmaHandle.Instance = DMA1_Channel1;                           // DMA1 Instance -> DMA1_CH1                          
  dmaHandle.Init.Direction = DMA_PERIPH_TO_MEMORY;              // Peripheral to Memory
  dmaHandle.Init.PeriphInc = DMA_PINC_DISABLE;                  // Peripheral increment mode Disable
  dmaHandle.Init.MemInc = DMA_MINC_ENABLE;                      // Memory increment mode Enable
  dmaHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD; // 16-bit
  dmaHandle.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;    // 16-bit      
  dmaHandle.Init.Mode = DMA_CIRCULAR;                           // Enable DMA Circular mode (Ring-Buffer)
  dmaHandle.Init.Priority = DMA_PRIORITY_MEDIUM;                // Priority Medium
  HAL_DMA_Init(&dmaHandle);
  __HAL_LINKDMA(&adc1Handle, DMA_Handle, dmaHandle);            // ADC Link to DMA
  //* Enable DMA Interrupt
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
}








