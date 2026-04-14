#ifndef USER_H__
#define USER_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#if 0
uint32_t add(uint32_t a, uint32_t b);
#endif // endif 0

// 调试宏 用于return *P 的函数
#define DEBUG_R_NULL(a)                                                      \
    do                                                                       \
    {                                                                        \
        if (!a)                                                              \
        {                                                                    \
            printf("failed: NULL ;func:%s ;line:%d \n", __func__, __LINE__); \
            return NULL;                                                     \
        }                                                                    \
    } while (0);
// 调试宏 用于return int 的函数
#define DEBUG_R_INT(a)                                                       \
    do                                                                       \
    {                                                                        \
        if (!a)                                                              \
        {                                                                    \
            printf("failed: NULL ;func:%s ;line:%d \n", __func__, __LINE__); \
            return -1;                                                       \
        }                                                                    \
    } while (0);

typedef struct node
{
    uint32_t data;
    struct node *next;
    struct node *prev;
} Node, *link_list;

typedef struct
{
    uint8_t len;
    link_list head; // 头节点
    link_list tail; // 尾巴节点
} list, *round_list;

/*
    用途：用于生成一个双向循环链表
    输入：无
    输出：succeed :一个双向循环链表,failed : NULL
*/
round_list list_init(void);

/**
 * @brief  在循环链表中追加一个节点
 * @param  环形链表的指针
 * @param  node-> data
 * @retval succeed :节点地址；failed : NULL
 */
link_list append_node(round_list list, uint32_t data);

/**
 * @brief  在循环链表中插入一个节点
 * @param  环形链表的指针
 * @param  node-> data
 * @param  index: 要插入的索引
 * @retval succeed :节点地址；failed : NULL
 */
link_list inset_node(round_list list, uint32_t data, uint32_t index);

/**
 * @brief  根据node->data数值查找结点
 * @param  list：环形链表
 * @param  data： node->data
 * @retval succeed：返回节点地址； failed ： NULL
 */
link_list find_node_use_data(round_list list, uint32_t data);

/**
 * @brief  根据索引查找结点
 * @param  list：环形链表
 * @param  index： 索引
 * @retval succeed：返回节点地址； failed ： NULL
 */
link_list find_node_use_index(round_list list, uint32_t index);

/**
 * @brief  根据数值删除结点
 * @param  list：环形链表
 * @param  data： node->data
 * @retval succeed：删除的node->data； failed ：-1
 */
int64_t delete_node_use_data(round_list list, uint32_t data);

/**
 * @brief  根据索引删除结点
 * @param  list：环形链表
 * @param  index： 索引
 * @retval succeed：删除的node->data； failed ：-1
 */
int64_t delete_node_use_index(round_list list, uint32_t index);

/**
 * @brief  删除整个循环链表
 * @param  list：环形链表
 * @retval succeed：0； failed ：-1
 */
int8_t del_round_list(round_list list);

/**
 * @brief  打印整个循环链表
 * @param  list：环形链表
 * @retval 无
 */
void print_list(round_list list);
#endif