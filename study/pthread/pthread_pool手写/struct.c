/*嵌套结构体指针 混淆点*/
#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    void *arg;
} Task;

typedef struct
{
    int data;
} B;

typedef struct
{

    Task *taskQ;
    B *tmp;
} Pool;

int main()
{
    int a = 9;
    Pool *mypool = (Pool *)malloc(sizeof(Pool));
    mypool->taskQ = (Task *)malloc(sizeof(Task) * 5);
    mypool->tmp = (B *)malloc(sizeof(B));

    mypool->taskQ[3].arg = (void *)&a; // 这个有什么区别
    mypool->tmp->data = 10;
    printf(" mypool->taskQ[3].arg=%d\n", *(int *)(mypool->taskQ[3].arg));
    ((mypool->taskQ) + 3)->arg = (void *)&a;
    //(*(mypool->taskQ + 3)).arg = (void *)&a; // 正确写法
    // printf(" mypool->*(taskQ+3)->arg = %d\n", *(int *)(mypool->*(taskQ + 3)->arg));
    printf(" mypool->*(mypool->taskQ + 3)->arg = %d\n", *(int *)(*(mypool->taskQ + 3)).arg);

    printf(" mypool->tmp->data =%d\n", mypool->tmp->data);
    return 0;
}