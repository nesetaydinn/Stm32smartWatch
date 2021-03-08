/*
 * lampScreen.c
 *
 *  Created on: Mar 8, 2021
 *      Author: neset
 */



#include "LampScreen.h"
#include "../../tOSbaga.h"
#include "stdio.h"


void tos_LampScreen_Init(void) {
	static lv_style_t style_screen;
	lv_style_copy(&style_screen, &lv_style_plain);
	style_screen.body.main_color = LV_COLOR_WHITE;
	style_screen.body.grad_color = LV_COLOR_WHITE;
	lv_obj_set_style(lv_scr_act(), &style_screen);
}
