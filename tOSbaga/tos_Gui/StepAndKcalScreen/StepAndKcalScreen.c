/*
 * StepAndKcal.c
 *
 *  Created on: 14 Ara 2020
 *      Author: neset
 */

#include "StepAndKcalScreen.h"
#include "../../tOSbaga.h"


lv_obj_t *SAK_stepsArc,*SAK_kCalsArc,*SAK_distancesArc, *SAK_stepsLbl, *SAK_kcalsLbl, *SAK_distanceLbl;
char stepAndKcalBuffer[8],*SAK_buffTmp;
static lv_style_t style_screen,description_Style;

void StepAndKcal_Steps(bool theme);
void StepAndKcal_kCals(bool theme);
void StepAndKcal_Distances(bool unitType,bool theme);

void SAK_steps_angle_loader(void);
void SAK_kCals_angle_loader(void);
void SAK_distances_angle_loader(void);

uint16_t SAK_steps,SAK_kCals;
double SAK_distance;
bool SAk_taskController,SAK_unitType;

/* This function using for initiation steps and kcals screen set on Screen
 * @param unitType using for kilometers or miles
 * true->kilometers || fasle->miles
 * @param theme using for set Theme
 * true->dark || false->light
*/
void tos_StepAndKcalScreen_Init(bool unitType, bool theme){
	lv_obj_clean(lv_scr_act());
	lv_style_copy(&description_Style, &lv_style_plain);
	description_Style.text.font = &lv_font_unscii_8;
	description_Style.text.color = LV_COLOR_GRAY;

	lv_style_copy(&style_screen, &lv_style_plain);
	if(theme){
		style_screen.body.main_color = LV_COLOR_BLACK;
		style_screen.body.grad_color = LV_COLOR_BLACK;
		description_Style.text.color = LV_COLOR_SILVER;
	}else{
		style_screen.body.main_color = LV_COLOR_WHITE;
		style_screen.body.grad_color = LV_COLOR_WHITE;
		description_Style.text.color = LV_COLOR_SILVER;
	}	lv_obj_set_style(lv_scr_act(), &style_screen);

	SAK_unitType=unitType;
	SAK_buffTmp="null";

	StepAndKcal_Steps(theme);
	StepAndKcal_kCals(theme);
	StepAndKcal_Distances(unitType,theme);
	SAk_taskController=true;
}
/* This function using for initiation steps Objs on Screen
 * @param theme using for set Theme
 * true->dark || false->light
*/
void StepAndKcal_Steps(bool theme){
	//Static objs
	lv_obj_t * img1 = lv_img_create(lv_scr_act(), NULL);
	if(theme) lv_img_set_src(img1, &stepsBlack42x28);
	else lv_img_set_src(img1, &stepsWhite42x28);
	lv_obj_align(img1, NULL, LV_ALIGN_CENTER, 0, -83);

   	lv_obj_t * stepsDescLbl= lv_label_create(lv_scr_act(), NULL);
 	lv_label_set_style(stepsDescLbl, LV_LABEL_STYLE_MAIN, &description_Style);
   	lv_label_set_text(stepsDescLbl, "steps");
   	lv_obj_align(stepsDescLbl, NULL, LV_ALIGN_CENTER, 0, -9);

    static lv_style_t steps_Style;
    lv_style_copy(&steps_Style, &lv_style_plain);
    steps_Style.line.color = lv_color_make(101,204,53);
    steps_Style.line.width = 3;
    steps_Style.text.color = lv_color_make(101,204,53);
    steps_Style.text.font = &digital_font_for_number_30;

	//Dynamic objs
    SAK_stepsArc = lv_arc_create(lv_scr_act(), NULL);
    lv_obj_set_size(SAK_stepsArc, 65, 65);
    lv_arc_set_angles(SAK_stepsArc, 0, 360);
    lv_arc_set_style(SAK_stepsArc, LV_ARC_STYLE_MAIN, &steps_Style);
    lv_obj_align(SAK_stepsArc, NULL, LV_ALIGN_CENTER, 0, -83);

    SAK_stepsLbl = lv_label_create(lv_scr_act(), NULL);
 	lv_label_set_style(SAK_stepsLbl, LV_LABEL_STYLE_MAIN, &steps_Style);
   	lv_label_set_text(SAK_stepsLbl, "0000");
 	lv_obj_align(SAK_stepsLbl, NULL, LV_ALIGN_CENTER, 0, -30);
}
/* This function using for initiation kCals Objs on Screen
 * @param theme using for set Theme
 * true->dark || false->light
*/
void StepAndKcal_kCals(bool theme){
	//Static objs
	lv_obj_t * img1 = lv_img_create(lv_scr_act(), NULL);
	if(theme) lv_img_set_src(img1, &kCalsBlack42x28);
	else lv_img_set_src(img1, &kCalsWhite42x28);
	lv_obj_align(img1, NULL, LV_ALIGN_CENTER, -60, 37);

	static lv_style_t kCals_Style;
	lv_style_copy(&kCals_Style, &lv_style_plain);
	kCals_Style.line.color = lv_color_make(255,205,105);
    kCals_Style.line.width = 3;
    kCals_Style.text.color = lv_color_make(255,205,105);
    kCals_Style.text.font = &digital_font_for_number_30;

   	lv_obj_t * kCalsDescLbl= lv_label_create(lv_scr_act(), NULL);
 	lv_label_set_style(kCalsDescLbl, LV_LABEL_STYLE_MAIN, &description_Style);
   	lv_label_set_text(kCalsDescLbl, "kCals");
   	lv_obj_align(kCalsDescLbl, NULL, LV_ALIGN_CENTER, -60, 111);

    //Dynamic objs
    SAK_kCalsArc = lv_arc_create(lv_scr_act(), NULL);
    lv_obj_set_size(SAK_kCalsArc, 80, 80);
    lv_arc_set_angles(SAK_kCalsArc, 0, 360);
    lv_arc_set_style(SAK_kCalsArc, LV_ARC_STYLE_MAIN, &kCals_Style);
    lv_obj_align(SAK_kCalsArc, NULL, LV_ALIGN_CENTER,-60, 37);

    SAK_kcalsLbl = lv_label_create(lv_scr_act(), NULL);
   	lv_label_set_style(SAK_kcalsLbl, LV_LABEL_STYLE_MAIN, &kCals_Style);
   	lv_label_set_text(SAK_kcalsLbl, "0000");
   	lv_obj_align(SAK_kcalsLbl, NULL, LV_ALIGN_CENTER, -60, 90);
}
/* This function using for initiation kMeters Objs on Screen
 * @param unitType using for kilometers or miles
 * true->kilometers || fasle->miles
 * @param theme using for set Theme
 * true->dark || false->light
*/
void StepAndKcal_Distances(bool unitType,bool theme){
	//Static objs
	lv_obj_t * img1 = lv_img_create(lv_scr_act(), NULL);
	if(theme) lv_img_set_src(img1, &locationPointBlack42x28);
	else lv_img_set_src(img1, &locationPointWhite42x28);
	lv_obj_align(img1, NULL, LV_ALIGN_CENTER, 60, 37);

    static lv_style_t distance_Style;
    lv_style_copy(&distance_Style, &lv_style_plain);
    distance_Style.line.color = lv_color_make(214,23,32);
    distance_Style.line.width = 3;
    distance_Style.text.color = lv_color_make(214,23,32);
    distance_Style.text.font = &digital_font_for_number_30;

   	lv_obj_t * distDescLbl= lv_label_create(lv_scr_act(), NULL);
 	lv_label_set_style(distDescLbl, LV_LABEL_STYLE_MAIN, &description_Style);
 	if(unitType) lv_label_set_text(distDescLbl, "km");
 	else lv_label_set_text(distDescLbl, "miles");
   	lv_obj_align(distDescLbl, NULL, LV_ALIGN_CENTER, 60, 111);

    //Dynamic objs
    SAK_distancesArc = lv_arc_create(lv_scr_act(), NULL);
    lv_obj_set_size(SAK_distancesArc, 80, 80);
    lv_arc_set_angles(SAK_distancesArc, 0, 360);
    lv_arc_set_style(SAK_distancesArc, LV_ARC_STYLE_MAIN, &distance_Style);
    lv_obj_align(SAK_distancesArc, NULL, LV_ALIGN_CENTER, 60, 37);

    SAK_distanceLbl = lv_label_create(lv_scr_act(), NULL);
   	lv_label_set_style(SAK_distanceLbl, LV_LABEL_STYLE_MAIN, &distance_Style);
   	lv_label_set_text(SAK_distanceLbl, "0000.00");
   	lv_obj_align(SAK_distanceLbl, NULL, LV_ALIGN_CENTER, 60, 90);
}

