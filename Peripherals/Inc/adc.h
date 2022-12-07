/*
 * adc.h
 *
 *  Created on: Dec 6, 2022
 *      Author: SquadQuiz
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

#include "main.h"

//* Import External Variable
extern ADC_HandleTypeDef adc1Handle;
extern DMA_HandleTypeDef dmaHandle;

/**
 * @brief typedef enumuration for ADC Channel Selection
 */
typedef enum ADC_SingleSelect_TAG
{
  ADC_SingleSelect_Potentiometer = 1,
  ADC_SingleSelect_Joystick_X,
  ADC_SingleSelect_Joystick_Y
} ADC_SingleSelect_e;

/**
 * @brief ADC Channel GPIO Configuration
 ** Potentiometer -> PA1
 ** Joystick-X    -> PA2
 ** Joystick-Y    -> PA3
 */
void adc_GPIO_config(void);

/**
 * @brief ADC Single Channel Configuration
 * 
 * @param channel 
 * @return true 
 * @return false 
 */
bool adc_singleChannel_config(ADC_SingleSelect_e channel);

/**
 * @brief ADC Interrupt Module Configuration
 */
void adc_Interrupt_config(void);

/**
 * @brief ADC Multi Channel Configuration
 ** Potentiometer -> PA1
 ** Joystick-X    -> PA2
 ** Joystick-Y    -> PA3
 * @retval true, false
 */
bool adc_multiChannel_config(void);

/**
 * @brief ADC1 -> DMA Configuration
 * 
 */
void adc_dma_config(void);

/**
 * @brief ADC AWDG Configuration
 * 
 * @param channel 
 * @return true 
 */
bool adc_AWDG_config(ADC_SingleSelect_e channel);

#endif /* INC_ADC_H_ */


