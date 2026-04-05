/**
 * @file day4/main.c
 * @auter   YinNingBo
 * @date    2026-4-5
 * @system  Linux C
 * @description  双向链式链表（没有头节点）。
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node
{
    int data;
    struct node *next; // 表示下一个
    struct node *prev; // 表示上一个
} Node, *link_list;

// 同时显示出头和尾巴 ，便于双向遍历
typedef struct
{
    link_list head;
    link_list tail;
} List, *bothway_list;
// return ptr 的函数用的判NULL

#define DEBUG_NULL_PTR(a)                                                         \
    do                                                                            \
    {                                                                             \
        if (!a)                                                                   \
        {                                                                         \
            printf(" func:%s,line:%d . failed : is NULL \n", __func__, __LINE__); \
            return NULL;                                                          \
        }                                                                         \
    } while (0)

// return int 的函数用的判NULL
#define DEBUG_NULL_INT(a)                                                         \
    do                                                                            \
    {                                                                             \
        if (!a)                                                                   \
        {                                                                         \
            printf(" func:%s,line:%d . failed : is NULL \n", __func__, __LINE__); \
            return -1;                                                            \
        }                                                                         \
    } while (0)

/**
 * @brief  创建链表 ，初始值为 -1 ，用来记录len(list)
 * @retval 返回值描述
 */
bothway_list create_list(void)
{
    //  创建链表
    bothway_list list = (bothway_list)malloc(sizeof(List));
    DEBUG_NULL_PTR(list);

    // 2. 创建节点
    link_list head = (link_list)malloc(sizeof(Node));
    DEBUG_NULL_PTR(head);
    head->data = 0;

    head->prev = NULL;
    head->next = NULL;
    list->head = head; // 头尾是同一个节点
    list->tail = head;
    return list;
}

/*
 *  追加节点
 *  Ｌ: 链表
 *  f_data : 要追加的node-> data
 */
link_list append_node(bothway_list *L, int f_data)
{
    // printf("%d\t", f_data);     回显
    // 1. 参数检测
    DEBUG_NULL_PTR(*L);
    // 2. 生成新节点：
    link_list new_node = (link_list)malloc(sizeof(Node));
    DEBUG_NULL_PTR(new_node);
    new_node->data = f_data; // 存储数值
    new_node->next = NULL;   // 新节点的next
    link_list p = (*L)->head;
    if ((*L)->head->data == 0)
    {                                // 建立new_node 的next 与  prve
        new_node->prev = (*L)->head; // 新节点的prve

        (*L)->head->data = 1; // 长度更新
        (*L)->head->next = new_node;
        (*L)->tail = new_node;
    }
    else if ((*L)->head->data >= 0)
    {
        // 3.2 插入尾节点
        new_node->prev = (*L)->tail;
        (*L)->tail->next = new_node;
        (*L)->tail = new_node;
        (*L)->head->data++;
    }

    return new_node;
}

/**
 * @brief  简要描述函数功能
 * @param  参数1描述
 * @param  参数2描述
 * @param
 * @retval 返回值描述
 */
link_list insert_node(bothway_list *L, unsigned int f_index, int f_data)
{
    // 1. 参数检测 L ，f_index
    DEBUG_NULL_PTR(*L);
    if ((f_index <= 0) || f_index >= (*L)->head->data)
    {
        printf("func:%s,line:%d ; f_inex is out of (len-1) \n", __func__, __LINE__);
        return NULL;
    }
    // 2. 创建新节点
    link_list new_node = (link_list)malloc(sizeof(Node));
    new_node->data = f_data;

    // 3. 遍历到f_index-1位置
    link_list p = (*L)->head;
    if (f_index == 0) // 插入位置是首节点
    {
        new_node->prev = (*L)->head;
        new_node->next = (*L)->head->next;

        (*L)->head->next = new_node;
        // 判断首节点是否为NULL
        if ((*L)->head->next)
        {
            // 首节点为NULL
            (*L)->head->next->prev = new_node;
            (*L)->tail = new_node;
        }
    }
    if (f_index == ((*L)->head->data - 1)) //   插入位置是尾节点
    {
        new_node->prev = (*L)->tail;
        new_node->next = (*L)->tail->next;

        (*L)->tail->next = new_node;
        (*L)->tail = new_node;
    }
    // 在其他位置(1 ~ len-2)
    (*L)->head->data++;
    for (int i = 0; i <= f_index; i++)
    {
        if (i == f_index)
        {
            // 遍历到要插入的前一个了
            new_node->next = p->next;
            new_node->prev = p;
            p->next->prev = new_node;
            p->next = new_node;
        }
        else
        {
            // 没有遍历到
            p = p->next;
        }
    }
    // 更新长度
    return new_node;
}

