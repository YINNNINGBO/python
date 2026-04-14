#include "user.h"
int main(int argc, const char *argv[])
{
    // printf("a+b = %d \n", add(1, 2));
    round_list list = list_init();
    append_node(list, 1);
    // 使用随机数插入链表
    srandom((unsigned int)time(NULL));
    for (uint8_t i = 0; i < 10; i++)
    {
        append_node(list, random() % 100);
    }
    print_list(list);
    printf("list len = %d \n", list->len);
    // 查找结点
    printf("--------------------------------------find_node_use_index\n");
    if (!find_node_use_index(list, 12))
    {
        printf("检测超出边界查找 :可以检测到超出边界值\n");
    }
    link_list find_node = find_node_use_index(list, 3);
    if (find_node->data == find_node_use_data(list, find_node->data)->data)
    {
        printf("func:find_node_use_data and func:find_node_use_index success \n");
    }
    printf("--------------------------------------func:find_node_use_XXX: del head\n");
    // 测试删除节点
    printf("--------------------------------------delete_node_use_data\n");
    delete_node_use_data(list, list->head->data);
    printf("--------------------------------------delete_node_use_index\n");
    delete_node_use_index(list, 0);
    print_list(list);
    return 0;
}