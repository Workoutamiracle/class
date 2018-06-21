#include"../View/Seat_UI.h"
#include"../Service/Seat.h"
#include"../Common/List.h"
#include"../Service/Studio.h"
#include<studio.h>
//管理座位界面
void Seat_UI_MgtEntry(int roomID)
{
	//定义演出厅数据结点
	studio_t studio_data;
	int rows,cols;
	//定义座位链表头结点，临时结点
	seat_list_t list,temp;
	if(Studio_Srv_FetchByID(roomID,&studio_data)) {//获取对应演出厅信息
		//若演出厅存在，获取演出厅所有座位信息
		//若座位存在，则循环输出座位信息
		int num = Seat_Srv_FetchByRoomID(list,roomID);
		if(num) {
			List_ForEach(list,temp) {
			printf("id:%d roomID:%d row:%d column:%d status:%d\n",temp->data.id,temp->data.roomID,temp->data.row,temp->data.column,temp->data.status);
			}
			char choice;
			printf("[a]:add a seat [U]:change a seat [d]:delete a seat [r]return last");
			while(scanf("%c",&choice) == 1 && choice != 'r') {
				switch(choice) {
					case 'a':
					case 'A'://添加一个新座位
						printf("input it's rows and cols:")
						scnaf("%d %d",&rows,&cols);
						Seat_UI_Add(list,roomID,rows,cols);
						studio_data.seatsCount++;
						break;
					case 'u':
					case 'U'://修改一个座位
						printf("input the seat's rows and cols that you want to change");
						scanf("%d %d",&rows,&cols);
						Seat_UI_Modify(list,rows,cols);
						break;
					case 'd':
					case 'D'://删除一个座位
						printf("input the seat's rows and cols that you want to delete:"):
						scanf("%d %d",&rows,&cols);
						Seat_UI_Delete(list,rows,cols);
						studio_data.seatsCount--;
						break;
				}
				Studio_Srv_Modify(&studio_data);
				printf("[a]:add a seat [U]:change a seat [d]:delete a seat [r]return last");
			}
		}

		else {//若座位不存在，则初始化座位信息，并更新演出厅数据
			printf("seat is not live,please input it's rows and cols");
			scanf("%d %d",&rows,&cols);
			//初始化座位信息
			Seat_Srv_RoomInit(list,roomID,rows,cols);
			studio_data.rowsCount = rows;
			studio_data.colsCount = cols;
			studio_data.seatsCount = num;
			//更新演出厅信息
			Studio_Srv_Modify(&studio_data);
		}
	}
	else	
`		return;
}

//根据座位状态获取界面显示状态符号界面
char Seat_UI_Status2Char(seat_status_t status)
{
	switch(statuc){
		case SEAT_GOOD:
			return '#';
		case SEAT_BROKEN:
			return '-';
		case SEAT_NONE:
			return ' ';
	}
}

//根据输入符号获取座位状态界面
seat_status_t Seat_UI_Char2Status(char statusChar)
{
	switch(statusChar) {
		case '#':
			return SEAT_GOOD;
		case '-':
			return SEAT_BROKEN;
		case ' ':
			return SEAT_NODE;
	}
}

//修改座位界面
int Seat_UI_Modify(seat_list_t list,int rowsCount,int colsCount)
{
	int rtn = 0; //成功修改座位的标志置0
	//根据行列号找到座位所在链表结点
	seat_node_t *temp = Seat_Srv_FindByRowCol(list,rowsCount,colsCount);
	if(temp == NULL) {
		printf("the seat is not find");
		return rtn;
	}
	//将座位链表结点数据信息更新
	seat_t data = temp->data;
	if(Seat_Srv_Modify(&data))
		rtn = 1;
	else
		printf("change the seat is failed");
	return rtn;
}

//删除座位界面
int Seat_UI_Delete(seat_list_t list,int rowsCount,int colsCount)
{
	int found = 0;//成功删除座位的标志置0
	//根据行列号找到座位所在链表结点
	seat_node_t *temp = Seat_Srv_FindByRowCol(list,rowsCount,colsCount);
	if(temp == NULL) {
		printf("the seat is no find");
		return found;
	}
	//将座位链表结点数据信息更新
	seat_t data = temp->data;
	if(Seat_Srv_DeleteByID(data.id))	//根据座位ID删除座位
		found = 1;
	else
		printf("delete the seat is failed");
	return found;
}

//添加新座位界面
int Seat_UI_Add(seat_list_t list,int roomID,int rowsCount,int colsCount)
{
	newCount = 0;	//添加座位计数
	seat_t data;
	data->row = rowsCount;
	data->column = colsCount;
	char choice;
	while(1) {
		if(Seat_Srv_FindByRowCol(list,rowsCount,colsCount)) {
			printf("the seat is live");
			continue;
		}
		else {
			//设置座位的演出厅ID和状态
			printf("输入座位的演出厅ID和状态:");
			scanf("%d %d",&data->roomID,&data->status);
			while(getchar() != '\n')
				continue;
			//添加座位
			if(Seat_Srv_Add(&data)) {
				newCount++;
				printf("add the seat is successful\n");
			}
			else
				printf("add the seat is failed");
			printf("input your choice to go on:");
			scanf("%c",&choice;);
			if(choice != 'a' || choice != 'A')
				break;
	}
	return newCount;
}


			
		

















