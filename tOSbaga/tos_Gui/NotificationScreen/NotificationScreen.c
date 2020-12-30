/*
 * NotificationScreen.c
 *
 *  Created on: 18 Ara 2020
 *      Author: neset
 */
#include "NotificationScreen.h"
#include "../../tOSbaga.h"

static lv_style_t style_screen,sb_style,bg_style,scrl_style,appName_Style,notification_Style;
lv_obj_t * notBox;
tos_Notification * root, * node;
char NS_buffer[16];
int8_t myPos;
uint8_t selectedItem;
bool isOpenNotificationBox,NS_isBtnPressed,NS_taskController;
uint8_t NS_rightBtnListen=0,NS_leftBtnListen=0;

void NotificationScreen_ItemsStyleInit(bool theme);
tos_Position NotificationScreen_ItemsetPos(int8_t index);
int8_t NotificationScreen_GetMaxScroll(tos_Notification* node);
void NotificationScreen_Items(char *appName,char * appNotification,tos_Position pos,bool isSelected);
void NotificationScreen_SetOnScreenItems(tos_Notification * root,tos_Notification* node,int8_t posIndex);
void NotificationScreen_NotificationBox(char * appNotification);
/*This function using for initialization notification screen*/
void tos_NotificationScreen_Init(bool theme){
	lv_obj_clean(lv_scr_act());
	lv_style_copy(&style_screen, &lv_style_plain);
	if(theme){
		style_screen.body.main_color = LV_COLOR_BLACK;
		style_screen.body.grad_color = LV_COLOR_BLACK;
	}else{
		style_screen.body.main_color = LV_COLOR_WHITE;
		style_screen.body.grad_color = LV_COLOR_WHITE;
	}	lv_obj_set_style(lv_scr_act(), &style_screen);
    NotificationScreen_ItemsStyleInit(theme);

	root=tos_Notification_CreateRoot(root);
    node=tos_Notification_SetFirstNode(root,node);

    myPos=0;
    isOpenNotificationBox=false;
    NS_isBtnPressed=false;
    NotificationScreen_SetOnScreenItems(root,node,myPos);
    NS_taskController=true;

}
/*This function using for control to buttons*/
void NotificationScreen_ButtonController(void){
	if(!NS_isBtnPressed){
		NS_isBtnPressed=true;
		  if(2==NS_rightBtnListen){
			  //open
			  if(!isOpenNotificationBox){
				  isOpenNotificationBox=true;
				  char * tmp=tos_NotificationGetItem(root,selectedItem)->appNot;
				    NotificationScreen_NotificationBox(tmp);
			  }
		  }
		  if(1==NS_rightBtnListen) {
		  			  if(!isOpenNotificationBox){
		  			  //minus
		  				lv_obj_clean(lv_scr_act());
		  				if(myPos>-NotificationScreen_GetMaxScroll(node))myPos--;
		  				NotificationScreen_SetOnScreenItems(root,node,myPos);
		  			  }else {isOpenNotificationBox=false;
		  			  //remove
		  				lv_obj_clean(lv_scr_act());
		  				notBox = NULL;
		  			    tos_NotificationDelItem(root,node,selectedItem);
		  				NotificationScreen_SetOnScreenItems(root,node,myPos);

		  			  }
		  		  }
		  if(1==NS_leftBtnListen) {
			  //plus
			  if(!isOpenNotificationBox){
				lv_obj_clean(lv_scr_act());
				if(myPos<0)myPos++;
				NotificationScreen_SetOnScreenItems(root,node,myPos);
			  }else{isOpenNotificationBox=false;
				  lv_mbox_start_auto_close(notBox,0);
			  }
		  }
		  NS_isBtnPressed=false;
		  NS_rightBtnListen=tos_RightButton_Listenner_For_MenuControl();
		  NS_leftBtnListen =tos_LeftButton_Listenner_For_MenuControl();

	}
}
/*This function using for create notification items
 * @param appName using for get app name
 * @param appNotification for get app notification text
 * @param pos set item position
 * @param isSelected get statu (is first item on screen?) */
