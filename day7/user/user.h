#ifndef USER_H__
#define USER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
// typedef char i8;
// typedef unisgned char u8;

// typedef int i32;
// typedef unisgned int u32;

typedef int i32;
typedef unsigned int u32;
typedef char i8;
typedef unsigned char u8;

#define STACK_MAN_LEN 10
typedef struct node
{
    i32 data;
    struct node *next;
} link_node, *linklist;
typedef struct
{
    linklist top; // 栈顶指针
    u32 count;    // 栈长度
} stack_list;

/**
 * 创建空链栈 count = 0
 * 无参数，
 * retval: success :链栈指针， ；failed：NULL
 */
stack_list *stack_init(void);

/**
 * @brief  判断栈是不是空的
 * @param  f_stack :链栈指针 **
 * @retval -1:检测失败； 0：空； 1 ：不为空
 */
i8 if_empty(stack_list *f_stack);

/**
 * @brief  判断栈是不是满的
 * @param  f_stack :链栈指针 **
 * @retval -1:检测失败； 0：满； 1 ：不满
 */
i8 if_full(stack_list *f_stack);

/**
 * @brief  入栈  (头插法)
 * @param  f_stack :链栈指针 **
 * @param f_data :入栈的数据
 * @retval -1: malloc failed ,0 :ok
 */
i8 push(stack_list *f_stack, i32 f_data);

/**
 * @brief  出栈
 * @param  f_stack :链栈指针 **
 * @retval success :f_satck->node->data ; failed : -1
 */
i32 pop(stack_list *f_stack);

/**
 * @brief 销毁栈
 * @param  f_stack :链栈指针 **
 * @retval success :0   ; failed : -1
 */
i8 del_stack(stack_list *f_stack);

i8 print_stack(stack_list *f_stack);
#endif