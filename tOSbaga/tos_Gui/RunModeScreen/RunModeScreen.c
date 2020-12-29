/*
 * RunModeScreen.c
 *
 *  Created on: Dec 15, 2020
 *      Author: neset
 */

#include "RunModeScreen.h"
#include "../../tOSbaga.h"


lv_obj_t *RM_Lbl,*RM_targetTimeBar,*RM_stepsArc,*RM_stepsLbl,*RM_kCalsArc,*RM_kCalsLbl,*RM_distArc,*RM_distLbl;

static lv_style_t style_screen,description_Style;

char runModeBuffer[64];
uint8_t RMtimeSetVal,RMseconds,RMminutes,RMhours,RMtargetSeconds=50,RMtargetMinutes,RMtargetHours;
uint16_t RMmilisecs,RMstepsBeff,RMsteps,RMkCalsBeff,RMkCals;
float RMdistancesBeff,RMdistances;
bool RM_theme,RM_taskController,isStartRun,RMfirstVAl,RM_unitType;

void RunMode_Obj_Init(void);
void RunMode_Steps(bool theme);
void RunMode_kCals(bool theme);
void RunMode_Distances(bool unitType, bool theme);
void RunMode_RunTimeLblController(void);
void RunMode_RunTimeSetVal(void);
void RunMode_RunTimeUpdateVal(void);
void RunMode_FistValueSet(void);

void RunMode_RunMode_Updater(void);
void RunMode_steps_angle_loader(void);
void RunMode_kCals_angle_loader(void);
void RunMode_distances_angle_loader(void);

/*This function using for initialization Run Mode screen*/
void tos_RunModeScreen_Init(bool unitType,bool theme){
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

	RMfirstVAl=true;
	RMtimeSetVal=0;
	isStartRun=false;

	RM_theme=theme;
	RM_unitType=unitType;
	RunMode_Obj_Init();
	RunMode_Steps(theme);
	RunMode_kCals(theme);
	RunMode_Distances(unitType,theme);
	RM_taskController=true;
	lv_task_create(RunModeScreen_Updater, 500, LV_TASK_PRIO_LOWEST, NULL);
}