//Update Functions
/*This function using for update all update functions*/
void SAK_Updater(void){
	if(SAk_taskController){
		SAK_steps_angle_loader();
		SAK_kCals_angle_loader();
		SAK_distances_angle_loader();
	}
}
/* This function using for calculate and set the angle for arcObjects,
We use here set steps
*/
void SAK_steps_angle_loader(void)
{
 		snprintf(stepAndKcalBuffer,8, "%05d",SAK_steps);
 		lv_label_set_text(SAK_stepsLbl, stepAndKcalBuffer);
 		lv_obj_align(SAK_stepsLbl, NULL, LV_ALIGN_CENTER, 0, -30);

 		if(SAK_steps<=10000){
 			double stepsTemp = tos_Ratio(SAK_steps, 0, 10000, 0, 359);
 			if(stepsTemp < 180) lv_arc_set_angles(SAK_stepsArc, 180-stepsTemp ,180);
 			    else lv_arc_set_angles(SAK_stepsArc, 540-stepsTemp ,180);
 		}
}

/* This function using for calculate and set the angle for arcObjects,
We use here set kCAls
*/
void SAK_kCals_angle_loader(void)
{
 		snprintf(stepAndKcalBuffer,8, "%05d",SAK_kCals);
 		lv_label_set_text(SAK_kcalsLbl, stepAndKcalBuffer);
 	   	lv_obj_align(SAK_kcalsLbl, NULL, LV_ALIGN_CENTER, -60, 90);

 	   	if(SAK_kCals<=10000){
 			double kCalsTemp = tos_Ratio(SAK_kCals, 0, 10000, 0, 359);
 			if(kCalsTemp < 180) lv_arc_set_angles(SAK_kCalsArc, 180-kCalsTemp ,180);
 			    else lv_arc_set_angles(SAK_kCalsArc, 540-kCalsTemp ,180);
 	   	}
}

/* This function using for calculate and set the angle for arcObjects,
We use here set kCAls
*/
void SAK_distances_angle_loader(void){
		float distTmp=(float)tos_distance_Calc(SAK_unitType,SAK_steps);

		uint16_t tmp1=distTmp; float tmp2=distTmp-tmp1; tmp2*=1000;
	 	snprintf(stepAndKcalBuffer,8, "%03d.%03d",tmp1,(uint16_t)tmp2);
	 	lv_label_set_text(SAK_distanceLbl, stepAndKcalBuffer);
	 	lv_obj_align(SAK_distanceLbl, NULL, LV_ALIGN_CENTER, 60, 90);

 	   	double distanceTemp = tos_Ratio(distTmp, 0, 1000, 0, 359);
 		if(distanceTemp < 180) lv_arc_set_angles(SAK_distancesArc, 180-distanceTemp ,180);
 			else lv_arc_set_angles(SAK_distancesArc, 540-distanceTemp ,180);
}
//Setter Getter Functions
void StepAndKcal_SetStepsAndKcals(uint16_t getSteps, uint16_t getKcals) {
	SAK_steps =getSteps;
	SAK_kCals =getKcals;
}
void StepAndKcal_TaskControllerSet(bool active){
	SAk_taskController = active;
}

