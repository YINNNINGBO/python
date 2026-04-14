#ifndef USER_H__
#define USER_H__

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef int i32;
typedef unsigned int u32;
typedef char i8;
typedef unsigned char u8;
#define MAX_SIZE 1024
typedef struct
{
    i32 data[MAX_SIZE];
    u32 top; // 用于指向栈顶
} Stack;

void initStack(Stack *s);

// 判断栈是否为空
int isEmpty(Stack *s);

// 判断栈是否满
int isFull(Stack *s);

// 入栈
void push(Stack *s, int value);

// 出栈
int pop(Stack *s);

// 查看栈顶元素
int peek(Stack *s);
#endif