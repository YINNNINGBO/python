#include "user.h"
/** 测试结果
 ./mutex
在<写> __data[0]:>1,arg:>write1
在<读> __data[0]:>1,arg:>read3
在<写> __data[0]:>2,arg:>write1
在<读> __data[0]:>2,arg:>read3
在<写> __data[0]:>3,arg:>write1
在<读> __data[0]:>3,arg:>read3
在<写> __data[0]:>4,arg:>write1
在<读> __data[0]:>4,arg:>read3
在<写> __data[0]:>5,arg:>write1
在<读> __data[0]:>5,arg:>read3
在<写> __data[0]:>6,arg:>write1
在<读> __data[0]:>6,arg:>read3
在<写> __data[0]:>7,arg:>write1
在<读> __data[0]:>7,arg:>read3
在<写> __data[0]:>8,arg:>write1
^Cmake: *** 正在删除文件“mutex”
make: *** [Makefile:6: mutex] 中断
*/

// 互斥锁静态初始化  相比与动态初始化  不需要手动释放
pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t my_cond = PTHREAD_COND_INITIALIZER;

#define BUF_SIZE 5
static int data[BUF_SIZE];
static int count = 0;       // 数组内索引
static int write_allow = 1; //=1:允许写， =0：允许读   作为是否阻塞线程的标志位
void *mutex_read(void *arg)
{

    while (1)
    {
        pthread_mutex_lock(&my_mutex);
        while (write_allow || !count)
        { // 如果没有数据可读

            pthread_cond_wait(&my_cond, &my_mutex);
        }
        pthread_cond_signal(&my_cond); // 有数据可读时
                                       // 下买你的做法，无法清零 源缓冲区数据
        count--;
        write_allow++;
        printf("在<读> __data[%d]:>%d,arg:>%s\n", count, data[count], (char *)arg);
        usleep(100000); // 可以看出上锁后以一次次读还是 一次去全读
        pthread_mutex_unlock(&my_mutex);
    }
}
void *mutex_write(void *arg)
{

    int itmp = 1;
    while (1)
    {
        pthread_mutex_lock(&my_mutex);
        while (!write_allow || count > BUF_SIZE - 1)
        {
            pthread_cond_wait(&my_cond, &my_mutex);
        }
        pthread_cond_signal(&my_cond);
        data[count] = itmp++;
        /*count++运算尽量不要在printf中与count 一起使用 */
        printf("在<写> __data[%d]:>%d,arg:>%s\n", count, data[count], (char *)arg);
        count++;
        write_allow--;
        usleep(100000);
        pthread_mutex_unlock(&my_mutex);
    }
}

int main(int argc, const char **argv)
{
    pthread_t tid_w0, tid_r0;
    pthread_create(&tid_w0, NULL, mutex_write, (void *)"write1");
    pthread_create(&tid_r0, NULL, mutex_read, (void *)"read3");
    sleep(2);
    // 使用pthread_join 会挂起等在子线程结束，才会结束父线程
    pthread_join(tid_w0, NULL);
    pthread_join(tid_r0, NULL);

    return 0;
}
