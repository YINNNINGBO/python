/**
 * @file    main.c
 * @auter   YinNingBo
 * @date    2026-4-3
 * @system  系统、硬件
 * @brief   带虚拟节点，虚拟节点用来存储数据链表的长度
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//  b  是控制返回值 是void * 还是 int
#define DEBUG_LIST_IF_NULL(a, b)                                      \
    do                                                                \
    {                                                                 \
        if (!a)                                                       \
        {                                                             \
            printf("file:%s,line:%d,链表为空\n", __FILE__, __LINE__); \
            if (b == 1)                                               \
            {                                                         \
                return NULL;                                          \
            }                                                         \
            else                                                      \
            {                                                         \
                return 0;                                             \
            }                                                         \
        }                                                             \
    } while (0)

#define DEBUG_MALLOC_IF_NULL(a, b)                                        \
    do                                                                    \
    {                                                                     \
        if (!a)                                                           \
        {                                                                 \
            printf("file:%s,line:%d,内存分配失败\n", __FILE__, __LINE__); \
            if (b == 1)                                                   \
            {                                                             \
                return NULL;                                              \
            }                                                             \
            else                                                          \
            {                                                             \
                return 0;                                                 \
            }                                                             \
        }                                                                 \
    } while (0)

typedef struct node
{
    int data;
    struct node *next;
} Node, *link_list;

/**
 * @brief  创建list 头
 * @retval 返回list  头
 */
link_list create_list(void)
{
    link_list L = (link_list)malloc(sizeof(Node));
    DEBUG_MALLOC_IF_NULL(L, 1);
    L->data = 0; // 虚拟节点数据域不存储数据
    L->next = NULL;
    return L;
}

/**
 * @brief  添加新节点
 * @param  参数1描述 L：链表头指针
 * @param  参数2描述 data：要添加的note-> data
 * @retval 返回 新节点
 */
link_list append_node(link_list *L, int data)
{
    // 判断链表是否 = NULL
    link_list p = *L;
    DEBUG_LIST_IF_NULL(*L, 1);
    // 遍历到链表末尾
    while (p->next)
    {
        p = p->next;
    }
    // 创建新节点
    link_list new_node = (link_list)malloc(sizeof(Node));
    DEBUG_MALLOC_IF_NULL(new_node, 1);
    (*L)->data++; // 虚拟节点数据域存储链表长度
    new_node->data = data;
    new_node->next = NULL;
    p->next = new_node;
    return new_node;
}

/**
 * @brief  插入节点
 * @param  参数1描述 L ：链表头指针
 * @param  参数2描述 data：要插入的note-> data
 * @param  参数3描述 index：要插入的位置  0开始
 * @retval 返回 新节点
 */
link_list insert_node(link_list *L, int data, int index)
{
    link_list p = *L;
    // 判断链表是否 = NULL
    DEBUG_LIST_IF_NULL(*L, 1);
    //  判断index是否合法
    if (index < 0)
    {
        // 若长度为0，index只能为0
        index = 0;
    }
    else if (index > (*L)->data)
    {
        // 若长度不为0，index只能在0~length-1之间
        index = (*L)->data;
    }
    // 遍历到要插入的位置
    for (int i = 0; i < index && p->next; i++)
    {
        p = p->next;
    }
    // 创建新节点
    link_list new_node = (link_list)malloc(sizeof(Node));
    DEBUG_MALLOC_IF_NULL(new_node, 1);
    (*L)->data++; // 虚拟节点数据域存储链表长度
    new_node->data = data;
    new_node->next = p->next;
    p->next = new_node;
    return new_node;
}

/**
 * @brief  简要删除节点
 * @param  L: list head
 * @param  data: 要删除的数值
 * @retval 返回值成功返回1，失败返回0
 */
int delete_node(link_list *L, int data)
{
    DEBUG_LIST_IF_NULL(*L, 0);
    link_list p = *L;
    while (p->next)
    {
        if (p->next->data == data)
        {
            link_list temp = p->next;
            p->next = temp->next;
            free(temp);
            (*L)->data--; // 虚拟节点数据域存储链表长度
            return 1;
        }
        p = p->next;
    }
    return 0;
}

/* 删除链表 */
void delete_list(link_list *L)
{
    if (!*L)
    {
        printf("file:%s,line:%d,链表为空\n", __FILE__, __LINE__);
        return;
    }
    link_list p = *L;
    while (p)
    {
        link_list temp = p;
        p = p->next;
        free(temp);
    }
}

/**
 * @brief  返回想要节点的数值
 * @param  链表
 * @param  0开始的所以 ，（用于指定是哪个note）
 * @retval 返回值note->data
 */
int get_data(link_list *L, int index)
{
    DEBUG_LIST_IF_NULL(*L, 0);
    link_list p = *L;
    // 判断index 的合理性
    if (index < 0)
    {
        // 返回第一个
        return (*L)->next->data; // index 超出范围
    }
    else if (index >= (*L)->data)
    { // index 超出范围 就返回最后一个

        while (p->next)
        {
            p = p->next;
        }
        return p->data; // index 超出范围
    }
    else
    {
        // 遍历到要获取的节点
        for (int i = 0; i < index && p->next; i++)
        {
            p = p->next;
        }
        return p->data;
    }
}

int print_list(link_list *L)
{
    DEBUG_LIST_IF_NULL(*L, 0);
    link_list p = (*L)->next; // 跳过虚拟节点
    while (p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
    return 1;
}

int main(int argc, const char *argv[])
{
    // 1.创建链表
    link_list L = create_list();
    // 2.追加节点
    // 创建随机数
    srandom((int)time(NULL));
    for (int i = 0; i < 10; i++)
    {
        append_node(&L, random() % 100); // 生成100以内的随机数
    }
    print_list(&L);
    // 3.插入节点
    insert_node(&L, 999, 3); // 在链表头插入999
    print_list(&L);
    // 4.删除节点 text  delete No.3
    delete_node(&L, get_data(&L, 3));
    print_list(&L);
    // 5.删除链表
    delete_list(&L);
    return 0;
}