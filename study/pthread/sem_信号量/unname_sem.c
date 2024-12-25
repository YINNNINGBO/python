#include "user.h"

sem_t unname_sem;
static int data = 0;
#define TID_ARR_SIZE 1000
void *my_header(void *arg)
{
    // 信号亮上锁
    sem_wait(&unname_sem);
    data += 1;
    // 信号亮唤醒
    sem_post(&unname_sem);
    return NULL;
}
int main(int argc, const char **argv)
{
    char *arg = (char *)malloc(sizeof(char) * 100);
    pthread_t tid_arr[TID_ARR_SIZE];

    /**
     * sem_init (sem_t *__sem, int __pshared, unsigned int __value)
     * __pshared  0：表示同进程下的不同线程间，1：表示不同进程间。
     * __value    0：表示信号亮不可用，       1：表示信号量可用
     */
    // 信号量初始化
    if (sem_init(&unname_sem, 0, 1))
    {
        perror("sem_init is failed!!");
        fprintf(stderr, "errno is :%d\n", errno);
        _exit(EXIT_FAILURE);
    }
    // 创建线程
    for (int i = 0; i < TID_ARR_SIZE; i++)
    {
        if (pthread_create(tid_arr + i, NULL, my_header, (void *)arg))
        {
            perror("pthread_create is failed!!");
            fprintf(stderr, "pthread_create NO:%d,errno is :%d\n", i, errno);
        }
    }
    // 回收线程
    for (int i = 0; i < TID_ARR_SIZE; i++)
    {
        if (pthread_join(tid_arr[i], NULL))
        {
            perror("pthread_join is failed!!");
            fprintf(stderr, "pthread_join NO:%d,errno is :%d\n", i, errno);
        }
    }
    printf("in late data =:%d\n", data);
    // 销毁信号量
    if (sem_destroy(&unname_sem))
    {
        perror("sem_destroy is failed!!");
        fprintf(stderr, "errno is :%d\n", errno);
        _exit(EXIT_FAILURE);
    }
    return 0;
}