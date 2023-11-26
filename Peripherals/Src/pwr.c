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
  // Enable Sleep On Exit (Sleep on exit)
  HAL_PWR_EnableSleepOnExit();
  // Enter Sleep (WFI - Wait for Interrupt)
  HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI); 
  // Resume SysTick
  HAL_ResumeTick();
}


