/*
 * tos_StepsAndKcals_Helper.h
 *
 *  Created on: Jan 29, 2021
 *      Author: neset
 */

#ifndef TOS_HELPER_TOS_STEPSANDKCALS_HELPER_H_
#define TOS_HELPER_TOS_STEPSANDKCALS_HELPER_H_

#include "../../mpu6050/defines.h"
#include "../../mpu6050/tm_stm32_mpu6050.h"
#include "main.h"
#include "math.h"

#define TESTBLT_PORT huart6
extern UART_HandleTypeDef TESTBLT_PORT;

void tos_StepsAndKcalsInit(void);
void tos_StepsAndKcalsRead(void);
void tos_StepsAndKcalsCalcSteps(void);

#endif /* TOS_HELPER_TOS_STEPSANDKCALS_HELPER_H_ */
