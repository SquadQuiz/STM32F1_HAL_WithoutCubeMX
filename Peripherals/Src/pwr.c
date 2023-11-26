/*
 * pwr.c
 *
 *  Created on: Nov 26, 2023
 *      Author: SquadQuiz
 */

#include "pwr.h"
#include "rcc.h"

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

void pwr_enterStop(void)
{
  // Suspend SysTick
  HAL_SuspendTick();
  // Disable Sleep On Exit (Sleep on exit)
  HAL_PWR_DisableSleepOnExit();
  // Enter Stop mode
  HAL_PWR_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
  // HSE
  rcc_systemClockConfig(); // re-initialized clock
  // Resume SysTick
  HAL_ResumeTick();
}
