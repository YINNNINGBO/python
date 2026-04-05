双向链表 （并非环形） 有虚拟节点

typedef struct node
{
    int data;
    struct node *next; // 表示下一个
    struct node *prev; // 表示上一个
} Node, *link_list;

首节点->prev = NULL
尾巴节点->next = NULL 