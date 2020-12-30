/*
 * tos_Button_Helper.c
 *
 *  Created on: 8 Ara 2020
 *      Author: neset
 */

#include "tos_Button_Helper.h"
static uint16_t enterbtncounter=0,rightbtncounter=0,leftbtncounter=0;
uint8_t tos_RightButton_Listenner_For_MenuControl(void) {
	if(READ_RIGHT_BTN){
		if(rightbtncounter>=BTN_LONG_PRESS_TIME){ rightbtncounter=0;return 2;}
		if(rightbtncounter>=BTN_SHORT_PRESS_TIME){ rightbtncounter=0;return 1;}
		 rightbtncounter=0;
	}
	return 0;
}
uint8_t tos_LeftButton_Listenner_For_MenuControl(void) {

			if(READ_LEFT_BTN){
				if(leftbtncounter>=BTN_LONG_PRESS_TIME){ leftbtncounter=0;return 2;}
				if(leftbtncounter>=BTN_SHORT_PRESS_TIME){ leftbtncounter=0;return 1;}
				 leftbtncounter=0;
			}
			return 0;
}

uint8_t tos_EnterButton_Listenner_For_MenuControl(void) {
			if(READ_ENTER_BTN){
				if(enterbtncounter>=BTN_LONG_PRESS_TIME){ enterbtncounter=0;return 2;}
				if(enterbtncounter>=BTN_SHORT_PRESS_TIME){ enterbtncounter=0;return 1;}
				 enterbtncounter=0;
			}
			return 0;
}
void tos_ButtonCounterIncrease(void){
	if(!READ_ENTER_BTN)enterbtncounter++;
	else if(!READ_LEFT_BTN)leftbtncounter++;
	else if(!READ_RIGHT_BTN)rightbtncounter++;
}
