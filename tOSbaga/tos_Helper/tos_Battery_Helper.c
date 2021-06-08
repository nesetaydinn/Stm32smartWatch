/*
 * tos_Battery_Helper.c
 *
 *  Created on: 7 Ara 2020
 *      Author: neset
 */

#include "../tOSbaga.h"
#include "../../lvgl/lvgl.h"


uint8_t realbatValue;
bool isCharging;

char * tos_BatteryVal_Sym_Helper(uint8_t batteryVal);
lv_color_t tos_BatteryVal_SymColor_Helper(uint8_t batteryVal);

void tos_getBatteryVAl(uint8_t batteryVal,uint8_t Screen){
	static uint8_t batteryValueTemp = 255;
	if (batteryVal != batteryValueTemp){
	char * batterySym= tos_BatteryVal_Sym_Helper(batteryVal);
	lv_color_t batteryClr = tos_BatteryVal_SymColor_Helper(batteryVal);
	switch(Screen){
	case TOS_SCREEN_MAIN_:  	MainScreen_SetBatteryVal(batterySym, batteryClr); break;
	case TOS_SCREEN_SLEEPMODE_:  SleepModeScreen_SetBatteryVal(batterySym, batteryClr); break;
	default: return;
	}

	}
}
void tos_BatteryRead(ADC_HandleTypeDef *battery){
	uint16_t tmpbatValue;
	static uint32_t filter=0;
	HAL_ADC_PollForConversion(battery, BATTERY_READ_TIMEOUT);
	  HAL_ADC_Start(battery);
	  for(int c=0;c<256;c++){
		  filter+=HAL_ADC_GetValue(battery);
	  }
	  tmpbatValue=(uint16_t)(filter>>8);
	  realbatValue=(uint8_t) tos_Ratio(tmpbatValue,0,4095,0,100);
	  filter=0;
	  HAL_ADC_Stop(battery);

	  BATTERY_CHARGED;
	  isCharging=BATTERY_IS_CHARGING;
}

char * tos_BatteryVal_Sym_Helper(uint8_t batteryVal){
		if(!isCharging){
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
uint8_t tos_getRealbatValue(void){return realbatValue;}
