#include "user.h"
int main(int argc, const char *argv[])
{
    i32 tmp_data = 0;
    stack_list *stack = stack_init();
    srandom((i32)time(NULL));
    for (u8 i = 0; i < 10; i++)
    {
        i32 t = random() % 100;
        printf("%d ", t);
        push(stack, t);
    }
    putc('\n', stdout);
    tmp_data = push(stack, 12);
    print_stack(stack);
    if (tmp_data >= 0)
    {
        fputs("超出栈最大空间push成功\n", stdout);
    }
    tmp_data = pop(stack);
    printf("pop : %d \n", tmp_data);
    fputs("---------push一次", stdout);
    push(stack, 12);
    // if (tmp_data >= 0)
    // {
    printf("栈顶：%d\n", stack->top->data);
    print_stack(stack);
    // }
    // del_stack(stack);

    return 0;
}