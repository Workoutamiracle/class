/*
 *  Seat.c
 *
 *  Created on: 2015年6月12日
 *  Author: lc
 */
#include <stdlib.h>
#include "../Common/List.h"
#include "Seat.h"
//#include "../Persistence/Seat_Persist.h"
//#include "EntityKey.h"

inline int Seat_Srv_Add(const seat_t *data){
	// 请补充完整
       return 0;
}

inline int Seat_Srv_AddBatch(seat_list_t list){
	// 请补充完整
       return 0;
}

inline int Seat_Srv_Modify(const seat_t *data){
	// 请补充完整
       return 0;
}

inline int Seat_Srv_DeleteByID(int ID){
	// 请补充完整
       return 1;
}

inline int Seat_Srv_FetchByID(int ID, seat_t *buf){
	// 请补充完整
       return 0;
}

inline int Seat_Srv_DeleteAllByRoomID(int roomID){
	// 请补充完整
       return 0;
}

//根据演出厅ID载入座位
int Seat_Srv_FetchByRoomID(seat_list_t list, int roomID){
       // 请补充完整
       return 0;
}

/*根据放映厅ID提取有效的座位*/
int Seat_Srv_FetchValidByRoomID(seat_list_t list, int roomID)
{
       // 请补充完整
       return 0;
}


//根据行、列数初始化演出厅的座位
int Seat_Srv_RoomInit(seat_list_t list, int roomID, int rowsCount,
		int colsCount) {
	// 请补充完整
       return 0;
}

//对座位链表list进行按座位行号和列号排序
void Seat_Srv_SortSeatList(seat_list_t list) {
       // 请补充完整
}

//将结点node加入到已排序链表list中
void Seat_Srv_AddToSoftedList(seat_list_t list, seat_node_t *node) {
       // 请补充完整
}

inline seat_node_t * Seat_Srv_FindByRowCol(seat_list_t list, int row, int column) {
       // 请补充完整
       return NULL;
}


inline seat_node_t * Seat_Srv_FindByID(seat_list_t list, int rowID) {
       // 请补充完整
       return NULL;
}
