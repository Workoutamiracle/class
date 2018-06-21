#include "Sale_Persist.h"
#include "../Common/list.h"
#include "../Service/Sale.h"
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>
#include "EntityKey_Persist.h"


static const char SALE_DATA_FILE[] = "Sale.dat";
static const char SALE_DATA_TEMP_FILE[] = "SaleTmp.dat";

//存储新订单
int Sale_Perst_Insert (sale_t *data){
	return 0;
}

//更新票状态
int Ticket_Perst_Update (const ticket_t *data){
	return 0;
}

//根据演出计划ID载入票的数据
int Ticket_Srv_SelBySchID(int id, ticket_list_t list){
	return 0;
}

//根据票ID载入销售记录
int Sale_Perst_SelByTicketID (int ticket_id, sale_t *sale){
	return 0;
}

//根据ID载入销售记录
int Sale_Perst_SelByID (sale_list_t list, int usrID){
	return 0;

}
