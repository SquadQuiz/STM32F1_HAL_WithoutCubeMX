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

/**
 * @brief typedef enumuration for ADC Channel Selection
 * 
 */
typedef enum ADC_SingleSelect_TAG
{
  ADC_SingleSelect_Potentiometer = 1,
  ADC_SingleSelect_Joystick_x,
  ADC_SingleSelect_Joystick_y
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

#endif /* INC_ADC_H_ */


