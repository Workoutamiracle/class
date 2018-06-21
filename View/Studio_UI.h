/*
 * Studio_UI.h
 *
 *  Created on: 2015年4月25日
 *      Author: Administrator
 */

#ifndef STUDIO_UI_H_
#define STUDIO_UI_H_

//演出厅数据结点定义
typedef struct{
	int id;				//演出厅ID
	char name[30];		//演出厅名称
	int rowsCount;		//座位行数
	int colsCount;		//座位列数
	int seatsCount;		//座位个数
}studio_t;

//演出厅链表结点定义
typedef struct studio_node{
	studio_t data;		
	struct studio_node *next;
	struct studio_node *prev;
}studio_node_t,*studio_list_t;


int Studio_UI_Add(void);

int Studio_UI_Modify(int id);

int Studio_UI_Delete(int id);

//界面层入口函数
void Studio_UI_MgtEntry(void);

#endif /* STUDIO_UI_H_ */
