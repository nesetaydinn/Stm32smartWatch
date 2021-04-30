/*
 * tos_Battery_Helper.h
 *
 *  Created on: 7 Ara 2020
 *      Author: neset
 */

#ifndef TOS_HELPER_TOS_BATTERY_HELPER_H_
#define TOS_HELPER_TOS_BATTERY_HELPER_H_

#include "main.h"

#define BATTERY_READ_TIMEOUT 150

#define BATTERY_CHARGED HAL_GPIO_ReadPin(BatteryCharged_GPIO_Port,BatteryCharged_Pin)

#define BATTERY_IS_CHARGING HAL_GPIO_ReadPin(BatteryIsCharging_GPIO_Port,BatteryIsCharging_Pin)

void tos_BatteryRead(ADC_HandleTypeDef *battery);
void tos_getBatteryVAl(uint8_t batteryVal,uint8_t Screen);
uint8_t tos_getRealbatValue(void);



#endif /* TOS_HELPER_TOS_BATTERY_HELPER_H_ */
