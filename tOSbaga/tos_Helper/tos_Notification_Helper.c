#include "tos_Notification_Helper.h"



tos_Notification *  tos_Notification_CreateRoot(tos_Notification * root){
	root=NULL;
	root=tos_Notification_CreateNode(0);
	root->appName="root";
	root->appName="root";
    return root;
}
tos_Notification *  tos_Notification_SetFirstNode(tos_Notification * root,tos_Notification * node){
    node=NULL;
    node=root;
    return node;
}

tos_Notification * tos_Notification_CreateNode(uint16_t index){
	tos_Notification * node;
	node=(tos_Notification *)malloc(sizeof(tos_Notification));
	if(node){
		node->index=index;
		node->next=NULL;
	}
	return node;
}

void tos_Notification_RemoveNode(tos_Notification *previous,tos_Notification *node){

	if(!node){
		return;
	}
	if(previous){
		previous->next=node->next;
	}
	free(node);
	return;
}


void PrintList(tos_Notification * root){
	tos_Notification * tmp=root;
	while(tmp){
		printf("%d,",tmp->index);
		tmp=tmp->next;
	}
	return;
}

uint8_t tos_NotificationGetSize(tos_Notification * root){
	tos_Notification * tmp=root;
	while(tmp){
    if(tmp->next==NULL)	return (tmp->index+1);
	tmp=tmp->next;
	}

}


tos_Notification *tos_NotificationGetItem(tos_Notification * root,uint16_t itemIndex){
		tos_Notification * tmp=root;
	if( itemIndex<tos_NotificationGetSize(root)){
		while(tmp){
	if(tmp->index==itemIndex){
		return tmp;
	}tmp=tmp->next;
	}}
        return NULL;
}


tos_Notification * tos_NotificationPushItem(tos_Notification * node,char *appName,char *notification){
		tos_Notification * tmp;
		tmp=tos_Notification_CreateNode(tos_NotificationGetSize(node));
		if(appName!=NULL)tmp->appName =appName;
		if(notification!=NULL) tmp->appNot =notification;
        node->next=tmp;
        node=node->next;
        return node;

}

void tos_NotificationDelItem(tos_Notification *root,tos_Notification *node,uint16_t index){
		node=root;
		tos_Notification * tmp=NULL;
		while(node){
			if(node->index==index){
				if(tmp==NULL){
					root=node->next;
				}
				tos_Notification_RemoveNode(tmp,node);
				break;
			}
			tmp=node;
			node=node->next;
		}
}


