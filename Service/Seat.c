/*
 *  Seat.c
 *
 *  Created on: 2015��6��12��
 *  Author: lc
 */
#include <stdlib.h>
#include "../Common/List.h"
#include "Seat.h"
//#include "../Persistence/Seat_Persist.h"
//#include "EntityKey.h"

inline int Seat_Srv_Add(const seat_t *data){
	// �벹������
       return 0;
}

inline int Seat_Srv_AddBatch(seat_list_t list){
	// �벹������
       return 0;
}

inline int Seat_Srv_Modify(const seat_t *data){
	// �벹������
       return 0;
}

inline int Seat_Srv_DeleteByID(int ID){
	// �벹������
       return 1;
}

inline int Seat_Srv_FetchByID(int ID, seat_t *buf){
	// �벹������
       return 0;
}

inline int Seat_Srv_DeleteAllByRoomID(int roomID){
	// �벹������
       return 0;
}

//�����ݳ���ID������λ
int Seat_Srv_FetchByRoomID(seat_list_t list, int roomID){
       // �벹������
       return 0;
}

/*���ݷ�ӳ��ID��ȡ��Ч����λ*/
int Seat_Srv_FetchValidByRoomID(seat_list_t list, int roomID)
{
       // �벹������
       return 0;
}


//�����С�������ʼ���ݳ�������λ
int Seat_Srv_RoomInit(seat_list_t list, int roomID, int rowsCount,
		int colsCount) {
	// �벹������
       return 0;
}

//����λ����list���а���λ�кź��к�����
void Seat_Srv_SortSeatList(seat_list_t list) {
       // �벹������
}

//�����node���뵽����������list��
void Seat_Srv_AddToSoftedList(seat_list_t list, seat_node_t *node) {
       // �벹������
}

inline seat_node_t * Seat_Srv_FindByRowCol(seat_list_t list, int row, int column) {
       // �벹������
       return NULL;
}


inline seat_node_t * Seat_Srv_FindByID(seat_list_t list, int rowID) {
       // �벹������
       return NULL;
}
