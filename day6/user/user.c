#include "user.h"

// 初始化栈
void initStack(Stack *s)
{
    s->top = -1;
}

// 判断栈是否为空
int isEmpty(Stack *s)
{
    return s->top == -1;
}

// 判断栈是否满
int isFull(Stack *s)
{
    return s->top == MAX_SIZE - 1;
}

// 入栈
void push(Stack *s, int value)
{
    if (isFull(s))
    {
        printf("栈已满，无法入栈！\n");
        return;
    }
    s->data[++(s->top)] = value;
}

// 出栈
int pop(Stack *s)
{
    if (isEmpty(s))
    {
        printf("栈为空，无法出栈！\n");
        return -1;
    }
    return s->data[(s->top)--];
}

// 查看栈顶元素
int peek(Stack *s)
{
    if (isEmpty(s))
    {
        printf("栈为空！\n");
        return -1;
    }
    return s->data[s->top];
}