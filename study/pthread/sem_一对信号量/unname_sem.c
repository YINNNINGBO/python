
#include "user.h"

#define BUF_SIZE 5 // 缓冲区大小

// 共享缓冲区
int buffer[BUF_SIZE];
int in = 0;  // 写入位置
int out = 0; // 读取位置

// 信号量
sem_t empty;           // 控制缓冲区空位置
sem_t full;            // 控制缓冲区满位置
pthread_mutex_t mutex; // 互斥锁，保护共享缓冲区

void *producer(void *arg)
{
    for (int i = 0; i < 10; i++)
    {
        // 生产数据
        sem_wait(&empty);           // 等待直到缓冲区有空位置
        pthread_mutex_lock(&mutex); // 进入临界区

        buffer[in] = i; // 写入数据
        printf("生产者生产数据: %d\n", i);
        in = (in + 1) % BUF_SIZE; // 更新写入位置

        pthread_mutex_unlock(&mutex); // 离开临界区
        sem_post(&full);              // 增加满的位置，通知消费者

        usleep(500000); // 模拟生产的延迟
    }
    return NULL;
}

void *consumer(void *arg)
{
    for (int i = 0; i < 10; i++)
    {
        sem_wait(&full);            // 等待直到缓冲区有数据
        pthread_mutex_lock(&mutex); // 进入临界区

        int data = buffer[out]; // 读取数据
        printf("消费者消费数据: %d\n", data);
        out = (out + 1) % BUF_SIZE; // 更新读取位置

        pthread_mutex_unlock(&mutex); // 离开临界区
        sem_post(&empty);             // 增加空的位置，通知生产者

        usleep(800000); // 模拟消费的延迟
    }
    return NULL;
}

int main()
{
    // 初始化信号量
    sem_init(&empty, 0, BUF_SIZE);    // 初始时缓冲区是空的
    sem_init(&full, 0, 0);            // 初始时没有数据
    pthread_mutex_init(&mutex, NULL); // 初始化互斥锁

    pthread_t producer_thread, consumer_thread;

    // 创建生产者和消费者线程
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // 等待线程完成
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // 销毁信号量和互斥锁
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
