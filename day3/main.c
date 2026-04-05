/*
 * @file   day3/mian.c
 * @auter   YinNingBo
 * @date    2026-4-5
 * @system  linux -C
 * @description  循环链表（没有头节点）。
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node
{
	int data;
	struct node *next;
} Node, *link_list;

typedef struct
{
	int length;
	link_list head;
	link_list tail;
} List, *round_link_list;

/* 判断是否为NULL；a: 调试信息*/
#define DEBUG_NULL_PTR(a)                                                            \
	do                                                                               \
	{                                                                                \
		if (!a)                                                                      \
		{                                                                            \
			printf("func:%s ;line:%d, failed ,This is  NULL\n", __func__, __LINE__); \
			return NULL;                                                             \
		}                                                                            \
	} while (0)
#define DEBUG_NULL_INT(a)                                                            \
	do                                                                               \
	{                                                                                \
		if (!a)                                                                      \
		{                                                                            \
			printf("func:%s ;line:%d, failed ,This is  NULL\n", __func__, __LINE__); \
			return -1;                                                               \
		}                                                                            \
	} while (0)

/**
 * @brief  创建头节点   （当只有一个节点时，头就是尾）
 * @param  f_data : 指向头节点Note->data
 * @retval 成功：返回值指针，失败：返回NULL
 */
round_link_list create_list(int f_data)
{
	// 1. 创建循环链表
	round_link_list round_list = (round_link_list)malloc(sizeof(List));
	DEBUG_NULL_PTR(round_list);
	// 2. 初始化循环链表
	round_list->length = 1;
	round_list->head = (link_list)malloc(sizeof(Node));
	DEBUG_NULL_PTR(round_list->head);
	round_list->head->data = f_data;
	round_list->head->next = round_list->head;
	round_list->tail = round_list->head;
	return round_list;
}

/**
 * @brief  追加节点  (追加尾节点，不再需要遍历到结尾因为有tail指针)
 * @param  L: 循环链表首节点 指针
 * @param  f_data: 追加节点数据
 * @retval 返回值添加数据的节点指针
 */
round_link_list append_node(round_link_list *RL, int f_data)
{
	// 1. 判断参数
	DEBUG_NULL_PTR(*RL);
	link_list head = (*RL)->head;
	// 2. 创建新节点
	link_list new_node = (link_list)malloc(sizeof(Node));
	DEBUG_NULL_PTR(new_node);
	new_node->data = f_data;
	// 3. 将新节点追加到链表尾部
	(*RL)->tail->next = new_node;
	new_node->next = head;
	// 4. 更新链表尾指针和长度
	(*RL)->tail = new_node;
	(*RL)->length++;
	return *RL;
}

/**
 * @brief  插入节点
 * @param  L: 循环链表首节点 指针
 * @param  f_index: 插入位置的索引
 * @param  f_data: 插入节点的数据
 * @retval 成功：返回值插入数据的节点指针，失败：返回 NULL
 */
round_link_list insert_node(round_link_list *RL, int f_index, int f_data)
{
	// 1. 判断参数
	DEBUG_NULL_PTR(*RL);
	if ((f_index < 0) && (f_index >= (*RL)->length))
	{
		printf("func:%s ;line:%d, failed ,This is  index out of range\n", __func__, __LINE__);
		return NULL;
	}
	// 2. 创建新节点
	link_list new_node = (link_list)malloc(sizeof(Node));
	DEBUG_NULL_PTR(new_node);
	new_node->data = f_data;
	// 3. 插入节点
	// 3.1 插入位置为0
	if (f_index == 0)
	{
		new_node->next = (*RL)->head;
		(*RL)->head = new_node;
	}

	// 3.2 插入位置不为0,找到要插入的前一个节点
	link_list p = (*RL)->head;
	for (int i = 0; i < f_index - 1; i++)
	{
		p = p->next;
	}
	new_node->next = p->next;
	p->next = new_node;
	// 4. 更新链表长度
	(*RL)->length++;
	return *RL;
}

