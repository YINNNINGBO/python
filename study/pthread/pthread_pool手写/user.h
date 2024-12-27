#ifndef __USER_H__
#define __USER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <errno.h>
#include <semaphore.h>
#include <pthread.h>

#define NUMBER 2
// 任务结构体
typedef struct Task
{
    void (*function)(void *arg);
    void *arg;
} Task;

// 线程池结构体
struct ThreadPool
{
    // 任务队列
    Task *taskQ;       // 数组形式的队列
    int queueCapacity; // 容量
    int queueSize;     // 当前任务个数
    int queueFront;    // 队头 -> 取数据
    int queueRear;     // 队尾 -> 放数据

    pthread_t managerID;       // 管理者线程ID
    pthread_t *threadIDs;      // 工作的线程ID
    int minNum;                // 最小线程数量
    int maxNum;                // 最大线程数量
    int busyNum;               // 忙的线程的个数
    int liveNum;               // 存活的线程的个数
    int exitNum;               // 要销毁的线程个数
    pthread_mutex_t mutexPool; // 锁整个的线程池
    pthread_mutex_t mutexBusy; // 锁busyNum变量
    pthread_cond_t notFull;    // 任务队列是不是满了
    pthread_cond_t notEmpty;   // 任务队列是不是空了

    int shutdown; // 是不是要销毁线程池, 销毁为1, 不销毁为0
};

typedef struct ThreadPool ThreadPool;

/**
 * 作用 ：创建并初始化线程池
 * 参数 ：  min ：线程池中初始默认的最小线程数；max：线程池中初始默认的最大线程数； queueSize：任务队列容量
 * return:   正确:返回一个ThreadPool指针;   错误: 返回NULL
 */
ThreadPool *threadPoolCreate(int min, int max, int queueSize);

/**
 * 作用：销毁线程池
 * 参数：ThreadPool *
 */
int threadPoolDestroy(ThreadPool *pool);

// 给线程池添加任务
void threadPoolAdd(ThreadPool *pool, void (*func)(void *), void *arg);

// 获取线程池中工作的线程的个数
int threadPoolBusyNum(ThreadPool *pool);

// 获取线程池中活着的线程的个数
int threadPoolAliveNum(ThreadPool *pool);

//////////////////////
// 工作的线程(消费者线程)任务函数  从任务队列中取出任务去执行
void *worker(void *arg);
// 管理者线程任务函数              添加线程  摧毁线程
void *manager(void *arg);
// 单个线程退出
void threadExit(ThreadPool *pool);
#endif

// 作者: 苏丙榅
// 链接: https://subingwen.cn/linux/threadpool/#3-%E7%BA%BF%E7%A8%8B%E6%B1%A0%E5%AE%9A%E4%B9%89
// 来源: 爱编程的大丙
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
