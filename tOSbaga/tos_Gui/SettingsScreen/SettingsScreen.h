/*
 * SettingsScreen.h
 *
 *  Created on: 21 Ara 2020
 *      Author: neset
 */

#ifndef TOS_GUI_SETTINGSSCREEN_SETTINGSSCREEN_H_
#define TOS_GUI_SETTINGSSCREEN_SETTINGSSCREEN_H_


//Include
#include "../../../lvgl/lvgl.h"
#include "main.h"
#include "stdint.h"
#include "stdbool.h"
	//Definations


	//Functions
void tos_SettingsScreen_Init(bool theme,RTC_HandleTypeDef *hrtc);
void SettingsScreen_ButtonController(void);
void SettingsScreen_SetDate(uint8_t getYear, uint8_t getMonth, uint8_t getDate);
void SettingsScreen_SetTime(uint8_t getHours, uint8_t getMinutes, uint8_t getSeconds);
void SettingsScreen_SetBluetoothStatu(bool statu);
void SettingsScreen_SetUnitType(bool val);
bool SettingsScreen_isSettingsOpen(void);



#endif /* TOS_GUI_SETTINGSSCREEN_SETTINGSSCREEN_H_ */
