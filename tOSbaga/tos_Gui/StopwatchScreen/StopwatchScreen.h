/*
 * StopwatchScreen.h
 *
 *  Created on: 15 Ara 2020
 *      Author: neset
 */

#ifndef TOS_GUI_STOPWATCHSCREEN_STOPWATCHSCREEN_H_
#define TOS_GUI_STOPWATCHSCREEN_STOPWATCHSCREEN_H_

	//Include
#include "../../../lvgl/lvgl.h"
#include "main.h"
#include "stdint.h"
#include "stdbool.h"
	//Definations

#define TOS_STOPWATCH_TIMER htim4
extern TIM_HandleTypeDef TOS_STOPWATCH_TIMER;

	//Functions
void tos_StopWatchScreen_Init(bool theme);
void StopWatch_Stopwatch_Updater(lv_task_t *t);

void StopWatch_ButtonController(void);
void StopWatch_Update_Time(void);
void StopWatch_TaskControllerSet(bool active);
bool StopWatch_TaskControllerGet(void);




#endif /* TOS_GUI_STOPWATCHSCREEN_STOPWATCHSCREEN_H_ */
