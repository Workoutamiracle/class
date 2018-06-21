/*
 *  Seat.c
 *
 *  Created on: 2015年6月12日
 *  Author: lc
 */
#include <stdlib.h>
#include "../Common/List.h"
#include "../Service/Seat.h"
#include "../Persistence/Seat_Persist.h"
//#include "EntityKey.h"

//添加新座位
int Seat_Srv_Add(const seat_t *data)
{	
	return Seat_Perst_Insert(data);
}

/*
int Seat_Srv_AddBatch(seat_list_t list){
	// 请补充完整
       return 0;
}
*/

//修改座位
int Seat_Srv_Modify(const seat_t *data)
{
    return Seat_Persist_Update(data);
}

//根据座位ID删除座位
int Seat_Srv_DeleteByID(int ID)
{
    return Seat_Srv_RemoveByID(ID);
}


//根据座位ID获取座位
int Seat_Srv_FetchByID(int ID, seat_t *buf)
{
	
    return Seat_Perst_FetchByID(ID,buf);
}


//根据演出厅ID删除所有座位
int Seat_Srv_DeleteAllByRoomID(int roomID)
{
	return Seat_Perst_RemoveAllByRoomID(roomID);
}

//根据演出厅ID获取所有座位
int Seat_Srv_FetchByRoomID(seat_list_t list, int roomID)
{
	//载入演出厅所有座位
	int SeatCount = Seat_Perst_SelectByRoomID(list,roomID);
	//对链表list进行排序
	Seat_Srv_Sort_SeatList(list);	
	return SeatCount;
}

/*根据演出厅ID提取有效的座位*/
int Seat_Srv_FetchValidByRoomID(seat_list_t list, int roomID)
{
	//载入演出厅所有座位，生成链表list
	int seatCount = Seat_Perst_SelectByRoomID(list,roomID);
	seat_list_t p;
	//对链表list进行遍历
	List_ForEach(list,p) {
		if(p->data.status != SEAT_GOOD) {
		//去除座位状态不是SEAT_GOOD的座位	
			List_DelNode(p)
			seatCount--;
		}
		Seat_Srv_SortSeatList(list);

	return 0;
}


//根据行、列数初始化演出厅的座位
int Seat_Srv_RoomInit(seat_list_t list, int roomID, int rowsCount,int colsCount) 
{
	seat_list_t newNode,p = list;
	seat_t seat_data;
	for(int i = 1;i <= rowsCount;i++)
		for(int j = 1;j <= colsCount;j++) {
			newNode = (seat_list_t)malloc(sizeof(seat_list_t));
			seat_data->row = i;
			seat_data->column = j;
			newNode->data = seat_data;
			//尾插法插入新结点
			List_AddTail(p,newNode)
			p = p->next;
		}
		//将座位信息载入文件
		if(Seat_Perst_InsertBatch(list))
			return 1;
	return 0;
}

//对座位链表list进行按座位行号和列号排序
void Seat_Srv_SortSeatList(seat_list_t list) 
{
	if(list == NULL)
		return;
	list->prev->next = NULL;
	seat_list_t listLeft = list->next;
	list->next = list->prev=list;	//将list置为空
	seat_list_t p;
	while(lestLeft != NULL) {
		p = listLeft;
		listLeft = listLeft->next;
		//将结点p加入到已排序链表list中去
		Seat_Srv_AddToSortedList(list,p);
	}
}

//将结点node加入到已排序链表list中
void Seat_Srv_AddToSoftedList(seat_list_t list, seat_node_t *node) 
{
	seat_list_t p = list->next;
	if(list == NULL)
		List_AddTail(list,node)
	else {
		while(p != list && p->data.row <= node->data.row || p->data.column <= node->data.column) 
			p = p->next;
		//将node插入到p结点之前
		List_InsertBefore(p,node)
	}
}
		
}

//根据行列号获取座位
seat_node_t * Seat_Srv_FindByRowCol(seat_list_t list, int row, int column)
{
    seat_list_t p;
	//对链表结点进行遍历
	List_ForEach(list,p) 
		if(p->data.row == row && p->data.column == column)
			return p;
	//若未找到，则返回空
    return NULL;
}


/*
inline seat_node_t * Seat_Srv_FindByID(seat_list_t list, int rowID) {
       // 请补充完整
       return NULL;
}
*/
