/*
 * MenuScreen.h
 *
 *  Created on: 14 Ara 2020
 *      Author: neset
 */

#ifndef TOS_GUI_MENUSCREEN_MENUSCREEN_H_
#define TOS_GUI_MENUSCREEN_MENUSCREEN_H_


	//Include
#include "../../../lvgl/lvgl.h"
#include "stdint.h"
#include "stdbool.h"
#include "main.h"
	//Definations
#define ITEM0 0x00
#define ITEM1 0x01
#define ITEM2 0x02
#define ITEM3 0x03
#define ITEM4 0x04
#define ITEM5 0x05
#define ITEM6 0x06
#define ITEM7 0x07
#define ITEM_MAX ITEM7
#define ITEM_MIN ITEM0
	//Functions
void tos_MenuScreen_Init(bool theme,RTC_HandleTypeDef *hrtc);
void tos_Menu_Controller(void);
bool MenuScreen_TaskControllerGet(void);
void MenuScreen_TaskControllerSet(bool active);
void MenuScreen_SetItem(uint8_t SelectItem);

#endif /* TOS_GUI_MENUSCREEN_MENUSCREEN_H_ */