/**
 * @brief  通过node->data 查找节点
 * @param  L:
 * @param  f_data：要查找的对象
 * @retval succeed：节点；   failed ： NULL
 */
link_list find_node_use_data(bothway_list *L, int f_data)
{
    // 1. 参数验证
    DEBUG_NULL_PTR(*L);
    // 2. 遍历查找到node->next->data = f_data的节点
    link_list p = (*L)->head->next;
    while (p)
    {
        if (p->data == f_data)
        {
            return p;
        }
        else
        {
            p = p->next;
        }
    }
    // 没有找到
    printf("func:%s,line:%d, no found %d .\n", __func__, __LINE__, f_data);
    return NULL;
    // 3. 返回找到的节点
}

/**
 * @brief  根据索引查找节点，
 * @param  L:
 * @param  f_index: 索引值 （0 开始）
 * @retval failed:NULL   ;succeed: 找到的节点
 */
link_list find_node_use_index(bothway_list *L, int f_index)
{
    // 1. 参数验证
    DEBUG_NULL_PTR(*L);
    if (f_index <= 0 && f_index >= (*L)->head->data)
    {
        printf("func:%s ,line:%d f_index is out of len-1.\n", __func__, __LINE__);
        return NULL;
    }
    // 2. 遍历查找到f_index
    link_list p = (*L)->head->next;
    for (int i = 0; i < f_index; i++)
    {
        p = p->next;
    }
    return p;
    // 3. return
}

/**
 * @brief  根据数值删除节点
 * @param  L
 * @param  f_data:
 * @retval -1 :failed  , >=0 :succeed
 */
int del_node_use_data(bothway_list *L, int f_data)
{
    // 1. 参数验证
    DEBUG_NULL_INT(*L);
    // 2. 遍历
    int sign_find_if = -1; // 找到置为1
    link_list p = (*L)->head;
    int get_data;
    while (p->next)
    {
        if (p->next->data == f_data)
        { // 找到节点了
            sign_find_if = 1;
            (*L)->head->data--; //  更新记录的长度
            link_list del_node = p->next;
            p->next = del_node->next; // 重置p->next
            del_node->prev = NULL;
            if (p != (*L)->tail) // 该节点不是tail 时 需要的另外处理
            {
                // 当该节点是tail 时
                del_node->next->prev = p;
                del_node->next = NULL;
            }
            get_data = del_node->data;
            free(del_node);
            del_node = NULL;
            // break;   不跳出  若还有继续del
        }
        else
        {
            p = p->next;
        }
    }
    if (sign_find_if == 1)
    {
        return get_data;
    }
    else
    {
        printf("del_node_use_data failed ,because not finded \n");
    }
}

/**
 * @brief  根据索引删除节点
 * @param  L；链表
 * @param  f_index:索引值
 * @retval  -1； failed ，>0 ： succeed
 */
