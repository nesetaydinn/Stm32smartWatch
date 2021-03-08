#ifndef TOS_MAIN_SCREEN
#define TOS_MAIN_SCREEN

#ifdef __cplusplus
extern "C" {
#endif

	//Include
#include "../../../lvgl/lvgl.h"
#include "stdint.h" 
#include "stdbool.h" 
#include "math.h"
#include "main.h"

	//Definations
#define tos_mainScreen_Type1 0x00 //Analogue and digital type
#define tos_mainScreen_Type2 0x01 //only digital type
#define tos_mainScreen_Type3 0x02 //only analogue type

	//Functions
	void tos_MainScreen_Init(uint8_t screenType,bool theme);
	void MainScreen_Updater(void);
	void MainScreen_SetTime(uint8_t getHours, uint8_t getMinutes, uint8_t getSeconds);
	void MainScreen_SetDate(uint8_t getYear, uint8_t getMonth, uint8_t getDate, char* getWeekDay);
	void MainScreen_SetStepsAndKcals(uint16_t getSteps, uint16_t getKcals);
	void MainScreen_SetBatteryVal(char* getBatteryVal, lv_color_t getBatteryColor);
	void MainScreen_SetBluetoothStatusVal(bool getBluetoothStatus, lv_color_t getBluetoothColor);
	void MainScreen_TaskControllerSet(bool active);
#ifdef __cplusplus
}
#endif


#endif
