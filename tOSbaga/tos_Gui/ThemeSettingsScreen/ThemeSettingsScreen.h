/*
 * ThemeSettingsScreen.h
 *
 *  Created on: Mar 8, 2021
 *      Author: neset
 */

#ifndef TOS_GUI_THEMESETTINGSSCREEN_THEMESETTINGSSCREEN_H_
#define TOS_GUI_THEMESETTINGSSCREEN_THEMESETTINGSSCREEN_H_


//Include
#include "../../../lvgl/lvgl.h"
#include "main.h"
#include "stdint.h"
#include "stdbool.h"
	//Definations


	//Functions
void tos_ThemeSettingsScreen_Init(bool theme);
void ThemeSettingsScreen_ButtonController(void);
void ThemeSettingsScreen_SetTheme(bool theme);
bool ThemeSettingsScreen_GetTheme(void);
void ThemeSettingsScreen_SetClockType(uint8_t theme);
uint8_t ThemeSettingsScreen_GetClockType(void);
bool ThemeSettingsScreen_isSettingsOpen(void);


#endif /* TOS_GUI_THEMESETTINGSSCREEN_THEMESETTINGSSCREEN_H_ */
