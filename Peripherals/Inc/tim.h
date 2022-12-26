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
extern TIM_HandleTypeDef htim4;

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

/**
 * @brief TIM3 PWM GPIO Configuration
 ** LED Red   -> PB4
 ** LED Green -> PB5
 ** LED Blue  -> PB0
 */
void tim_TIM3_PWM_GPIO_config(void);

/**
 * @brief TIM3 PWM Configuration
 * @return True, False
 */
bool tim_TIM3_PWM_config(void);

/**
 * @brief TIM3 PWM Channel-1 Set DutyCycle
 ** LED Red   -> PB4
 * @param duty_0_100 : DutyCycle value 0-100
 */
void tim_PWM_setDutyCycle_CH1(uint8_t duty_0_100);

/**
 * @brief TIM3 PWM Channel-2 Set DutyCycle
 ** LED Green  -> PB5
 * @param duty_0_100 : DutyCycle value 0-100
 */
void tim_PWM_setDutyCycle_CH2(uint8_t duty_0_100);

/**
 * @brief TIM3 PWM Channel-3 Set DutyCycle
 ** LED Blue  -> PB0
 * @param duty_0_100 : DutyCycle value 0-100
 */
void tim_PWM_setDutyCycle_CH3(uint8_t duty_0_100);

/**
 * @brief TIM3 PWM RGB DutyCycle
 * 
 * @param red 
 * @param green 
 * @param blue 
 */
void tim_PWM_setRGB(uint8_t red, uint8_t green, uint8_t blue);

/**
 * @brief TIM4 Encoder GPIO Configuration
 */
void tim_TIM4_ENCODER_GPIO_config(void);

/**
 * @brief TIM4 Encoder Configuration
 * 
 * @return true, false
 */
bool tim_TIM4_ENCODER_config(void);

#endif /* INC_TIM_H_ */