/*
 * tos_Battery_Helper.c
 *
 *  Created on: 7 Ara 2020
 *      Author: neset
 */

#include "../tOSbaga.h"
#include "../../lvgl/lvgl.h"

char * tos_BatteryVal_Sym_Helper(uint8_t batteryVal,uint8_t batteryValueTemp);
lv_color_t tos_BatteryVal_SymColor_Helper(uint8_t batteryVal);

void tos_getBatteryVAl(uint8_t batteryVal,uint8_t Screen){
	static uint8_t batteryValueTemp = 255;
	if (batteryVal != batteryValueTemp){
	char * batterySym= tos_BatteryVal_Sym_Helper(batteryVal,batteryValueTemp);
	lv_color_t batteryClr = tos_BatteryVal_SymColor_Helper(batteryVal);
	switch(Screen){
	case TOS_SCREEN_MAIN_:  	MainScreen_SetBatteryVal(batterySym, batteryClr); break;
	case TOS_SCREEN_SLEEPMODE_:  SleepModeScreen_SetBatteryVal(batterySym, batteryClr); break;
	/*case TOS_SCREEN_STOPWATCH_: tos_MainScreen_Init(1,1);break;
	case TOS_SCREEN_NOTIFICATIONS_: break;*/
	default: return;
	}

	}
}

char * tos_BatteryVal_Sym_Helper(uint8_t batteryVal,uint8_t batteryValueTemp){
		if(batteryVal <= batteryValueTemp){
			if (batteryVal < 10 && batteryVal >= 0) return LV_SYMBOL_BATTERY_EMPTY;
			else if (batteryVal >= 10 && batteryVal < 25) return LV_SYMBOL_BATTERY_1;
			else if (batteryVal >= 25 && batteryVal < 50) return LV_SYMBOL_BATTERY_2;
			else if (batteryVal >= 50 && batteryVal < 80) return LV_SYMBOL_BATTERY_3;
			else if (batteryVal >= 80 && batteryVal <= 100) return LV_SYMBOL_BATTERY_FULL;
	}else{
			if (batteryVal < 10 && batteryVal >= 0) return LV_SYMBOL_BATTERY_EMPTY;
			else if (batteryVal >= 10 && batteryVal < 25) return LV_SYMBOL_CHARGE LV_SYMBOL_BATTERY_1;
			else if (batteryVal >= 25 && batteryVal < 50) return LV_SYMBOL_CHARGE LV_SYMBOL_BATTERY_2;
			else if (batteryVal >= 50 && batteryVal < 80) return LV_SYMBOL_CHARGE LV_SYMBOL_BATTERY_3;
			else if (batteryVal >= 80 && batteryVal <= 100) return LV_SYMBOL_CHARGE LV_SYMBOL_BATTERY_FULL;
			}
		return "err";
}
lv_color_t tos_BatteryVal_SymColor_Helper(uint8_t batteryVal){
			if (batteryVal < 10 && batteryVal >= 0) return LV_COLOR_RED;
			else if (batteryVal >= 10 && batteryVal < 25) return LV_COLOR_RED;
			else if (batteryVal >= 25 && batteryVal < 50) return LV_COLOR_ORANGE;
			else if (batteryVal >= 50 && batteryVal < 80) return LV_COLOR_ORANGE;
			else if (batteryVal >= 80 && batteryVal <= 100) return LV_COLOR_GREEN;

			return LV_COLOR_BLUE;
}
