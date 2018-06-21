#include"../Persistence"
#include"../View/Seat_UI.h"
#include"../Commom/EntityKey_Persist.h"
#include<stdio.h>

const char SEAT_DATA_FILE[] = "Seat.dat";
const char SEAT_DATA_TEMP_FILE[] = "Seattemp.dat";

//添加对象主键标识名称
const char SEAT_KEY_NAME[] = "Seat";


//向文件中存储新的座位数据
int Seat_Perst_Insert(seat_t *data)
{
	int rtn = 0; //成功添加演出厅标志置0
	//为新座位数据分配主键
	int key = EntKey_Perst_GetNewKeys(SEAT_KEY_NAME,1)
	if(key) {
		data->id = key;
		FILE *fp = fopen(SEAT_DATA_FILE,"ab");
		if(fp == NULL) {
			printf("open the file is failed"):
			return 0;
		}
		fwrite(data,1,sizeof(seat_t),fp);
		rtn = 1;
	}
	return rtn;
}

//向文件中批量存储座位
int Seat_Perst_InsertBatch(seat_list_t list)
{
	//遍历座位链表，统计批量存入的座位个数
	seat_list_t p;
	int len;
	List_ForEach(list,p) {
		p->data->id = EntKey_Perst_GetNewKeys(SEAT_KEY_NAME,1);


	