/*This function using for create and set objects on screen*/
void RunMode_Obj_Init(void){

    static lv_style_t obj_Style,indic_Style;
    lv_style_copy(&obj_Style, &lv_style_plain);
    obj_Style.text.color = LV_COLOR_BLACK;
    if(RM_theme) obj_Style.text.color = LV_COLOR_SILVER;
    obj_Style.text.font = &digital_font_for_number_30;
    obj_Style.body.main_color   = lv_color_make(0xFF, 0xA5, 0x00);
    obj_Style.body.grad_color   = lv_color_make(0xFF, 0xA5, 0x00);
    obj_Style.body.radius= 10;
    obj_Style.body.opa=200;
    lv_style_copy(&indic_Style, &obj_Style);
    indic_Style.body.main_color   = lv_color_make(0x00, 0xFF, 0xFF);
    indic_Style.body.grad_color   = lv_color_make(0x00, 0xFF, 0xFF);
    indic_Style.body.opa=255;

    RM_targetTimeBar = lv_bar_create(lv_scr_act(), NULL);
    lv_bar_set_style(RM_targetTimeBar, LV_BAR_STYLE_BG, &obj_Style);
    lv_bar_set_style(RM_targetTimeBar, LV_BAR_STYLE_INDIC, &indic_Style);
    lv_obj_set_size(RM_targetTimeBar, 150, 30);
    lv_obj_align(RM_targetTimeBar, NULL, LV_ALIGN_CENTER, 0, 80);
    lv_bar_set_range(RM_targetTimeBar,0,100);
    lv_bar_set_value(RM_targetTimeBar, 0, LV_ANIM_OFF);

    //MAGENTA -> FF00FF
   	//AQUA -> 00FFFF
	//ORANGE -> FFA500

    RM_Lbl = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_recolor(RM_Lbl, true);
 	lv_label_set_style(RM_Lbl, LV_LABEL_STYLE_MAIN, &obj_Style);
	snprintf(runModeBuffer,64, "#FF00FF %02d#.#00FFFF %02d#.#FFA500 %02d#.%03d",
			RMhours,RMminutes,RMseconds,RMmilisecs);
	lv_label_set_text(RM_Lbl, runModeBuffer);
 	lv_obj_align(RM_Lbl, NULL, LV_ALIGN_CENTER, 0, 40);
}
/* This function using for initiation kCAls Objs on Screen
 * @param theme using for set Theme
 * true->dark || false->light
*/
void RunMode_kCals(bool theme){
	//Static objs
	lv_obj_t * img1 = lv_img_create(lv_scr_act(), NULL);
	if(theme) lv_img_set_src(img1, &kCalsBlack42x28);
	else lv_img_set_src(img1, &kCalsWhite42x28);
	lv_obj_align(img1, NULL, LV_ALIGN_CENTER, -75, -60);

 	lv_obj_t * stepsDescLbl= lv_label_create(lv_scr_act(), NULL);
 	lv_label_set_style(stepsDescLbl, LV_LABEL_STYLE_MAIN, &description_Style);
   	lv_label_set_text(stepsDescLbl, "steps");
   	lv_obj_align(stepsDescLbl, NULL, LV_ALIGN_CENTER, -75, 3);

	static lv_style_t kCals_Style;
	lv_style_copy(&kCals_Style, &lv_style_plain);
	kCals_Style.line.color = lv_color_make(255,205,105);
    kCals_Style.line.width = 3;
    kCals_Style.text.color = lv_color_make(255,205,105);
    kCals_Style.text.font = &digital_font_for_number_30;

	//Dynamic objs
    RM_kCalsArc = lv_arc_create(lv_scr_act(), NULL);
    lv_obj_set_size(RM_kCalsArc, 60, 60);
    lv_arc_set_angles(RM_kCalsArc, 0, 360);
    lv_arc_set_style(RM_kCalsArc, LV_ARC_STYLE_MAIN, &kCals_Style);
    lv_obj_align(RM_kCalsArc, NULL, LV_ALIGN_CENTER, -75, -60);

    RM_kCalsLbl = lv_label_create(lv_scr_act(), NULL);
 	lv_label_set_style(RM_kCalsLbl, LV_LABEL_STYLE_MAIN, &kCals_Style);
   	lv_label_set_text(RM_kCalsLbl, "0000");
 	lv_obj_align(RM_kCalsLbl, NULL, LV_ALIGN_CENTER, -75, -15);

}
/* This function using for initiation Steps Objs on Screen
 * @param theme using for set Theme
 * true->dark || false->light
*/
void RunMode_Steps(bool theme){
	//Static objs
	lv_obj_t * img1 = lv_img_create(lv_scr_act(), NULL);
	if(theme) lv_img_set_src(img1, &stepsBlack42x28);
	else lv_img_set_src(img1, &stepsWhite42x28);
	lv_obj_align(img1, NULL, LV_ALIGN_CENTER, 0, -60);

 	lv_obj_t * stepsDescLbl= lv_label_create(lv_scr_act(), NULL);
 	lv_label_set_style(stepsDescLbl, LV_LABEL_STYLE_MAIN, &description_Style);
   	lv_label_set_text(stepsDescLbl, "steps");
   	lv_obj_align(stepsDescLbl, NULL, LV_ALIGN_CENTER, 0, 3);

    static lv_style_t steps_Style;
    lv_style_copy(&steps_Style, &lv_style_plain);
    steps_Style.line.color = lv_color_make(101,204,53);
    steps_Style.line.width = 3;
    steps_Style.text.color = lv_color_make(101,204,53);
    steps_Style.text.font = &digital_font_for_number_30;

	//Dynamic objs
    RM_stepsArc = lv_arc_create(lv_scr_act(), NULL);
    lv_obj_set_size(RM_stepsArc, 60, 60);
    lv_arc_set_angles(RM_stepsArc, 0, 360);
    lv_arc_set_style(RM_stepsArc, LV_ARC_STYLE_MAIN, &steps_Style);
    lv_obj_align(RM_stepsArc, NULL, LV_ALIGN_CENTER, 0, -60);

    RM_stepsLbl = lv_label_create(lv_scr_act(), NULL);
 	lv_label_set_style(RM_stepsLbl, LV_LABEL_STYLE_MAIN, &steps_Style);
   	lv_label_set_text(RM_stepsLbl, "00000");
 	lv_obj_align(RM_stepsLbl, NULL, LV_ALIGN_CENTER, 0, -15);

}
/* This function using for initiation Distances Objs on Screen
 * @param theme using for set Theme
 * true->dark || false->light
*/
void RunMode_Distances(bool unitType,bool theme){
	//Static objs
	lv_obj_t * img1 = lv_img_create(lv_scr_act(), NULL);
	if(theme) lv_img_set_src(img1, &locationPointBlack42x28);
	else lv_img_set_src(img1, &locationPointWhite42x28);
	lv_obj_align(img1, NULL, LV_ALIGN_CENTER, 75, -60);

 	lv_obj_t * distDescLbl= lv_label_create(lv_scr_act(), NULL);
 	lv_label_set_style(distDescLbl, LV_LABEL_STYLE_MAIN, &description_Style);
 	if(unitType) lv_label_set_text(distDescLbl, "km");
 	else lv_label_set_text(distDescLbl, "miles");
   	lv_obj_align(distDescLbl, NULL, LV_ALIGN_CENTER, 75, 3);

    static lv_style_t distance_Style;
    lv_style_copy(&distance_Style, &lv_style_plain);
    distance_Style.line.color = lv_color_make(214,23,32);
    distance_Style.line.width = 3;
    distance_Style.text.color = lv_color_make(214,23,32);
    distance_Style.text.font = &digital_font_for_number_30;

	//Dynamic objs
    RM_distArc = lv_arc_create(lv_scr_act(), NULL);
    lv_obj_set_size(RM_distArc, 60, 60);
    lv_arc_set_angles(RM_distArc, 0, 360);
    lv_arc_set_style(RM_distArc, LV_ARC_STYLE_MAIN, &distance_Style);
    lv_obj_align(RM_distArc, NULL, LV_ALIGN_CENTER, 75, -60);

    RM_distLbl = lv_label_create(lv_scr_act(), NULL);
 	lv_label_set_style(RM_distLbl, LV_LABEL_STYLE_MAIN, &distance_Style);
   	lv_label_set_text(RM_distLbl, "00.000");
 	lv_obj_align(RM_distLbl, NULL, LV_ALIGN_CENTER, 75, -15);
}
/*This function using for update all updater functions*/
void RunModeScreen_Updater(lv_task_t *t){
	if(RM_taskController){
		 RunMode_RunMode_Updater();
		 RunMode_steps_angle_loader();
		 RunMode_kCals_angle_loader();
		 RunMode_distances_angle_loader();
	}else lv_task_del(t);
}
/*This function using for update to current label*/
void RunMode_RunMode_Updater(void){
		if(0==RMtimeSetVal){
			uint16_t targetValTmp = RMtargetSeconds+(RMtargetMinutes*60)+(RMtargetHours*60*60);
			uint16_t nowValTmp = RMseconds+(RMminutes*60)+(RMhours*60*60);
			uint8_t targetBarTmp = tos_Ratio(nowValTmp, 0,targetValTmp ,0, 100);
		    lv_bar_set_value(RM_targetTimeBar, targetBarTmp, LV_ANIM_OFF);

		snprintf(runModeBuffer,64, "#FF00FF %02d#.#00FFFF %02d#.#FFA500 %02d#.%03d",
				RMhours,RMminutes,RMseconds,RMmilisecs);
		lv_label_set_text(RM_Lbl, runModeBuffer);
	 	lv_obj_align(RM_Lbl, NULL, LV_ALIGN_CENTER, 0, 40);
	}
}
/* This function using for calculate and set the angle for arcObjects,
We use here set steps
*/
void RunMode_steps_angle_loader(void)
{	    snprintf(runModeBuffer,8, "%05d",(RMsteps-RMstepsBeff));
 		lv_label_set_text(RM_stepsLbl, runModeBuffer);
 		lv_obj_align(RM_stepsLbl, NULL, LV_ALIGN_CENTER, 0, -15);

 		if((RMsteps-RMstepsBeff)<=10000){
 			double stepsTemp = tos_Ratio((RMsteps-RMstepsBeff), 0, 10000, 0, 359);
 			if(stepsTemp < 180) lv_arc_set_angles(RM_stepsArc, 180-stepsTemp ,180);
 			    else lv_arc_set_angles(RM_stepsArc, 540-stepsTemp ,180);
 		}
}
/* This function using for calculate and set the angle for arcObjects,
We use here set kCAls
*/
void RunMode_kCals_angle_loader(void)
{ 		snprintf(runModeBuffer,8, "%05d",(RMkCals-RMkCalsBeff));
 		lv_label_set_text(RM_kCalsLbl, runModeBuffer);
 	   	lv_obj_align(RM_kCalsLbl, NULL, LV_ALIGN_CENTER, -75, -15);

 	   	if((RMkCals-RMkCalsBeff)<=10000){
 			double kCalsTemp = tos_Ratio((RMkCals-RMkCalsBeff), 0, 10000, 0, 359);
 			if(kCalsTemp < 180) lv_arc_set_angles(RM_kCalsArc, 180-kCalsTemp ,180);
 			    else lv_arc_set_angles(RM_kCalsArc, 540-kCalsTemp ,180);
 	   	}
}
/* This function using for calculate and set the angle for arcObjects,
We use here set kCAls
*/
void RunMode_distances_angle_loader(void){
		RMdistances=(float)tos_distance_Calc(RM_unitType,RMsteps);
		float distTmp =RMdistances-RMdistancesBeff;
		uint16_t tmp1=distTmp; float tmp2=distTmp-tmp1; tmp2*=1000;
	 	snprintf(runModeBuffer,8, "%02d.%03d",tmp1,(uint16_t)tmp2);
	 	lv_label_set_text(RM_distLbl, runModeBuffer);
	 	lv_obj_align(RM_distLbl, NULL, LV_ALIGN_CENTER, 75,-15);

 	   	double distanceTemp = tos_Ratio(distTmp, 0, 1000, 0, 359);
 		if(distanceTemp < 180) lv_arc_set_angles(RM_distArc, 180-distanceTemp ,180);
 			else lv_arc_set_angles(RM_distArc, 540-distanceTemp ,180);
}
/*This function using for control to buttons*/
void RunMode_ButtonController(void){
	  if(1==tos_LeftButton_Listenner_For_MenuControl()) {
		  //Time Set
		  RunMode_RunTimeUpdateVal();
	  }
	  if(2==tos_LeftButton_Listenner_For_MenuControl()){
		  //Time Set Open/Close
		  RunMode_RunTimeSetVal();
	  }

	  if(1==tos_RightButton_Listenner_For_MenuControl()) {
		  //Timer start/stop
		  if(0==RMtimeSetVal && !isStartRun){ RunMode_FistValueSet();
			  HAL_TIM_Base_Start_IT(&TOS_RUNMODE_TIMER); isStartRun=true;
		  }
		  else { isStartRun=false;
			  HAL_TIM_Base_Stop_IT(&TOS_RUNMODE_TIMER);
		  }
	  }
	  if(2==tos_RightButton_Listenner_For_MenuControl()){
		  //Clear and stop
		   RMmilisecs=0; RMfirstVAl=true;
			  RMseconds=0;RMminutes=0;RMhours=0;RMtargetSeconds=0;RMtargetMinutes=0;RMtargetHours=0;
			  HAL_TIM_Base_Stop_IT(&TOS_RUNMODE_TIMER);
			  RunMode_RunTimeLblController();
	  }
}
/*This function using for update time
 * this function must be called in timer interupt function*/
