/*
 不带虚拟节点的 顺序单链表：
name: YinNingBo
date: 2026-4-3
file: day2/main.c

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node
{
	int data;
	struct node *next;
} Node, *link_list;

//  宏函数 用于判断是否为NULL,
// a 是要判断的指针， b是指定返回的标志的数据类型

#define DEBUG_NULL(a, b)                                                           \
	do                                                                             \
	{                                                                              \
		if (!a)                                                                    \
		{                                                                          \
			printf("func:%s ;line:%d, failed ,This is  NULL", __func__, __LINE__); \
			if (b == 1)                                                            \
			{                                                                      \
				return NULL;                                                       \
			}                                                                      \
			else                                                                   \
			{                                                                      \
				return -1;                                                         \
			}                                                                      \
		}                                                                          \
	} while (0)

/**
 * 创建一个节点为头节点
 */
link_list create_link(int f_data)
{
	link_list L = (link_list)malloc(sizeof(Node));
	DEBUG_NULL(L, 1);
	L->data = f_data;
	L->next = NULL;
	return L;
}

link_list append_node(link_list *L, int f_data)
{
	DEBUG_NULL(*L, 1);
	link_list p = *L;
	while (p->next)
	{
		p = p->next;
	}
	link_list new_node = (link_list)malloc(sizeof(Node));
	DEBUG_NULL(new_node, 1);
	new_node->data = f_data;
	new_node->next = NULL;
	p->next = new_node;
	return new_node;
}

/**
 * @brief  获取list的长度
 * @param  L： list
 * @retval 返回list的长度 -1 表示错误，>= 0 表示长度
 */
int get_list_len(link_list *L)
{
	DEBUG_NULL(*L, -1);
	link_list p = *L;
	int re_len = 0;
	while (p)
	{
		re_len++;
		p = p->next;
	}
	return re_len + 1;
}

link_list insert_node(link_list *L, int f_data, int f_index)
{
	link_list p = *L;
	// 1.检验参数
	DEBUG_NULL(*L, 1);
	// 2.创建新节点
	link_list new_node = (link_list)malloc(sizeof(Node));
	DEBUG_NULL(new_node, 1);
	new_node->data = f_data;
	// 判断索引位置
	if (f_index <= 0)
	{
		new_node->next = p;
		*L = new_node;
		return new_node;
	}
	else if (f_index > (get_list_len(L) - 1))
	{
		// index in [list_len , +inf)  遍历到最后一个
		while (p->next)
		{
			p = p->next;
		}
		p->next = new_node;
		new_node->next = NULL;
		return new_node;
	}
	else
	{
		// index in (0 ,list_len]
		for (int i = 0; i < f_index - 1; i++)
		{
			p = p->next;
		}
		new_node->next = p->next;
		p->next = new_node;
		return new_node;
	}
}

/*
 * @brief  根据参数中的索引获取node->data
 * @param  L : 链
 * @param  f_index:  索引
 * @retval  : -1 表示错误，>=0 表示node->data
 */
int get_data(link_list *L, int f_index)
{
	// 1. 判断参数
	DEBUG_NULL(*L, -1);
	link_list p = *L;
	f_index = f_index < 0 ? 0 : f_index;
	f_index = f_index > (get_list_len(L) - 1) ? (get_list_len(L) - 1) : f_index;
	// 2. 遍历到指定索引位置
	for (int i = 0; i < f_index - 1; i++)
	{
		p = p->next;
	}
	return p->data;
}

/*
 * @brief  删除list 中  ->data = f_data
 * @param  L : 链
 * @param  f_data:  要删除的数据
 * @retval -1 : 表示失败，没有该数值 0 : 表示成功删除
 */
int delete_node_use_data(link_list *L, int f_data)
{
	// 1. 判断参数
	DEBUG_NULL(*L, -1);
	link_list p = *L;
	link_list next_node = p->next;
	while (next_node)
	{
		// 若找到数值
		if (next_node->data == f_data)
		{
			p->next = next_node->next;
			free(next_node);
			return 0;
		}
		else
		{
			// 没有找到
			p = next_node;
			next_node = next_node->next;
		}
	}
	// 循环中没有找到 说明没有该数据
	printf("没有找到要删除的数值%d\n", f_data);
	return -1;
}

/*
 * @brief  删除list 中  ->index = f_index
 * @param  L : 链
 * @param  f_index:  要删除的索引
 * @retval -1 : 表示失败，没有该索引 ;>=0 : 返回成功并且返回node->data
 */
int delete_node_use_index(link_list *L, int f_index)
{
	link_list p = *L;
	// 1. 参数判断
	DEBUG_NULL(*L, -1);
	if ((f_index < 0) || (f_index >= get_list_len(L)))
	{
		return -1;
	};
	// 2. 遍历到指定索引位置
	for (int i = 0; i < f_index - 1; i++)
	{
		p = p->next;
	}
	// 3. 删除节点
	int tmp = p->next->data;
	link_list del_node = p->next;
	p->next = del_node->next;
	free(del_node);
	return tmp;
}

void delete_list(link_list *L)
{
	// 1. 判断参数
	if (!*L)
	{
		printf("func:%s ;line:%d, failed ,This is  NULL", __func__, __LINE__);
	}
	link_list p = (*L);
	while (p)
	{
		link_list del_p = p;
		p = p->next;
		free(del_p);
	}
}

/*  打印 list*/
void DEBUG_print_list(link_list *L)
{
	if (!(*L))
	{
		printf("func:%s ;line:%d, failed ,This is  NULL", __func__, __LINE__);
	}
	link_list p = *L;
	while (p)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

int main(int argc, const char *argv[])
{
	// 1.创建 list
	link_list L = create_link(1);
	// 2.追加 node
	srandom((int)time(NULL));
	for (int i = 0; i < 10; i++)
	{
		append_node(&L, random() % 100);
	}
	DEBUG_print_list(&L);
	// 3. 插入node
	if (!insert_node(&L, 100, 3))
	{
		printf("insert_node :插入失败\n");
	}
	DEBUG_print_list(&L);
	// 4. 通过data 删除node
	printf("delete 100 \n");
	delete_node_use_data(&L, 100);

	DEBUG_print_list(&L);
	// 5. 输入index  ，通过index 删除node
	delete_node_use_index(&L, 3);
	DEBUG_print_list(&L);
	// 6. 删除list
	delete_list(&L);
	return 0;
}
