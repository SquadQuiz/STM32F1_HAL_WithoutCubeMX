/*
 * tim.h
 *
 *  Created on: Dec 7, 2022
 *      Author: SquadQuiz
 */

#ifndef INC_TIM_H_
#define INC_TIM_H_

#include "main.h"

//* Import External Variable
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim1;

/**
 * @brief TIM3 TRGO mode Configuration
 * @param msPeriod : time to trigger ADC Conversion in ms unit
 * @retval True, False
 */
bool tim_TIM3_config(uint32_t msPeriod);

/**
 * @brief TIM1 Output Compre GPIO 
 */
void tim_TIM1_OC_GPIO_config(void);

/**
 * @brief TIM Output Compre Peripheral Configuration
 */
bool tim_TIM1_OC_config(uint32_t msPeriod);


#endif /* INC_TIM_H_ */