#include "user.h"

// 互斥锁静态初始化  相比与动态初始化  不需要手动释放
pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;

static int data = 0;

void *mutex_read(void *arg)
{
    /**
     * 读  分上锁与不上锁
     * 上锁    会一次次读，每次读取中间隔 100000um
     * 不上锁  会同时读  ，每次读取中间隔 100000um
     */
    pthread_mutex_lock(&my_mutex);
    printf("在<读>线程内data:>%d,arg:>%s\n", data, (char *)arg);
    usleep(100000); // 可以看出上锁后以一次次读还是 一次去全读
    pthread_mutex_unlock(&my_mutex);
}
void *mutex_write(void *arg)
{
    /**
     * 如果这里不上锁  不同的写线程  对data有竞态的可能
     * 又可能发生  data<3 的现象    《有可能》
     */
    // pthread_mutex_lock(&my_mutex);
    data += 1;
    printf("在<写>线程内data:>%d,arg:>%s\n", data, (char *)arg);
    usleep(100000);
    // pthread_mutex_unlock(&my_mutex);
}

int main(int argc, const char **argv)
{
    pthread_t tid_w0, tid_w1, tid_w2, tid_r0, tid_r1, tid_r2;
    pthread_create(&tid_w0, NULL, mutex_write, (void *)"write1");
    pthread_create(&tid_w1, NULL, mutex_write, (void *)"write2");
    pthread_create(&tid_w2, NULL, mutex_write, (void *)"write3");

    pthread_create(&tid_r0, NULL, mutex_read, (void *)"read1");
    pthread_create(&tid_r1, NULL, mutex_read, (void *)"read2");
    pthread_create(&tid_r2, NULL, mutex_read, (void *)"read3");
    sleep(2);
    // 分离线程
    pthread_detach(tid_w0);
    pthread_detach(tid_w1);
    pthread_detach(tid_w2);
    pthread_detach(tid_r0);
    pthread_detach(tid_r1);
    pthread_detach(tid_r2);

    return 0;
}