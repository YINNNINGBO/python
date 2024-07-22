#include "user.h"

int main(int argc,const char * argv[])
{
// 初始化
   // char buf[20] ={0};
	linklist list = (linklist)malloc (sizeof(linknode));
	list-> date = -1;
	list -> next = NULL;
 	list_add_node(list);
//	printf_list(list);
	list_add_node(list);
//	printf_list(list);
	list_add_node(list);
	printf("正向list->date :%d\n",list->date);
	printf_list(list);
	fputs("增加节点完成\n",stdout);
	int_insert_node(list ,1);
	printf_list(list);
	printf("正向list->date :%d\n",list->date);
	fputs("索引：插入节点完成\n",stdout);
	str_insert_node(list);
	printf_list(list);
	printf("正向list->date :%d\n",list->date);
  	fputs("数据：插入节点完成\n",stdout);
	fputs("打印逆转链表\n",stdout);
	linklist t =  reverse_list(list);
	printf_list(t);
	printf("逆向list -> date:%d\n",t->date);
	printf("逆向操作后正向list->date:%d\n",list->date);
	delete_end_node(list);
	printf_list(list);
	fputs("删除尾节点完成",stdout);
	delete_A_node(list);
	printf_list(list);

	return  0;
}
