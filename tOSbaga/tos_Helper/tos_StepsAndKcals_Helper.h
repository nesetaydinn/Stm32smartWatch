/*
 * tos_StepsAndKcals_Helper.h
 *
 *  Created on: Jan 29, 2021
 *      Author: neset
 */

#ifndef TOS_HELPER_TOS_STEPSANDKCALS_HELPER_H_
#define TOS_HELPER_TOS_STEPSANDKCALS_HELPER_H_

#include "../../MPU6050/NA_MPU6050.h"
#include "main.h"
#include "math.h"

#define KMTOMILE 0.621371192



void tos_StepsAndKcalsInit(void);
void tos_StepsAndKcalsRead(void);
void tos_StepsAndKcalsCalcSteps(void);
void tos_StepsAndKcalsSetVal(void);
uint16_t tos_StepsAndKcalsGetSteps(void);
float tos_StepsAndKcalsGetDistance_KiloMeter(void);
float tos_StepsAndKcalsGetDistance_Mile(void);
uint16_t tos_StepsAndKcalsGetDistance_KiloCal(void);
uint16_t tos_StepsAndKcalsGetDistance_Cal(void);
void tos_StepsAndKcalsSetSteps(uint16_t step);

void tos_StepsAndKcalsSetUnitType(bool u);
bool tos_StepsAndKcalsGetUnitType(void);

#endif /* TOS_HELPER_TOS_STEPSANDKCALS_HELPER_H_ */
