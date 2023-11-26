/*
 * crc.h
 *
 *  Created on: Nov 26, 2023
 *      Author: SquadQuiz
 */

#include "crc.h"

CRC_HandleTypeDef crcHandle;

bool crc_config(void)
{
  // Enable CRC Clock
  __HAL_RCC_CRC_CLK_ENABLE();
  crcHandle.Instance = CRC;
  if (HAL_CRC_Init(&crcHandle) != HAL_OK)
  {
    return false;
  }
  return true;
}