/*
 * rtc.h
 *
 *  Created on: Jan 21, 2023
 *      Author: SquadQuiz
 */

#ifndef INC_RTC_H_
#define INC_RTC_H_

#include "main.h"

//* Import External Variable
extern RTC_HandleTypeDef rtcHandle;
extern const char *daysOfWkString[7];

//* Time unit structure
typedef struct ClockTime_TAG
{
  uint8_t hrs24;
  uint8_t minutes;
  uint8_t seconds;
} ClockTime_t;

//* Date data structure
typedef struct ClockDate_TAG
{
  uint8_t dayOfWk;
  uint8_t day;
  uint8_t month;
  uint16_t year;
} ClockDate_t;

// Alarm Callback function
typedef void (*AlarmEventCallback_t)(void);

/**
 * @brief RTC Configuration.
 *
 */
bool rtc_config(void);

/**
 * @brief RTC set time.
 *
 */
void rtc_setTime(ClockTime_t *pTime);

/**
 * @brief RTC set date.
 *
 * @param pDate
 */
void rtc_setDate(ClockDate_t *pDate);

/**
 * @brief RTC get time & date.
 *
 * @param pTime
 * @param pDate
 */
void rtc_getTimeDate(ClockTime_t *pTime, ClockDate_t *pDate);

/**
 * @brief RTC set alarm.
 * 
 * @param pTime 
 * @param cb 
 */
void rtc_setAlarm(ClockTime_t *pTime, AlarmEventCallback_t cb);

/**
 * @brief RTC get alarm.
 * 
 * @param pTime 
 */
void rtc_getAlarm(ClockTime_t *pTime);

/**
 * @brief RTC stop alarm.
 * 
 * @param pTime 
 */
void rtc_stopAlarm(ClockTime_t *pTime);

/**
 * @brief RTC callback function.
 * 
 */
void rtc_alarm_callback(void);

#endif /* INC_RTC_H_ */
