/*
 * SleepModeScreen.h
 *
 *  Created on: 11 Ara 2020
 *      Author: neset
 */

#ifndef TOS_GUI_SLEEPMODESCREEN_SLEEPMODESCREEN_H_
#define TOS_GUI_SLEEPMODESCREEN_SLEEPMODESCREEN_H_


	//Include
#include "../../../lvgl/lvgl.h"
#include "stdint.h"
#include "stdbool.h"
	//Definations


	//Functions
void tos_SleepModeScreen_Init(void);
void SMS_Updater(void);

void SleepModeScreen_SetTime(uint8_t getHours, uint8_t getMinutes, uint8_t getSeconds);
void SleepModeScreen_SetDate(uint8_t getYear, uint8_t getMonth, uint8_t getDate, char* getWeekDay);
void SleepModeScreen_SetBatteryVal(char* getBatteryVal, lv_color_t getBatteryColor);
void SleepModeScreen_SetBluetoothStatusVal(bool getBluetoothStatus, lv_color_t getBluetoothColor);
void SleepModeScreen_TaskControllerSet(bool active);


#endif /* TOS_GUI_SLEEPMODESCREEN_SLEEPMODESCREEN_H_ */
