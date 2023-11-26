/*
 * pwr.h
 *
 *  Created on: Nov 26, 2023
 *      Author: SquadQuiz
 */

#ifndef INC_PWR_H_
#define INC_PWR_H_

#include "main.h"

/**
 * @brief Enter Sleep mode
 */
void pwr_enterSleep(void);

/**
 * @brief Enter Stop mode
 */
void pwr_enterStop(void);

/**
 * @brief Enter Standby mode
 */
void pwr_enterStandby(void);

#endif /* INC_PWR_H_ */
