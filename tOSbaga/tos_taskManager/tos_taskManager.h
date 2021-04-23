/*
 * tos_taskManager.h
 *
 *  Created on: Mar 3, 2021
 *      Author: neset
 */

#ifndef TOS_TASKMANAGER_TOS_TASKMANAGER_H_
#define TOS_TASKMANAGER_TOS_TASKMANAGER_H_


#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "main.h"



void tos_tasks_init(void);

void tos_BtnAndFSUpdate_TaskResume(void);
void tos_tftTickUpdaterTaskResume(void);
void tos_controllerTaskResume(void);
void tos_mpu6050readTaskResume(void);
void tos_stepAndkCalsCalcTaskResume(void);
void tos_Bluetooth_TaskResume(void);
void tos_ScreenUpdate_TaskResume(void);
void tos_SleepScreenUpdate_TaskResume(void);

void tos_BtnAndFSUpdate_TaskPause(void);
void tos_tftTickUpdaterTaskPause(void);
void tos_controllerTaskPause(void);
void tos_mpu6050readTaskPause(void);
void tos_stepAndkCalsCalcTaskPause(void);
void tos_Bluetooth_TaskPause(void);
void tos_ScreenUpdate_TaskPause(void);
void tos_SleepScreenUpdate_TaskPause(void);


#endif /* TOS_TASKMANAGER_TOS_TASKMANAGER_H_ */
