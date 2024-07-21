#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef  int date_t;


typedef struct node{
	date_t date;   //记录长度
	char str[20];    // 数据
	struct node* next;
}linknode,*linklist;
//创建一个 新节点  但是不添加
linklist node_cream();
//  删除节点
void  delete_end_node(linklist );
// 返回尾节点   用于在结尾插入节点
linklist get_list_end(linklist );
//在结尾添加节点
void list_add_node(linklist);
//链表打印
void printf_list( linklist );
 //用索引的方式 插入节点
void int_insert_node(linklist, int);
//找到索引的前节点 并返回
linklist int_former_node(linklist, int);
//用数据的方式拆插入节点
void str_insert_node(linklist ); //  这里先打印以下 list
//用数据的方式找到前节点 并返回
linklist  str_former_node(linklist,  char*);
//逆序链表 并返回
linklist  reverse_list(linklist);
