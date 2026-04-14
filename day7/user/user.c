#include "user.h"
/**
 * 链栈使用头插法
 */
#define DEBUG(a)                                                           \
    do                                                                     \
    {                                                                      \
        if (!a)                                                            \
        {                                                                  \
            printf("fail:is NULL :func:%s,line:%d\n", __func__, __LINE__); \
            return -1;                                                     \
        }                                                                  \
    } while (0)

#define OK ((u8)0)
#define FAILED ((u8)(-1))

stack_list *stack_init(void)
{
    stack_list *stack = (stack_list *)malloc(sizeof(stack_list));
    if (!stack)
    {
        printf("malloc failed func:%s ;line:%d\n", __func__, __LINE__);
        return NULL;
    }
    stack->top = NULL;
    stack->count = 0;
    return stack;
}

i8 if_empty(stack_list *f_stack)
{
    DEBUG(f_stack);
    if ((f_stack->count == 0) && (f_stack == NULL))
    {
        return OK;
    }
    else
    {
        return 1;
    }
}

i8 if_full(stack_list *f_stack)
{
    DEBUG(f_stack);
    if (f_stack->count == STACK_MAN_LEN)
    {
        return OK;
    }
    else
    {
        return 1;
    }
}

i8 push(stack_list *f_stack, i32 f_data)
{
    DEBUG(f_stack);
    if (f_stack->count == STACK_MAN_LEN)
    {
        printf("push 无效队列满了\n");
        return -1;
    }
    linklist node = (linklist)malloc(sizeof(link_node));
    DEBUG(node);
    node->data = f_data;
    node->next = f_stack->top;
    f_stack->top = node;
    f_stack->count++;
    return 0;
}

i32 pop(stack_list *f_stack)
{
    DEBUG(f_stack);
    linklist tmp_node = f_stack->top;
    i32 data = tmp_node->data;
    f_stack->top = tmp_node->next;
    f_stack->count--;
    free(tmp_node);
    return data;
}

i8 del_stack(stack_list *f_stack)
{
    DEBUG(f_stack);
    for (i32 i = 0; i < f_stack->count; i++)
    {
        pop(f_stack);
    }
    free(f_stack);
    f_stack = NULL;
    return 0;
}

i8 print_stack(stack_list *f_stack)
{
    // stack_list *tmp_stack = f_stack;  之类有个问题，f_stack 指向的是list的尾节点，这种类型转换是不合理的(得不到头节点)。
    if (!f_stack)
    {
        printf("failed 参数为空\n");
        return -1;
    }
    linklist tmp_node = f_stack->top;
    for (u8 i = 0; i < (f_stack->count); i++)
    {
        printf("%d ", tmp_node->data);
        if (!tmp_node->next)
        {
            break;
        }
        tmp_node = tmp_node->next;
    }
    putc('\n', stdout);
    return 0;
}
