/*
 * tos_Rtc_Helper.h
 *
 *  Created on: Dec 5, 2020
 *      Author: neset
 */
#include "main.h"

#ifndef TOS_HELPER_TOS_RTC_HELPER_H_
#define TOS_HELPER_TOS_RTC_HELPER_H_

  void tos_RTC_init(RTC_HandleTypeDef *hrtc);
  void tos_RTC_GetTime(RTC_HandleTypeDef *hrtc, uint8_t Screen);
  void tos_RTC_SetTime(RTC_HandleTypeDef *hrtc,uint8_t setHours,uint8_t setMins,uint8_t setSecs);
  void tos_RTC_SetDate(RTC_HandleTypeDef *hrtc,uint8_t setYear,uint8_t setMonth,uint8_t setDate);

#endif /* TOS_HELPER_TOS_RTC_HELPER_H_ */
