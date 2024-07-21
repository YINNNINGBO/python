#include "user.h"
linklist node_cream()
{
	
	linklist node = (linklist) malloc (sizeof(linknode));
	printf("输入要存入的数据:>");
	fgets(node-> str,sizeof(node-> str),stdin);
	fputs("node_ream\n",stdout);
	//fputs(node->str,stdout);
	node->str[strlen(node->str) -1] = '\0';
	node-> next =  NULL;
	return node;
}
// 在尾添加节点
void list_add_node(linklist h)
{ 
	linklist tmp = h;   
    get_list_end(tmp) -> next = node_cream();
	h -> date ++; 
	fputs("add one node over!\n",stdout);
	//fputs(node_cream()->  str,stdout);
}
//b 遍历到链表尾  返回指针
linklist get_list_end(linklist h)
{
	linklist tmp = h;
	if( h -> date == -1)
	{	
		return h;
	}else{
		while (tmp ->next)
		{
			tmp = tmp ->next;
		}
		return tmp;  // tmp ->next is NULL so ret
	}
}
void printf_list(linklist h)
{
	linklist tmp = h;
	if(h-> date == -1 ){
		fputs("list is empty!",stdout);
		exit(0);
	}else{
		tmp = tmp->next;
		fputs("list is: ",stdout);
		while(tmp != NULL)
		{
			fputs(tmp->str,stdout);
			fputs("->",stdout);
			tmp = tmp-> next;
		}fputs("\n",stdout);
	
	}

}
void  delete_end_node(linklist h)
{
	linklist tmp = h;
	if(!tmp -> next )
	{
		printf("Already! list is empty\n");
	// 	putchar();
	}else{
		while(tmp ->next->next )
		{
			tmp = tmp -> next;
		}
		tmp->next = NULL;
		h -> date--;
		printf("now ,finish delete end node!");
	}
}
// 按索引插入节点
void int_insert_node(linklist h,int i)
{
	linklist tmp  = h;
	if(tmp -> date == -1){
		fputs("list is NULL!",stdout);
		exit(1);
	}
	
	if(i>= 0 && i <= h-> date  ) //i  的范围正确时
	{
		fputs("now begin insert node\n",stdout);
	 //	char str1[20] ={0};
		linklist node1 = node_cream();
		if(int_former_node(tmp,i)-> next) // 前节点的下一个节点是不为空
		{
			
			node1-> next = int_former_node(tmp,i)->next;
			int_former_node(tmp,i)-> next =  node1 ;
		}else{//前节点的下一个节点 为 NULL 相当于添加节点
			list_add_node(tmp);
		}

	}else{//  i 的范围错误时
		fputs("i is error !",stdout);
	}

}

linklist int_former_node(linklist h, int i)
{
	linklist tmp = h;
	if(i == 0){
		return tmp;
	}else if (i ==((h-> date)+1)){
		return get_list_end(tmp);
	}else{
		for(int t = 0;t < i;t++)
		{
			tmp = tmp-> next;
		}
		return tmp;
	}
}

