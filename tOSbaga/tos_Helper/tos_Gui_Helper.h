/*
 * tos_Gui_Helper.h
 *
 *  Created on: 8 Ara 2020
 *      Author: neset
 */

#ifndef TOS_HELPER_TOS_GUI_HELPER_H_
#define TOS_HELPER_TOS_GUI_HELPER_H_

#include "main.h"

#define TOS_SLEEP_TIMER htim2
extern TIM_HandleTypeDef TOS_SLEEP_TIMER;

#define TOS_SCREENUPDATE_TIMER htim3
extern TIM_HandleTypeDef TOS_SCREENUPDATE_TIMER;

#define TOS_GUI_TIMER htim4
extern TIM_HandleTypeDef TOS_GUI_TIMER;

void tos_Screen_Init(void);
void tos_Get_Rtc(RTC_HandleTypeDef *hrtc);
void tos_Screen_Chooser(uint8_t currentScreen);
void tos_SleepScreen_Counter(void);
void tos_Set_Current_Screen(void);
void tos_Gui_ShutdownController(void);
void tos_ScreenController(void);
void tos_firstScreen_Update(void);
void tos_Screen_Variables_Getter(uint8_t Screen);
uint8_t tos_Get_Current_Screen(void);

#define TOS_SCREEN_MAIN_ 0X00
#define TOS_SCREEN_SLEEPMODE_ 0X01
#define TOS_SCREEN_MENU 0X02



#endif /* TOS_HELPER_TOS_GUI_HELPER_H_ */
