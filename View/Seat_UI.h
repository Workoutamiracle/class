#ifndef Seat_UI_H_
#define Seat_UI_H
/*座位管理界面层函数头文件 */
//座位状态类型定义
//类型标识：TTMS_SDS_Seat_Status
//类型名称：seat_status_t
//类型定义:
typedef enum{
	SEAT_NONE = 0,		//空位
	SEAT_GOOD = 1,		//有座位
	SEAT_BROKEN = 9		//损坏的座位
}seat_status_t;

//座位实体数据类型定义
//类型标识：TTMS_SDS_Seat_Ent
//类型名称：seat_t
//类型定义：
typedef struct{
	int id;				//座位ID
	int roomID;			//所在演出厅ID
	int row;			//座位行号
	int column;			//座位列号
	seat_status_t status;	//座位在此行的状态
}seat_t;

//座位链表结点定义
//类型标识：TTMS_SDS_Seat_ListNode
//类型名称：seat_node_t,seat_list_t
//类型定义：
typedef struct seat_node{
	seat_t data;
	struct seat_node *next;
	struct seat_node *prev;
}seat_node_t,*seat_list_t;

//管理座位界面
void Seat_UI_MgtEntry(int roomID);
//根据座位状态获取界面显示状态符号界面
char Seat_UI_Status2Char(seat_status_t status);
//根据输入符号获取座位状态界面
seat_status_t Seat_UI_Char2Status(char statusChar);
//修改座位界面
int Seat_UI_Modify(seat_list_t list,int rowsCount,int colsCount);
//删除座位界面
int Seat_UI_Delete(seat_list_t list,int rowsCount,int colsCount);
//添加新座位界面
int Seat_UI_Add(seat_list_t list,int roomID,int rowsCount,int colsCount);
#endif









