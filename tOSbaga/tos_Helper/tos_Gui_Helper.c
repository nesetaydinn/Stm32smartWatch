/*
 * tos_Gui_Helper.c
 *
 *  Created on: 8 Ara 2020
 *      Author: neset
 */

#include "../tOSbaga.h"
#include "../../lvgl/lvgl.h"
#include "../../MPU6050/NA_MPU6050.h"

#include "FreeRTOS.h"
#include "semphr.h"

RTC_HandleTypeDef *ScreenRtc;
uint8_t screenType;
bool screenTheme;
uint16_t screenCounter;
bool GuiHelperOpen;
bool screenStatu;
bool isScreenCounterEnable;
static bool isWorkingSystem=false;
static uint16_t sleepCounter;
uint8_t currentScreen,TGEnterBtnListenner,TGRightBtnListenner,TGLeftBtnListenner;

bool isOpenSleepScreen;
extern task2Mutex;

void tos_Gui_Init(void);
void tos_Screen_Create(void);



void tos_Screen_Init(void){
	TGEnterBtnListenner=0,TGRightBtnListenner=0,TGLeftBtnListenner=0;

}
void tos_Screen_Create(void){
	isScreenCounterEnable=true;
	screenStatu=true;
	GuiHelperOpen=true;
	screenType=ThemeSettingsScreen_GetClockType();
	screenTheme=ThemeSettingsScreen_GetTheme();
	currentScreen=255;
	screenCounter=0;
	isWorkingSystem=true;
	ST7789_UnSelect();
	tos_StartScreen_Init();

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
	if(3==TGEnterBtnListenner){
		tos_Gui_ShutdownController();
	}
	tos_Menu_Controller();
	if(screenCounter==0 && GuiHelperOpen){
		if(2==TGEnterBtnListenner){
				if(screenStatu){screenStatu=false; currentScreen=1;tos_Screen_Chooser(currentScreen); return;}
		}
		else if(1==TGEnterBtnListenner){ sleepCounter=0;
			if(!screenStatu){screenStatu=true;	ST7789_UnSelect(); return;}
			else if(1==currentScreen){currentScreen=0; tos_Screen_Chooser(currentScreen);	return;}
		}

		if(1==TGLeftBtnListenner){ sleepCounter=0;
			MenuScreen_SetItem(7); currentScreen=2; tos_Screen_Chooser(currentScreen);
			GuiHelperOpen=false; 	return;
			}
		if(1==TGRightBtnListenner){ sleepCounter=0;
			MenuScreen_SetItem(0); currentScreen=2; tos_Screen_Chooser(currentScreen);
			GuiHelperOpen=false; 	return;
		}


		if(isOpenSleepScreen && screenStatu ){isOpenSleepScreen=false; sleepCounter=0; currentScreen=TOS_SCREEN_SLEEPMODE_;  tos_Screen_Chooser(currentScreen);
		vTaskDelay(5);}
		else if(isOpenSleepScreen && !screenStatu){isOpenSleepScreen=false; sleepCounter=0; ST7789_Select();}
	}
	TGEnterBtnListenner=tos_EnterButton_Listenner_For_MenuControl();
	TGRightBtnListenner=tos_RightButton_Listenner_For_MenuControl();
	TGLeftBtnListenner=tos_LeftButton_Listenner_For_MenuControl();
}

MPUScaledData_Def getgyroScale;
float gyroYnow,gyroYbef,gyroYtotal;
void tos_Read_Gyro(void){
	if(isWorkingSystem && TOS_SCREEN_SLEEPMODE_==currentScreen){
	uint32_t t1,t2,dt;
	t1=HAL_GetTick();
	MPU6050_Read_ScaledGyro_Val();
	getgyroScale=MPU6050_getGyroScaleVals();
	gyroYnow=getgyroScale.y;
	gyroYtotal=gyroYnow-gyroYbef;
	if(gyroYtotal>90.0f){ST7789_UnSelect(); screenStatu=true;}
	if(gyroYtotal<-90.0f){ST7789_Select(); screenStatu=false;}
	gyroYbef=gyroYnow;
	t2=HAL_GetTick();
	dt=t2-t1;
	if(dt<400)vTaskDelay(400-dt);
	}
}

/*This function using for set new screen*/
void tos_Screen_Chooser(uint8_t currentScreen){

	xSemaphoreTake(task2Mutex,portMAX_DELAY);
	SleepModeScreen_TaskControllerSet(false);
	MainScreen_TaskControllerSet(false);
	MenuScreen_TaskControllerSet(false);
	lv_obj_clean(lv_scr_act());
	switch(currentScreen){
	case TOS_SCREEN_MAIN_:
		tos_MainScreen_Init(screenType,screenTheme);
		break;
	case TOS_SCREEN_SLEEPMODE_:
		tos_SleepModeScreen_Init();
		break;
	case TOS_SCREEN_MENU:
		tos_MenuScreen_Init(screenTheme,ScreenRtc);
		break;
	default: return;
	}

	xSemaphoreGive(task2Mutex);
}
void tos_Screen_Variables_Getter(uint8_t Screen){
	uint8_t battVal=tos_getRealbatValue();
	  tos_RTC_GetTime(ScreenRtc,Screen);
	  tos_getBatteryVAl(battVal,Screen);
	  tos_StepsAndKcalsSetVal(Screen);

}
void tos_Get_Rtc(RTC_HandleTypeDef *hrtc){
	ScreenRtc=hrtc;
}
uint8_t tos_Get_Current_Screen(void){
	return currentScreen;
}
void tos_Set_Current_Screen(void){
	currentScreen=0;
	GuiHelperOpen=true;
	tos_Screen_Chooser(currentScreen);
}

void tos_SleepScreen_Counter(void){
	if(isWorkingSystem){
if(TOS_SCREEN_MAIN_==currentScreen){
	sleepCounter++;
	isOpenSleepScreen=false;
	if(sleepCounter>100) isOpenSleepScreen=true;

}
else if(TOS_SCREEN_SLEEPMODE_==currentScreen && screenStatu){
	sleepCounter++;
	if(sleepCounter>200){screenStatu=false; isOpenSleepScreen=true;}

}
}

}
void tos_Gui_ShutdownController(void){
	if(isWorkingSystem){
		SleepModeScreen_TaskControllerSet(false);
		MainScreen_TaskControllerSet(false);
		MenuScreen_TaskControllerSet(false);
		GuiHelperOpen=false;
		isWorkingSystem=false;
		lv_obj_clean(lv_scr_act());
		ST7789_Select();
	}else {
		isWorkingSystem=true;
		tos_Screen_Create();
	}

}
void tos_Gui_SetScreenType(uint8_t type){screenType=type;}
void tos_Gui_SetTheme(bool theme){screenTheme=theme;}

bool tos_Gui_GetWorkingSystemVal(void){
	return isWorkingSystem;
}

