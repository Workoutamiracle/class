#ifndef SCHEDULE_H_
#define SCHEDULE_H_

#include "../Common/Common.h"

typedef struct {
	int id;
	int play_id;
	int studio_id;
	ttms_date_t date;
	ttms_time_t time;
	int seat_count;
}schedule_t;

//双向链表
typedef struct schedule_node {
	schedule_t data;
	struct schedule_node *next, *prev;
} schedule_node_t, *schedule_list_t;

 int Schedule_Srv_Add(schedule_t *data);

 int Schedule_Srv_Modify( schedule_t *data);

 int Schedule_Srv_DeleteByID(int ID);

 int Schedule_Srv_FetchByID(int ID, schedule_t *buf);

 int Schedule_Srv_FetchAll(schedule_list_t list);

 int Schedule_Srv_FetchByPlay(schedule_list_t list,int play_id);
 
//根据剧目ID获取票房
int Schedule_Srv_StatRevByPlay(int play_id, int *soldCount);

//根据演出ID，统计上座率及票房，返回票房数收入
//int Schedule_Srv_StatRevByPlay(int play_id, int *soldCount, int *totalCount);


#endif //SCHEDULE_H_
