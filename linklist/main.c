#include "user.h"

int main(int argc,const char * argv[])
{
// 初始化
   // char buf[20] ={0};
	linklist list = (linklist)malloc (sizeof(linknode));
	list-> date = -1;  
	list -> next = NULL;
	fputs("000\n",stdout);
 	list_add_node(list);
	fputs("000\n",stdout);

	printf_list(list);
	printf("111\n");
	list_add_node(list);
	printf_list(list);
	list_add_node(list);
	printf_list(list);

	int_insert_node(list ,1);
	printf_list(list);
//	printf("3\n ");
	delete_end_node(list);
//	printf("4 \n");
	return  0;
}
