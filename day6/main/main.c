#include "user.h"
i32 main(i32 argc, const i8 *argv[])
{
    Stack s;
    initStack(&s);

    push(&s, 10);
    push(&s, 20);
    push(&s, 30);

    printf("当前栈顶元素: %d\n", peek(&s));

    printf("出栈: %d\n", pop(&s));
    printf("出栈: %d\n", pop(&s));

    printf("当前栈顶元素: %d\n", peek(&s));

    return 0;
}