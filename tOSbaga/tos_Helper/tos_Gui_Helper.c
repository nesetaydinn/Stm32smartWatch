/*
 * tos_Gui_Helper.c
 *
 *  Created on: 8 Ara 2020
 *      Author: neset
 */

#include "../tOSbaga.h"
#include "../../lvgl/lvgl.h"

RTC_HandleTypeDef *ScreenRtc;
uint8_t screenType,screenTheme;
uint16_t screenCounter;
bool GuiHelperOpen;
bool screenStatu;
bool isScreenCounterEnable;
static bool isWorkingSystem=false;
static uint16_t sleepCounter;
uint8_t currentScreen;
void tos_Gui_Init(void);



void tos_Screen_Init(void){
	ST7789_UnSelect();
	isScreenCounterEnable=true;
	screenStatu=true;
	GuiHelperOpen=true;
	screenType=1;
	screenTheme=0;
	currentScreen=1;
	screenCounter=0;
	tos_StartScreen_Init();
	HAL_TIM_Base_Start_IT(&TOS_GUI_TIMER);
	isWorkingSystem=true;


}
void tos_firstScreen_Update(void){
	if(isScreenCounterEnable){
		screenCounter++;
		if(screenCounter>=5000){
			tos_Gui_Init();
		}
	}

}

void tos_Gui_Init(void){
	screenCounter=0;
	currentScreen=0;
	isScreenCounterEnable=false;
	lv_obj_clean(lv_scr_act());
	tos_Screen_Chooser(currentScreen);
}


void tos_ScreenController(void){
	 tos_Menu_Controller();
	if(screenCounter==0 && GuiHelperOpen){

		if(1==tos_EnterButton_Listenner_For_MenuControl()){ sleepCounter=0;
			if(!screenStatu){screenStatu=true;	ST7789_UnSelect(); return;}
			else if(1==currentScreen){currentScreen=0; tos_Screen_Chooser(currentScreen);	return;}
		}
		else if(2==tos_EnterButton_Listenner_For_MenuControl()){
				//screenStatu=false; currentScreen=1;tos_Screen_Chooser(currentScreen); return;
		}
		if(1==tos_LeftButton_Listenner_For_MenuControl()){ sleepCounter=0;
			MenuScreen_SetItem(5); currentScreen=2; tos_Screen_Chooser(currentScreen);
			GuiHelperOpen=false; 	return;
			}
		if(1==tos_RightButton_Listenner_For_MenuControl()){ sleepCounter=0;
			MenuScreen_SetItem(0); currentScreen=2; tos_Screen_Chooser(currentScreen);
			GuiHelperOpen=false; 	return;
		}


	}

}
/*This function using for set new screen*/
void tos_Screen_Chooser(uint8_t currentScreen){
	SleepModeScreen_TaskControllerSet(false);
	MainScreen_TaskControllerSet(false);
	MenuScreen_TaskControllerSet(false);
	lv_obj_clean(lv_scr_act());
	switch(currentScreen){
	case TOS_SCREEN_MAIN_:
		HAL_TIM_Base_Start_IT(&TOS_SCREENUPDATE_TIMER);
		MainScreen_TaskControllerSet(true);
		tos_MainScreen_Init(1,1);break;
	case TOS_SCREEN_SLEEPMODE_:
		SleepModeScreen_TaskControllerSet(true);
		tos_SleepModeScreen_Init();break;
	case TOS_SCREEN_MENU:
		HAL_TIM_Base_Stop_IT(&TOS_SCREENUPDATE_TIMER);
		MenuScreen_TaskControllerSet(true);
		tos_MenuScreen_Init(true,ScreenRtc);
		break;
	default: return;
	}
}
void tos_Screen_Variables_Getter(uint8_t Screen){
	  tos_BluetoothReceiverAndTransmitter(ScreenRtc);
	  tos_BluetoothGetStatusVAl(tos_BluetoothGetEnableVal(),Screen);
	  tos_RTC_GetTime(ScreenRtc,Screen);
	  tos_getBatteryVAl(50,Screen);

}
void tos_Get_Rtc(RTC_HandleTypeDef *hrtc){
	ScreenRtc=hrtc;
}
uint8_t tos_Get_Current_Screen(void){
	return currentScreen;
}
void tos_Set_Current_Screen(void){
	currentScreen=0; tos_Screen_Chooser(currentScreen);
	GuiHelperOpen=true;
}
void tos_SleepScreen_Counter(void){
	sleepCounter++;
	if(sleepCounter>=450){
		if(1==currentScreen) { screenStatu=false; ST7789_Select(); }
		currentScreen=1; tos_Screen_Chooser(currentScreen);
		sleepCounter=0;
	}
}
void tos_Gui_ShutdownController(void){
	if(isWorkingSystem){
		isWorkingSystem=false;
		tos_StartScreen_Init();
		lv_obj_clean(lv_scr_act());
		SleepModeScreen_TaskControllerSet(false);
		MainScreen_TaskControllerSet(false);
		MenuScreen_TaskControllerSet(false);
		HAL_TIM_Base_Stop_IT(&TOS_SCREENUPDATE_TIMER);
		ST7789_Select();
	}else {
		isWorkingSystem=true;
		tos_Screen_Init();
	}

}

