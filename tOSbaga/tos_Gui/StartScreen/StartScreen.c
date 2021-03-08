/*
 * StartScreen.c
 *
 *  Created on: 8 Ara 2020
 *      Author: neset
 */
#include "StartScreen.h"
#include "../../tOSbaga.h"
#include "stdio.h"


void tos_StartScreen_Init(void) {
	static lv_style_t style_screen;
	lv_style_copy(&style_screen, &lv_style_plain);
	style_screen.body.main_color = LV_COLOR_BLACK;
	style_screen.body.grad_color = LV_COLOR_BLACK;
	style_screen.text.color = lv_color_make(68,133,247);
	style_screen.text.font = &lv_font_roboto_28;
	lv_obj_set_style(lv_scr_act(), &style_screen);

	lv_obj_t * img1 = lv_img_create(lv_scr_act(), NULL);
	lv_img_set_src(img1, &tos75x75);
	lv_obj_align(img1, NULL, LV_ALIGN_CENTER, 0, -20);

	lv_obj_t * tosLbl =lv_label_create(lv_scr_act(), NULL);
 	lv_label_set_style(tosLbl, LV_LABEL_STYLE_MAIN, &style_screen);
 	lv_label_set_text(tosLbl, "tOSbaga fsw 1.0");
 	lv_obj_align(tosLbl, NULL, LV_ALIGN_CENTER, 0, 50);
}
