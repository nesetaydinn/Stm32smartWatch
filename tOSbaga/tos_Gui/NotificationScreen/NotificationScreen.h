/*
 * NotificationScreen.h
 *
 *  Created on: 18 Ara 2020
 *      Author: neset
 */

#ifndef TOS_GUI_NOTIFICATIONSCREEN_NOTIFICATIONSCREEN_H_
#define TOS_GUI_NOTIFICATIONSCREEN_NOTIFICATIONSCREEN_H_



//Include
#include "../../../lvgl/lvgl.h"
#include "main.h"
#include "stdint.h"
#include "stdbool.h"
#include "string.h"
	//Definations

typedef struct tos_Position{
	uint16_t x,y;
}tos_Position;

	//Functions
void tos_NotificationScreen_Init(bool theme);
void NotificationScreen_ButtonController(void);
void NotificationScreen_GetNotifications(char *appName,char* appNotification);
void NotificationScreen_TaskControllerSet(bool active);
bool NotificationScreen_TaskControllerGet(void);



#endif /* TOS_GUI_NOTIFICATIONSCREEN_NOTIFICATIONSCREEN_H_ */
