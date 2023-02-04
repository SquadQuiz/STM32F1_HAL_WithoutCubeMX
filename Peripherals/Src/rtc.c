/*
 * rtc.c
 *
 *  Created on: Jan 21, 2023
 *      Author: SquadQuiz
 */

#include "rtc.h"

//* Handle Typedef Global Variable
RTC_HandleTypeDef rtcHandle;

//* Weekday const string array.
const char *daysOfWkString[7] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};

/**
 * @brief RTC Configuration.
 *
 */
bool rtc_config(void)
{
  //* RTC Using LSE Clock (32.768 kHz)
  //@note 32,768 = 256 x 128 = 8 bit x 7 bit.
  __HAL_RCC_RTC_ENABLE();     // Enable RCC LSE Clock for RTC Peripheral.
  HAL_PWR_EnableBkUpAccess(); // Enable power for back-up
  __HAL_RCC_BKP_CLK_ENABLE(); // Enable Back-up clock

  //* RTC Configuration
  rtcHandle.Instance = RTC;
  rtcHandle.Init.AsynchPrediv = RTC_AUTO_1_SECOND; // Set RTC Auto-reload eqaul to 1 sec.
  rtcHandle.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;  // Alarm pulse signal on the TAMPER pin "PC13"

  // avoid RTC re-initialization
  if ((RCC->BDCR & RCC_BDCR_RTCEN) == 0) // if RTC clock is not enable
  {
    if (HAL_RTC_Init(&rtcHandle) != HAL_OK) // initialze RTC.
    {
      return false;
    }
  }
  return true;
}

/**
 * @brief RTC set time.
 *
 */
void rtc_setTime(ClockTime_t *pTime)
{
  RTC_TimeTypeDef timDef = {0};
  timDef.Hours = pTime->hrs24;                          // set hour
  timDef.Minutes = pTime->minutes;                      // set minute
  timDef.Seconds = pTime->seconds;                      // set second.
  HAL_RTC_SetTime(&rtcHandle, &timDef, RTC_FORMAT_BIN); // initilize time
}

/**
 * @brief RTC set date.
 *
 * @param pDate
 */
void rtc_setDate(ClockDate_t *pDate)
{
  RTC_DateTypeDef dateDef = {0};
  dateDef.WeekDay = pDate->dayOfWk;                      // set weekday
  dateDef.Date = pDate->day;                             // set day
  dateDef.Month = pDate->month;                          // set month
  dateDef.Year = pDate->year - 2000;                     // set year
  HAL_RTC_SetDate(&rtcHandle, &dateDef, RTC_FORMAT_BIN); // initilize date
}

/**
 * @brief RTC get time & date.
 *
 * @param pTime
 * @param pDate
 */
void rtc_getTimeDate(ClockTime_t *pTime, ClockDate_t *pDate)
{
  RTC_TimeTypeDef timDef = {0};
  RTC_DateTypeDef dateDef = {0};
  HAL_RTC_GetTime(&rtcHandle, &timDef, RTC_FORMAT_BIN);  // get time from RTC
  HAL_RTC_GetDate(&rtcHandle, &dateDef, RTC_FORMAT_BIN); // get date from RTC

  // Time
  pTime->hrs24 = timDef.Hours;     // get hour
  pTime->minutes = timDef.Minutes; // get minute
  pTime->seconds = timDef.Seconds; // get second

  // Date
  pDate->dayOfWk = dateDef.WeekDay;  // get weekday
  pDate->day = dateDef.Date;         // get day
  pDate->month = dateDef.Month;      // get month
  pDate->year = dateDef.Year + 2000; // get year
}
