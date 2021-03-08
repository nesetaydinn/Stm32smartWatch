/*
 * tos_Button_Helper.h
 *
 *  Created on: 8 Ara 2020
 *      Author: neset
 */

#ifndef TOS_HELPER_TOS_BUTTON_HELPER_H_
#define TOS_HELPER_TOS_BUTTON_HELPER_H_

#include "main.h"

/*Buttons connected pull up so when clicked button be logic 0 */
//Right Button Read
#define READ_RIGHT_BTN HAL_GPIO_ReadPin(Right_Btn_GPIO_Port,Right_Btn_Pin)
//Enter Button Read
#define READ_ENTER_BTN HAL_GPIO_ReadPin(Enter_Btn_GPIO_Port,Enter_Btn_Pin)
//Left Button Read
#define READ_LEFT_BTN HAL_GPIO_ReadPin(Left_Btn_GPIO_Port,Left_Btn_Pin)

//Screen Light Control
#define ST7789_Select() HAL_GPIO_WritePin(ST7789_CS_GPIO_Port, ST7789_CS_Pin, GPIO_PIN_RESET)
#define ST7789_UnSelect() HAL_GPIO_WritePin(ST7789_CS_GPIO_Port, ST7789_CS_Pin, GPIO_PIN_SET)

#define BTN_SHORT_PRESS_TIME 5
#define BTN_LONG_PRESS_TIME 550
#define BTN_ULTRA_LONG_PRESS_TIME 1200

uint8_t tos_RightButton_Listenner_For_MenuControl(void);
uint8_t tos_LeftButton_Listenner_For_MenuControl(void);
uint8_t tos_EnterButton_Listenner_For_MenuControl(void);
void tos_ButtonCounterIncrease(void);

#endif /* TOS_HELPER_TOS_BUTTON_HELPER_H_ */
