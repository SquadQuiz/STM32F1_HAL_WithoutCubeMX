/*
 * i2c.h
 *
 *  Created on: Nov 26, 2023
 *      Author: SquadQuiz
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_

#include "main.h"

extern I2C_HandleTypeDef i2c1Handle;

/**
 * @brief I2C1 GPIO Configuration
 */
void i2c_I2C1_gpio_config(void);

/**
 * @brief I2C1 Configuration
 */
bool i2c_config(void);

#endif /* INC_I2C_H_ */