void NotificationScreen_Items(char *appName,char * appNotification,tos_Position pos,bool isSelected){
	  lv_obj_t * itemCanvas = lv_page_create(lv_scr_act(), NULL);
	  lv_obj_set_size(itemCanvas, 200, 50);
	  lv_page_set_sb_mode(itemCanvas,LV_SB_MODE_OFF);
	  lv_page_set_style(itemCanvas, LV_PAGE_STYLE_BG, &bg_style);
	  lv_page_set_style(itemCanvas, LV_PAGE_STYLE_SB, &sb_style);
	  lv_page_set_style(itemCanvas, LV_PAGE_STYLE_SCRL, &scrl_style);
	  lv_obj_align(itemCanvas, NULL, LV_ALIGN_CENTER, pos.x, pos.y);

	  if(strlen(appName)>=12)  {
		snprintf(NS_buffer,14, "%.9s ...",appName);
	  }else snprintf(NS_buffer,14, "%s",appName);

	  lv_obj_t * appNameLbl = lv_label_create(itemCanvas, NULL);
	  lv_obj_set_width(appNameLbl, 50);
	  lv_label_set_style(appNameLbl, LV_LABEL_STYLE_MAIN, &appName_Style);
	  lv_label_set_text(appNameLbl, NS_buffer);
	  lv_obj_align(appNameLbl, itemCanvas, LV_ALIGN_IN_TOP_LEFT, 20, 0);

	  lv_obj_t * appNotLbl = lv_label_create(itemCanvas, NULL);
	  lv_label_set_text(appNotLbl, appNotification);
	  lv_label_set_style(appNotLbl, LV_LABEL_STYLE_MAIN, &notification_Style);
	  lv_obj_align(appNotLbl, itemCanvas, LV_ALIGN_IN_BOTTOM_LEFT, 20, 0);

	  lv_obj_t * isSelettedItem = lv_cb_create(itemCanvas, NULL);
	  lv_obj_align(isSelettedItem, itemCanvas, LV_ALIGN_IN_RIGHT_MID, 80, 0);
	  lv_cb_set_checked(isSelettedItem,isSelected);
	  lv_cb_set_text(isSelettedItem,"");
}
/*This function using for notification box*/
void NotificationScreen_NotificationBox(char * appNotification){
    static const char * btns[] ={"Okey", "Delete", ""};

    notBox = lv_mbox_create(lv_scr_act(), NULL);
    lv_mbox_add_btns(notBox, btns);
    lv_mbox_set_text(notBox, appNotification);
    lv_obj_set_width(notBox, 200);
    lv_obj_set_height(notBox, 150);
    lv_obj_align(notBox, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_mbox_set_style(notBox, LV_MBOX_STYLE_BG,  &sb_style);
    lv_mbox_set_style(notBox, LV_MBOX_STYLE_BTN_REL,  &scrl_style);
    lv_mbox_set_style(notBox, LV_MBOX_STYLE_BTN_TGL_PR,  &bg_style);
}

/*This function using for notification items set values(app name,app notification,position)
 * @param root using for first node
 * @param node using for all nodes
 * @param posIndex using for set position index*/
void NotificationScreen_SetOnScreenItems(tos_Notification * root,tos_Notification* node,int8_t posIndex){
	bool selected= false;
       for(uint8_t i=1;i<(uint8_t)tos_NotificationGetSize(node);i++){
    	   	   if(tos_NotificationGetItem(root,i) !=NULL){
    	           if(posIndex==0){selectedItem=i; selected=true;}
    	           else selected=false;
        NotificationScreen_Items(tos_NotificationGetItem(root,i)->appName,
        		tos_NotificationGetItem(root,i)->appNot,
				NotificationScreen_ItemsetPos(posIndex),selected);
        posIndex++;
    }
    }
}
/*This function using for set notification style init
 * created a style init because when create a notification then be not get again memory
 * @param theme using for select theme
 * true -> dark
 * false -> light*/
void NotificationScreen_ItemsStyleInit(bool theme){
    lv_style_copy(&scrl_style, &lv_style_plain);
    scrl_style.body.main_color = LV_COLOR_SILVER;
    scrl_style.body.grad_color = LV_COLOR_SILVER;
    scrl_style.body.border.color = LV_COLOR_BLACK;
    scrl_style.body.border.width = 0;

    lv_style_copy(&sb_style, &lv_style_plain);
    sb_style.body.main_color = LV_COLOR_WHITE;
    sb_style.body.grad_color = LV_COLOR_WHITE;
    sb_style.body.border.color = LV_COLOR_BLACK;
    sb_style.text.color =LV_COLOR_BLACK;
    sb_style.body.border.width = 1;
    sb_style.body.border.opa = LV_OPA_70;
    sb_style.body.opa = LV_OPA_70;
    sb_style.body.padding.right = 3;
    sb_style.body.padding.bottom = 3;
    sb_style.body.padding.inner = 8;
    lv_style_copy(&bg_style, &lv_style_plain);
    bg_style.body.main_color = LV_COLOR_WHITE;
    bg_style.body.grad_color = LV_COLOR_WHITE;
    bg_style.body.border.color = LV_COLOR_WHITE;
    bg_style.body.border.width = 0;
    bg_style.body.border.opa = LV_OPA_70;
    bg_style.body.opa = LV_OPA_70;
    if(theme){
    	sb_style.body.main_color = LV_COLOR_BLACK;
        sb_style.body.grad_color = LV_COLOR_BLACK;
        sb_style.body.border.color = LV_COLOR_WHITE;
        bg_style.body.main_color = LV_COLOR_BLACK;
        bg_style.body.grad_color = LV_COLOR_BLACK;
        bg_style.body.border.color = LV_COLOR_BLACK;
        sb_style.text.color =LV_COLOR_WHITE;
    }

	lv_style_copy(&appName_Style, &lv_style_plain);
	appName_Style.text.font = &lv_font_roboto_22;
	appName_Style.text.color = LV_COLOR_AQUA;

	lv_style_copy(&notification_Style, &lv_style_plain);
	notification_Style.text.font = &lv_font_roboto_16;
	notification_Style.text.color = LV_COLOR_BLACK;
}
/*This function using for set items position
 * @param index using for set position axis y*/
tos_Position NotificationScreen_ItemsetPos(int8_t index){
	tos_Position tmp;
	tmp.x=0; tmp.y=(index*55)-90;
	return tmp;
}
/*This function using for return can get max going scroll value
 * @param node using for get node*/
int8_t NotificationScreen_GetMaxScroll(tos_Notification* node){
	if(tos_NotificationGetSize(node)>=5){
		int8_t max=tos_NotificationGetSize(node)-2;
		return max;
	} return 0;
}

//Setter Getter Functions
void NotificationScreen_TaskControllerSet(bool active){
	NS_taskController = active;
}
bool NotificationScreen_TaskControllerGet(void){
	return NS_taskController;
}
void NotificationScreen_GetNotifications(char *appName,char* appNotification){
	  node=tos_NotificationPushItem(node,appName,appNotification);
}