/**
 * @brief  通过Note->data查找节点
 * @param  L: 循环链表首节点 指针
 * @param  f_data: 要查找的数据
 * @retval 成功：返回值查找结果的节点指针，失败：返回 NULL
 */
link_list find_node_use_data(round_link_list *RL, int f_data)
{
	// 1. 判断参数
	DEBUG_NULL_PTR(*RL);
	// 2. 查找遍历节点
	link_list head = (*RL)->head;
	link_list p = head;
	do
	{
		// 找到就return p
		if (p->data == f_data)
		{
			return p;
		}
		// 没有找到就继续遍历
		p = p->next;
	} while (p->next != head);
	// 2.1 没有找到 list 中有该数值
	// 程序执行到这里 说明 round_list 中没有该数值
	return NULL;
}

/**
 * @brief  通过节点的索引查找节点
 * @param  L: 首节点指针
 * @param  f_index:索引
 * @retval 成功返回节点，失败返回 NULL
 */
link_list find_node_use_index(round_link_list *RL, int f_index)
{
	// 1. 判断参数 长度和NULL
	DEBUG_NULL_PTR(*RL);
	if ((f_index < 0) && (f_index >= (*RL)->length))
	{
		printf("func:%s ;line:%d, failed ,This is  index out of range\n", __func__, __LINE__);
		return NULL;
	}
	// 2. 查找节点
	// 2.1 f_index = 0 直接返回头节点
	if (f_index == 0)
	{
		return (*RL)->head;
	}
	// 2.2 f_index > 0 遍历节点
	link_list head = (*RL)->head;
	link_list p = head;
	int i = 0;
	for (i = 0; i < f_index; i++)
	{
		p = p->next;
	}
	if (i == f_index)
	{
		return p->next;
	}
}

/**
 * @brief  根据node->data 删除节点
 * @param  L:首节点
 * @param  f_data: node->data
 * @retval 成功：返回node->data，失败：返回 -1
 */
int delete_node_use_data(round_link_list *RL, int f_data)
{
	// 1. 判断参数
	DEBUG_NULL_INT(*RL);
	// 2. 查找节点
	// 2.1 head->data == f_data 删除头节点
	link_list head = (*RL)->head;
	if (head->data == f_data)
	{
		// 删除头节点
		(*RL)->head = head->next;
		(*RL)->tail->next = (*RL)->head->next; // 更新尾节点的next指针
		(*RL)->length--;
		int del_data = head->data;
		free(head);
		head = NULL;
		return del_data;
	}
	// 2.2 遍历round_list 找到要删除的节点
	link_list p = head->next; // 这里直接从 第二个开始
	while (p->next != (*RL)->head->next)
	{
		// 判断节点
		if (p->next->data == f_data)
		{
			// 删除节点
			link_list del_node = p->next;
			p->next = del_node->next;
			int del_data = del_node->data;
			free(del_node);
			del_node = NULL;
			(*RL)->length--;
			return del_data;
		}
		p = p->next;
	}
	printf("failed ,This is  data not found %d\n", f_data);
	return -1;
}

/**
 * @brief  根据索引删除节点
 * @param  L:首节点
 * @param  f_index: 索引值
 * @retval 成功：return 删除节点的node->data，失败：返回 -1
 */