void RunMode_Update_Time(void){
	//Colled by stm32f4xx_it.c TIM4_IRQHandler func
	if(RM_taskController){
		if(RMtargetHours==RMhours && RMtargetMinutes ==RMminutes && RMtargetSeconds==RMseconds)
		HAL_TIM_Base_Stop_IT(&TOS_RUNMODE_TIMER);
		RMmilisecs++;
			if(RMmilisecs==1000){
				RMmilisecs=0;
				RMseconds++;
				if(RMseconds==60){
					RMseconds=0;
					RMminutes++;
					if(RMminutes==60){
						RMminutes=0;
						RMhours++;
					}
				}
			}
	}

}
/*This function using for  control the set target values chouser*/
void RunMode_RunTimeSetVal(void){
	RMtimeSetVal++;
	if(4==RMtimeSetVal)RMtimeSetVal=0;
	RunMode_RunTimeLblController();
}

/*This function using for  update and plus the target values*/
void RunMode_RunTimeUpdateVal(void){
	switch(RMtimeSetVal){
	case 1: RMtargetHours++; if(24==RMtargetHours)RMtargetHours=0; break;
	case 2: RMtargetMinutes++; if(60==RMtargetMinutes)RMtargetMinutes=0; break;
	case 3: RMtargetSeconds++; if(60==RMtargetSeconds)RMtargetSeconds=0; break;
	default: break;
	}
	RunMode_RunTimeLblController();
}

