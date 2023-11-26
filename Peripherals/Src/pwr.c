/*
 * pwr.c
 *
 *  Created on: Nov 26, 2023
 *      Author: SquadQuiz
 */

#include "pwr.h"

void pwr_enterSleep(void)
{
  // Suspend SysTick
  HAL_SuspendTick();
  // Disable Sleep On Exit (Sleep now)
  HAL_PWR_DisableSleepOnExit();
  // Enter Sleep (WFI - Wait for Interrupt)
  HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI); 
  // Resume SysTick
  HAL_ResumeTick();
}


