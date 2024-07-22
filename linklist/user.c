#include "user.h"
linklist node_cream()
{
	linklist node = (linklist) malloc (sizeof(linknode));
	printf("input:>");
B:
	fgets(node-> str,sizeof(node-> str),stdin);
	// 这里只能用 siezof()
	if(node-> str[0] != '\n')
	{
		node->str[strlen(node->str) -1] = '\0';
		node-> next =  NULL;
	}else{
		goto B;//  防止输入的是 \n   若果是 就  重新输入
	}
	return node;
}
// 在尾添加节点
void list_add_node(linklist h)
{ 
	linklist tmp = h;   
    get_list_end(tmp) -> next = node_cream();
	h->date ++; 
	fputs("add one node over!\n",stdout);
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
			fflush(stdout);
		}
       puts("\n");
	}

}
void  delete_end_node(linklist h)
{
	linklist tmp = h;
	if(h->date == -1 )
	{
		printf("Already! list is empty\n");
	// 	putchar();
	}else{
		while(tmp->next->next != NULL){
			tmp = tmp->next;
		}
		free(tmp->next->next);
		tmp->next = NULL;
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
			h->date++;
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
//  
void str_insert_node(linklist h)
{
    linklist node = node_cream();// 先生成一个节点保存要存的数据
	linklist tmp = h;
	if(h->date == -1 ){//  说明空链表直接在尾部插入
		list_add_node(tmp);
	}else{
		printf_list(tmp);
		fputs("输入你的插入位置\n",stdout);
		linklist t = node_cream();
		char * cur = t->str;
		linklist front_node = str_former_node(tmp,cur);
		node-> next = front_node-> next;
		front_node-> next = node;
		h-> date++;
	}
}
linklist str_former_node(linklist h,char* cur)//   查找插入位置的前节点
{// 返回   ->str = cur  的节点
	linklist tmp = h-> next;// 直接移动到一个数据的节点
	while(tmp)
	{
		int result = strncmp(tmp->str, cur, strlen(tmp-> str) < strlen(cur) ? strlen(tmp->str) :strlen(cur));
		if (result == 0) {
			return tmp;
		}else{
			tmp = tmp-> next;
		} 
	}
	fputs("插入位置错讹\n",stdout);
	return get_list_end(h);
}
//逆转  list
linklist reverse_list (linklist h)
{ 
	linklist tmp = NULL;  // 逆序链表的头指针，初始为空
    linklist current = h->next; // 遍历原链表的当前指针
    while (current != NULL) {
        linklist t = (linklist)malloc(sizeof(linknode)); // 创建一个新节点
       		if (t == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        strcpy(t->str,current->str); // 复制原链表节点的数据
        t->next = tmp;           // 将新节点插入逆序链表的头部
        tmp = t;
        current = current->next; // 移动到下一个原链表节点
    }
	linklist tmp2 = (linklist) malloc (sizeof(linknode));
	tmp2->date = h->date;
	tmp2->next = tmp;
    return tmp2; // 返回逆序链表的头指针
}
void delete_A_node(linklist h)
{
	linklist tmp  = h;
	if(h-> date == -1){
		fputs("list is NULL!\n",stdout);
		return;
	}
	printf_list(h);
	char cur[20] ="0";
	fputs("输入你要删除的节点：>",stdout);
	fgets(cur,sizeof(cur),stdin);
	cur[strlen(cur)-1] = '\0';
	while(tmp->next)
	{
		int result = strncmp(tmp->next->str, cur, strlen(tmp->next->str) );
		if (result == 0) {//若  tmp—>next ->str = cur  将tmp-> next 删除   
			linklist t =  tmp->next;
			tmp->next = tmp->next->next;
			t->next = NULL;
			free(t);
		}else{
			tmp = tmp-> next;
		} 

	}

	
}
