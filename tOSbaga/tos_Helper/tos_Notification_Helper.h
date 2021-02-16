#include <stdio.h>
#include <stdlib.h>
#include "stdint.h"


typedef struct tos_Notification{
	char appName[20];
	char appNot[200];
	uint16_t index;
	struct tos_Notification * next;
}tos_Notification;


tos_Notification *  tos_Notification_SetFirstNode(tos_Notification * root,tos_Notification * node);
tos_Notification * tos_Notification_CreateRoot(tos_Notification * root);
tos_Notification * tos_Notification_CreateNode(uint16_t index);
tos_Notification * tos_NotificationPushItem(tos_Notification * node,char *appName,char *notification);
tos_Notification *tos_NotificationGetItem(tos_Notification * root,uint16_t itemIndex);
void PrintList(tos_Notification * root);
void tos_NotificationDelItem(tos_Notification *root,tos_Notification *node,uint16_t index);
uint8_t tos_NotificationGetSize(tos_Notification * root);


