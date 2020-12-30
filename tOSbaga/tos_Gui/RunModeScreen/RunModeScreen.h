/*
 * RunModeScreen.h
 *
 *  Created on: Dec 15, 2020
 *      Author: neset
 */

#ifndef TOS_GUI_RUNMODESCREEN_RUNMODESCREEN_H_
#define TOS_GUI_RUNMODESCREEN_RUNMODESCREEN_H_

//Include
#include "../../../lvgl/lvgl.h"
#include "main.h"
#include "stdint.h"
#include "stdbool.h"
	//Definations

#define TOS_RUNMODE_TIMER htim2
extern TIM_HandleTypeDef TOS_RUNMODE_TIMER;

	//Functions
void tos_RunModeScreen_Init(bool unitType,bool theme);
void RunModeScreen_Updater(lv_task_t *t);
void RunMode_ButtonController(void);
void RunMode_Update_Time(void);
void RunMode_TaskControllerSet(bool active);
void RunMode_SetStepsAndKcals(uint16_t getSteps, uint16_t getKcals);
bool RunMode_TaskControllerGet(void);



#endif /* TOS_GUI_RUNMODESCREEN_RUNMODESCREEN_H_ */