/*This function using for update set time label*/
void RunMode_RunTimeLblController(void){
	switch(RMtimeSetVal){
	case 1:
			if(RM_theme)
				 snprintf(runModeBuffer,64, "#FFFFFF %02d#.#00FFFF %02d#.#FFA500 %02d#.%03d",
					RMtargetHours,RMtargetMinutes,RMtargetSeconds,RMmilisecs);
			else snprintf(runModeBuffer,64, "#000000 %02d#.#00FFFF %02d#.#FFA500 %02d#.%03d",
					RMtargetHours,RMtargetMinutes,RMtargetSeconds,RMmilisecs);
		break;
	case 2:
			if(RM_theme)
				 snprintf(runModeBuffer,64, "#FF00FF %02d#.#FFFFFF %02d#.#FFA500 %02d#.%03d",
					RMtargetHours,RMtargetMinutes,RMtargetSeconds,RMmilisecs);
			else snprintf(runModeBuffer,64, "#FF00FF %02d#.#000000 %02d#.#FFA500 %02d#.%03d",
					RMtargetHours,RMtargetMinutes,RMtargetSeconds,RMmilisecs);
		break;
	case 3:
		if(RM_theme)
			 snprintf(runModeBuffer,64, "#FF00FF %02d#.#00FFFF %02d#.#FFFFFF %02d#.%03d",
					RMtargetHours,RMtargetMinutes,RMtargetSeconds,RMmilisecs);
		else snprintf(runModeBuffer,64, "#FF00FF %02d#.#00FFFF %02d#.#000000 %02d#.%03d",
					RMtargetHours,RMtargetMinutes,RMtargetSeconds,RMmilisecs);
		break;
	default: snprintf(runModeBuffer,64, "#FF00FF %02d#.#00FFFF %02d#.#FFA500 %02d#.%03d",
					RMtargetHours,RMtargetMinutes,RMtargetSeconds,RMmilisecs); break;
	}
	lv_label_set_text(RM_Lbl, runModeBuffer);
 	lv_obj_align(RM_Lbl, NULL, LV_ALIGN_CENTER, 0, 40);

}
//Setter Getter Functions
void RunMode_FistValueSet(void){
	if(RMfirstVAl){
		RMstepsBeff=RMsteps;
		RMkCalsBeff=RMkCals;
		RMdistances=(float)tos_distance_Calc(RM_unitType,RMsteps);
		RMdistancesBeff=RMdistances;
		RMfirstVAl=false;
	}

}
void RunMode_SetStepsAndKcals(uint16_t getSteps, uint16_t getKcals) {
	RMsteps =getSteps;
	RMkCals =getKcals;
}
void RunMode_TaskControllerSet(bool active){
	RM_taskController = active;
}
bool RunMode_TaskControllerGet(void){
	return RM_taskController;
}
