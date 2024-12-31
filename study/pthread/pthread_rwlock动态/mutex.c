#include "user.h"
#include <bits/pthreadtypes.h>
/**
 * 读写锁
 * 读操作使用读锁  可以让读操作并发读
 * 写操作使用写锁  可以阻塞其他使用写锁的与读锁的操作
 */
pthread_rwlock_t rwlock;

static int data = 0;

void *mutex_read(void *arg)
{
    /**
     * 读  分上锁与不上锁
     * 上锁    并行读，但是不回被其他写线程打断
     * 不上锁 并行读 但是又可能被写线程打断
     */
    // 上读锁  不让其他线程写，同使可以多个线程并发读
   // pthread_rwlock_rdlock(&rwlock);
    printf("在<读>线程内data:>%d,arg:>%s\n", data, (char *)arg);
    sleep(1); // 可以看出上锁后以一次次读还是 一次去全读
   // pthread_rwlock_unlock(&rwlock);
}
void *mutex_write(void *arg)
{
    /**
     * 如果这里不上锁  不同的写线程  对data有竞态的可能
     * 又可能发生  data<3 的现象    《有可能》
     */
    // 写的过程上写锁 阻塞其他线程程写，和读
    pthread_rwlock_wrlock(&rwlock);
    data += 1;
    printf("在<写>线程内data:>%d,arg:>%s\n", data, (char *)arg);
    usleep(500000);
    pthread_rwlock_unlock(&rwlock);
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
    sleep(4);
    /**
     * 这个时间必须 >  各线程都执行完后相加的时间 ，
     * 否则父进程结束，旗下的线程即便使用“pthread_detach”  分离  也会因为父进程结束而结束
     *
     *  ****进程结束，进程其下的线程都会因此结束，资源被上层进程回收
     *
     * */

    // 动态初始化
    pthread_rwlock_init(&rwlock, NULL);
    // 分离线程
    pthread_detach(tid_w0);
    pthread_detach(tid_w1);
    pthread_detach(tid_w2);
    pthread_detach(tid_r0);
    pthread_detach(tid_r1);
    pthread_detach(tid_r2);

    // 释放互斥锁
    pthread_rwlock_destroy(&rwlock);
    return 0;
}
