/*
 * tos_Button_Helper.c
 *
 *  Created on: 8 Ara 2020
 *      Author: neset
 */

#include "tos_Button_Helper.h"

uint8_t tos_EnterButton_LongPress_Listenner(void) {

	static uint8_t buttonCounter=0,result;

	if (!READ_ENTER_BTN) {
		while (!READ_ENTER_BTN) {
			if (buttonCounter >=300) {
				result=2;
				buttonCounter=0;
				return result;
			}
			else if(buttonCounter >=2)result=1;
		}
	} buttonCounter=0;
	return result;
}
uint8_t tos_RightButton_Listenner_For_MenuControl(void) {
	uint8_t result=0, counter=0;
	if (!READ_RIGHT_BTN) {
		while (!READ_RIGHT_BTN) {
			if (counter >=50) {
				result=2;
				return result;
			}
			else if(counter >=20)result=1;
			counter++;
		}
	}
	return result;
}
uint8_t tos_LeftButton_Listenner_For_MenuControl(void) {
	uint8_t result=0, counter=0;
	if (!READ_LEFT_BTN) {
		while (!READ_LEFT_BTN) {
			if (counter >=50) {
				result=2;
				return result;
			}
			else if(counter >=20)result=1;
			counter++;
		}
	}
	return result;
}
uint8_t tos_EnterButton_Listenner_For_MenuControl(void) {
	uint8_t result=0, counter=0;
	if (!READ_ENTER_BTN) {
		while (!READ_ENTER_BTN) {
			if (counter >=50) {
				result=2;
				return result;
			}
			else if(counter >=20)result=1;
			counter++;
		}
	}
	return result;
}
