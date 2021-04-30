/*
 * StepAndKcal.h
 *
 *  Created on: 14 Ara 2020
 *      Author: neset
 */

#ifndef TOS_GUI_STEPANDKCALSCREEN_STEPANDKCALSCREEN_H_
#define TOS_GUI_STEPANDKCALSCREEN_STEPANDKCALSCREEN_H_


	//Include
#include "../../../lvgl/lvgl.h"
#include "stdint.h"
#include "stdbool.h"
	//Definations


	//Functions
void tos_StepAndKcalScreen_Init(bool unitType,bool theme);
void SAK_Updater(void);
void StepAndKcal_SetStepsAndKcals(uint16_t getSteps, uint16_t getKcals);

void StepAndKcal_TaskControllerSet(bool active);



#endif /* TOS_GUI_STEPANDKCALSCREEN_STEPANDKCALSCREEN_H_ */
