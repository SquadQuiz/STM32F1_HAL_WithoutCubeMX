/*
 * crc.h
 *
 *  Created on: Nov 26, 2023
 *      Author: SquadQuiz
 */

#ifndef INC_CRC_H_
#define INC_CRC_H_

#include "main.h"

extern CRC_HandleTypeDef crcHandle;

/**
 * @brief CRC Configuration
 */
bool crc_config(void);

#endif /* INC_CRC_H_ */