int del_node_use_index(bothway_list *L, unsigned f_index)
{
    // 1. 验证 参数 L f_index
    DEBUG_NULL_INT(*L);
    if (f_index <= 0 && f_index >= (*L)->head->data)
    {
        printf("func:%s ,line:%d f_index is out of len-1.\n", __func__, __LINE__);
        return -1;
    }

    // 2. 遍历 到index = f_index-1
    link_list p = (*L)->head;

    for (int i = 0; i < f_index - 1; i++)
    {
        p = p->next;
    }

    (*L)->head->data--; //  更新length
    link_list del_node = p->next;
    // 3. 分为 del_node = tail 和 != tail  两种情况
    if (del_node == (*L)->tail)
    { // del_node = tail
        p->next = del_node->next;
        del_node->prev = NULL;
    }
    else
    { // del_node != tail
        p->next = del_node->next;
        del_node->next->prev = p;
        del_node->next = NULL;
        del_node->prev = NULL;
    }
    int get_data = del_node->data;
    free(del_node);
    del_node = NULL;
    return get_data;
}

// 因为是双向的所以  从tail 开始删除会更简单
int del_list(bothway_list *L)
{
    // 1， 验证
    DEBUG_NULL_INT(*L);
    // 2.  删除整个链表
    link_list p = (*L)->tail;
    while (p)
    {
        link_list del_node = p;
        p = p->prev;
        (*L)->head->data--;
        free(del_node);
        del_node = NULL;
    }
    free(*L); // *L : 才是申请的堆内存 ，free(L) 释放的栈，会报错
    (*L) = NULL;
    return 1;
}

/**
 * @brief  打印整个链表
 * @param  L
 * @retval 1 ： succeed ; -1 :error
 */
int printf_list(bothway_list *L)
{
    // 1. 参数判断
    DEBUG_NULL_INT(*L);
    // 2. 遍历打印
    link_list p = (*L)->head->next;
    while (p)
    {
        printf("%d  ", p->data);
        p = p->next;
    }
    fputs("\n", stdout);
    return 1;
}

/**
 * @brief  获取链表的长度
 * @param  L： 链表
 * @retval  > 0 :实际长度， -1 ：error
 */
int get_list_length(bothway_list *L)
{ // 1. 判断参数
    DEBUG_NULL_INT(*L);
    // 获取链表长度
    link_list p = (*L)->head->next;
    int len = 0;
    while (p)
    {
        p = p->next;
        len++;
    }
    return len;
}

int main(int argc, const char *argv[])
{
    // 1. 创建链表
    bothway_list L = create_list();

    // 2. append 追击节点
    srandom((unsigned int)time(NULL));
    for (int i = 0; i < 10; i++)
    {
        append_node(&L, random() % 100);
    }
    printf_list(&L);
    // 3. insert 插入节点
    int ret = 0;
    link_list ret_node = NULL; // 先初始化两个变量用于接收返回值
    // ret_node = insert_node(&L, -1, 1000);
    // DEBUG_NULL_INT(ret_node);
    // ret_node = insert_node(&L, 13, 1000);
    // DEBUG_NULL_INT(ret_node);
    ret_node = insert_node(&L, 5, 1000);
    DEBUG_NULL_INT(ret_node);
    printf_list(&L);

    // 4.index 查找节点
    ret_node = find_node_use_index(&L, 3);
    printf("find data:%d ,use index:3. \n", ret_node->data);
    // 5.  data 查找节点
    ret = find_node_use_data(&L, ret_node->data)->data;
    printf("find data:%d ,use data. \n", ret);
    // 6. del index
    ret = del_node_use_index(&L, 3);
    printf("del_node_use_index : %d\n", ret);
    printf_list(&L);

    // 7. del data
    printf("del_node_use_data: %d\n", del_node_use_data(&L, find_node_use_index(&L, 3)->data));
    printf_list(&L);

    // 8. lenght
    ret = get_list_length(&L);

    if (((L)->head->data) == get_list_length(&L))
    {
        printf("func : get_list_lenght  is sueeccd .\n");
    }
    // 9. del list
    del_list(&L);
    return 0;
}
