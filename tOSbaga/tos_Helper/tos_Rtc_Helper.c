/*
 * tos_Rtc_Helper.c
 *
 *  Created on: Dec 5, 2020
 *      Author: neset
 */
#include "../tOSbaga.h"

RTC_TimeTypeDef myTime = {0};
RTC_DateTypeDef myDate = {0};

char * weekDayFinder(uint8_t getDay,uint8_t getMonth,uint16_t getYear);

void tos_RTC_init(RTC_HandleTypeDef *hrtc){
	tos_RTC_SetDate(hrtc,tos_Flash_GetYear(),tos_Flash_GetMonth(),tos_Flash_GetDate());
	tos_RTC_SetTime(hrtc,tos_Flash_GetHours(),tos_Flash_GetMinutes(),tos_Flash_GetSeconds());

}

  void tos_RTC_GetTime(RTC_HandleTypeDef *hrtc, uint8_t Screen){
	  	  	  static uint8_t befDate;
			  HAL_RTC_GetTime(hrtc,&myTime,RTC_FORMAT_BIN);
			  HAL_RTC_GetDate(hrtc,&myDate,RTC_FORMAT_BIN);
			  if(befDate!=myDate.Date)tos_StepsAndKcalsSetSteps(0);
			  switch(Screen){
				befDate=myDate.Date;
				case TOS_SCREEN_MAIN_: MainScreen_SetTime(myTime.Hours,myTime.Minutes,myTime.Seconds);
				  MainScreen_SetDate(myDate.Year,myDate.Month,myDate.Date,
									  weekDayFinder(myDate.Year,myDate.Month,myDate.Date));
				  break;
				case TOS_SCREEN_SLEEPMODE_: SleepModeScreen_SetTime(myTime.Hours,myTime.Minutes,myTime.Seconds);
				SleepModeScreen_SetDate(myDate.Year,myDate.Month,myDate.Date,
									  weekDayFinder(myDate.Year,myDate.Month,myDate.Date)); break;
				default:
					  SettingsScreen_SetTime(myTime.Hours,myTime.Minutes,myTime.Seconds);
					  SettingsScreen_SetDate(myDate.Year,myDate.Month,myDate.Date);
					  return;
				}

			/*  MainScreen_SetDate(myDate.Year,myDate.Month,myDate.Date,
					  weekDayFinder(myDate.Year,myDate.Month,myDate.Date));*/
  }

  void tos_RTC_SetTime(RTC_HandleTypeDef *hrtc,uint8_t setHours,uint8_t setMins,uint8_t setSecs){
	  if(setSecs>60 || setMins>60 || setHours>24) return;
	  RTC_TimeTypeDef tmp = {0};
	  tmp.Hours = setHours;
	  tmp.Minutes = setMins;
	  tmp.Seconds = setSecs;
	  HAL_RTC_SetTime(hrtc,&tmp,RTC_FORMAT_BIN);
  }

  void tos_RTC_SetDate(RTC_HandleTypeDef *hrtc,uint8_t setYear,uint8_t setMonth,uint8_t setDate){
	  if(setDate>31 || setMonth>12) return;
	  RTC_DateTypeDef tmp = {0};
	  tmp.Year = setYear;
	  tmp.Month = setMonth;
	  tmp.Date = setDate;
	  HAL_RTC_SetDate(hrtc,&tmp,RTC_FORMAT_BIN);
  }



char * weekDayFinder(uint8_t getYear,uint8_t getMonth,uint16_t getDate){
	getYear=getYear+2000;
	static uint8_t t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
	getYear-= getMonth < 3;
	double weekDayTmp =(double)((getYear + (getYear/4) - (getYear/100) + (getYear/400) + t[getMonth-1] + getDate) % 7);
	uint8_t weekDay =tos_Rounding(weekDayTmp);


	switch(weekDay){
	case 0: return "Pazartesi"; break;
	case 1: return "Sali"; break;
	case 2: return "Carsamba"; break;
	case 3: return "Persembe"; break;
	case 4: return "Cuma"; break;
	case 5: return "Cumartesi"; break;
	case 6: return "Pazar"; break;
	default: return " ";
	}

}