int delete_node_use_index(round_link_list *RL, int f_index)
{
	// 1. 判断参数 长度和NULL
	DEBUG_NULL_INT(*RL);
	if (0 > f_index && f_index >= (*RL)->length)
	{
		printf("func:%s ;line:%d, failed ,This is  index out of range\n", __func__, __LINE__);
		return -1;
	}
	// 2. 查找节点
	// 2.1 f_index = 0 删除头节点
	if (0 == f_index)
	{
		link_list del_node = (*RL)->head;
		(*RL)->head = del_node->next;
		(*RL)->tail->next = (*RL)->head; // 更新尾节点的next指针
		(*RL)->length--;
		int del_data = del_node->data;
		free(del_node);
		del_node = NULL;
		return del_data;
	}
	// 2.2 f_index > 0 遍历节点找到要删除的节点
	link_list p = (*RL)->head;
	for (int i = 0; i < f_index - 1; i++)
	{
		p = p->next;
	}
	// 判断 要删除的是不是尾节点
	if (p->next == (*RL)->tail)
	{
		// 删除尾节点
		link_list del_node = p->next;
		p->next = del_node->next;
		(*RL)->tail = p; // 更新尾节点指针
		(*RL)->length--;
		int del_data = del_node->data;
		free(del_node);
		del_node = NULL;
		return del_data;
	}
	// 删除其他节点
	link_list del_node = p->next;
	p->next = del_node->next;
	(*RL)->length--;
	int del_data = del_node->data;
	free(del_node);
	del_node = NULL;
	return del_data;
}

/**
 * @brief  删除整个链表
 * @param  L；首节点
 * @retval 成功：return 1 ；失败：return -1
 */
int delete_round_list(round_link_list *RL)
{
	// 1. 判断参数
	DEBUG_NULL_INT(*RL);
	// 2. 删除节点
	link_list del_node = (*RL)->head;
	while ((*RL)->length > 0)
	{

		link_list next_node = del_node->next;
		free(del_node);
		del_node = NULL;
		if (next_node)
		{
			del_node = next_node;
		}
		(*RL)->length--;
	}
	// 3. 删除RL
	free(*RL); // RL 是二级指针这里free(*RL) 正确
	(*RL) = NULL;
	return 1;
}

/**
 * @brief  获取链表长度
 * @param  L: 首节点
 * @retval 成功：return 链表长度；失败：return -1
 */
int get_list_length(link_list *L)
{
	//  1. 判断参数
	DEBUG_NULL_INT(*L);

	link_list head = *L;
	link_list p = head;
	int len = 0;

	do
	{
		len++;
		p = p->next;
	} while (p != head);

	return len;
}

int printf_list(round_link_list *RL)
{
	// 1. 判断参数
	DEBUG_NULL_INT(*RL);
	link_list head = (*RL)->head;
	link_list p = head;
	do
	{
		printf("%d ", p->data);
		p = p->next;
	} while (p != (*RL)->head);
	printf("\n");
	return 1;
}

int main(int argc, const char *argv[])
{
	// 1. 创建循环链表
	round_link_list round_list = create_list(1);
	// 2. 追加节点
	srandom((unsigned int)time(NULL));
	for (int i = 0; i < 10; i++)
	{
		append_node(&round_list, random() % 100);
	}
	printf_list(&round_list);
	// 插入节点
	insert_node(&round_list, 5, 999);
	printf_list(&round_list);
	insert_node(&round_list, 14, 888);
	// 3. 查找节点
	link_list find_node = find_node_use_data(&round_list, 999);
	if (find_node && find_node->data == 999)
	{
		printf("find_node_use_data success\n");
	}
	else
	{
		printf("find_node_use_data failed\n");
	}
	find_node = find_node_use_index(&round_list, 5);
	printf("find_node_use_index No5: %d\n", find_node->data);
	printf_list(&round_list);
	// 4. 删除节点
	int del_data = delete_node_use_data(&round_list, 999);
	if (del_data == 999)
	{
		printf("delete_node_use_data %d :success\n", del_data);
	}
	else
	{
		printf("delete_node_use_data failed, data = %d\n", del_data);
	}
	delete_node_use_data(&round_list, -1); // 这里应该是提示找不到
	printf_list(&round_list);
	del_data = delete_node_use_index(&round_list, 5);
	printf("delete_node_use_index 5 : %d\n", del_data);
	printf_list(&round_list);
	// 5. 获取链表长度
	int list_length = get_list_length(&round_list->head);
	if (list_length == round_list->length)
	{
		printf("get_list_length success\n");
	}
	else
	{
		printf("get_list_length failed\n");
	}
	// 5. 删除整个链表
	int del_list = delete_round_list(&round_list);
	return 0;
}
