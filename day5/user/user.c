#include "user.h"

#if 0  // 测试makefile  的代码
uint32_t add(uint32_t a, uint32_t b)
{
    return (a + b);
}
#endif // 0

round_list list_init(void)
{
    // 1. 申请一个环形链表的内存空间
    round_list list = (round_list)malloc(sizeof(list));
    DEBUG_R_NULL(list);
    // 2. 链表初始化 ，长度, head ,prev
    list->head = NULL;
    list->tail = NULL;
    list->len = 0;
    return list;
}

link_list append_node(round_list list, uint32_t data)
{
    // 1.参数判断
    DEBUG_R_NULL(list);
    // 2. 申请一个节点的空间
    link_list node = (link_list)malloc(sizeof(Node));
    DEBUG_R_NULL(node);
    node->data = data;
    // 3.插入合适的位置
    // 3.1 首节点
    if (list->len == 0)
    {
        list->head = node;
        list->tail = node;
        node->next = node;
        node->prev = node;
    }
    // 3.2 正好第二个节点也是危机带你
    else if (list->len == 1)
    {
        node->prev = list->head;
        node->next = list->head;
        list->head->next = node;
        list->head->prev = node;
        list->tail = node;
    }
    else
    {
        node->prev = list->tail;
        node->next = list->head;
        list->tail->next = node;
        list->head->prev = node;
        list->tail = node;
    }

    list->len++;
    return node;
}

link_list inset_node(round_list list, uint32_t data, uint32_t index)
{
    // 1.参数判断 list
    DEBUG_R_NULL(list);
    // 2. 申请一个节点的空间
    link_list node = (link_list)malloc(sizeof(Node));
    DEBUG_R_NULL(node);
    node->data = data;
    // 3.插入合适的位置 （
    // 3.1 首节点
    if (index == 0)
    {
        node->prev = list->tail;
        node->next = list->head;
        list->head->prev = node;
        list->tail->next = node;
        list->head = node;
    }
    // 3.2 尾  index 若是过大，直接插到结尾）
    else if (index == (list->len - 1) || index >= list->len)
    {
        node->prev = list->tail;
        node->next = list->head;
        list->tail->next = node;
        list->head->prev = node;
        list->tail = node;
    }
    // 3.3 中间  （遍历到前一个）
    else
    {
        link_list tmp = list->head;
        for (uint8_t i = 0; i < index - 1; i++) // 遍历插入到必要位置
        {
            tmp = tmp->next;
        }
        node->prev = tmp;
        node->next = tmp->next;
        tmp->next->prev = node;
        tmp->next = node;
    }
    list->len++;
    return node;
}

link_list find_node_use_data(round_list list, uint32_t data)
{
    // 1. 参数判断
    DEBUG_R_NULL(list);
    // 2. 遍历链表，找到data相同的节点
    link_list tmp = list->head;
    do
    {
        if (tmp->data == data)
        {
            return tmp;
        }
        tmp = tmp->next;
    } while (tmp != list->head); // 遍历链表
    //* 没有找到要查找的节点
    printf("failed: not found data ;func:%s ;line:%d \n", __func__, __LINE__);
    return NULL;
}

link_list find_node_use_index(round_list list, uint32_t index)
{
    // 1. 参数判断 list  index
    DEBUG_R_NULL(list);
    if (index >= list->len)
    {
        printf("failed: index out of range ;func:<%s> ; line:%d \n", __func__, __LINE__);
        return NULL;
    }
    // 2. 遍历链表，找到索引相同的节点
    link_list tmp = list->head;
    for (uint8_t i = 0; i < index; i++)
    {
        tmp = tmp->next;
    }
    return tmp;
}

int64_t delete_node_use_data(round_list list, uint32_t data)
{
    // 1. 参数判断
    DEBUG_R_INT(list);
    // 2. 遍历链表，找到data相同的节点
    link_list tmp = list->head;
    int64_t re_data;
    for (uint8_t i = 0; i < list->len; i++)
    {
        if (tmp->data == data) // 当前节点就是要删除的节点
        {
            tmp->prev->next = tmp->next;
            tmp->next->prev = tmp->prev;
            if (tmp == list->head) // 要删除的节点是 head
            {
                list->head = tmp->next; // 更新 head
            }
            if (tmp == list->tail)
            {
                list->tail = tmp->prev; // 更新 tail
            }
            re_data = tmp->data;
            free(tmp);
            list->len--;
            return re_data;
        }
        tmp = tmp->next;
    }
    // 没有找到要删除的节点
    printf("failed: not found data ;func:%s ;line:%d \n", __func__, __LINE__);
    return -1;
}

int64_t delete_node_use_index(round_list list, uint32_t index)
{
    // 1. 参数判断 list index
    DEBUG_R_INT(list);
    if (index >= list->len)
    { // 要删除的节点不存在
        printf("failed: index out of range ;func:%s ;line:%d \n", __func__, __LINE__);
        return -1;
    }
    // 2. 遍历链表，找到索引相同的节点
    // 2.1 要删除头节点
    int64_t re_data;
    if (index == 0)
    {
        // 要删除的节点是 head
        link_list del = list->head;
        list->tail->prev = del->next;
        del->next->prev = list->tail;
        list->head = del->next;
        re_data = del->data;
        free(del);
    }
    else
    {
        link_list tmp = list->head;
        for (uint8_t i = 0; i < index; i++) // 遍历当前节点
        {
            tmp = tmp->next;
        }
        if (tmp == list->tail) // 要删除的节点是 tail
        {
            list->tail = tmp->prev; // 更新 tail
        }
        // 删除节点
        re_data = tmp->data;
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
        free(tmp);
    }
    list->len--;
    return re_data;
}

int8_t del_round_list(round_list list)
{
    // 1. 参数判断 list
    DEBUG_R_INT(list);
    // 2. 遍历链表，删除每个节点
    link_list tmp = list->head;
    for (uint8_t i = 0; i < list->len; i++)
    {
        link_list del = tmp;
        tmp = tmp->next;
        free(del);
    }
    // 3. 删除链表
    free(list);
    return 0;
}

void print_list(round_list list)
{
    // 1. 参数判断 list
    if (!list)
    {
        printf("failed: NULL ;func:%s ;line:%d \n", __func__, __LINE__);
    }
    // 2. 遍历链表，打印每个节点
    link_list tmp = list->head;
    for (uint8_t i = 0; i < list->len; i++)
    {
        printf("%d ", tmp->data);
        tmp = tmp->next;
    }
    putc('\n', stdout);
}