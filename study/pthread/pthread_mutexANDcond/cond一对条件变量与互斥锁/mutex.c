#include "user.h"

// 互斥锁静态初始化  相比与动态初始化  不需要手动释放
pthread_mutex_t my_read_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t my_read_cond = PTHREAD_COND_INITIALIZER;

pthread_mutex_t my_write_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t my_write_cond = PTHREAD_COND_INITIALIZER;

#define BUF_SIZE 5
static int data[BUF_SIZE];
static int count = 0; // 数组内索引
static int itmp;      // 这里使用全局变量 在read中添加《itmp = 1;》 可以做到  write5~1 read 1~5  的死循环
void *mutex_read(void *arg)
{
    while (1)
    {

        pthread_mutex_lock(&my_read_mutex);
        if (count == 0)
        { // 如果没有数据可读
            itmp = 1;
            pthread_cond_wait(&my_read_cond, &my_read_mutex);
        }
        // 下买你的做法，无法清零 源缓冲区数据
        count--;
        printf("在<读> __data[%d]:>%d,arg:>%s\n", count, data[count], (char *)arg);
        usleep(100000); // 可以看出上锁后以一次次读还是 一次去全读
        pthread_mutex_unlock(&my_read_mutex);
        pthread_cond_signal(&my_write_cond); // 有数据可读时
    }
}
void *mutex_write(void *arg)
{

    itmp = 1;
    while (1)
    {
        pthread_mutex_lock(&my_write_mutex);
        if (count > BUF_SIZE - 1)
        {
            pthread_cond_wait(&my_write_cond, &my_write_mutex);
        }

        data[count] = itmp++;
        /*count++运算尽量不要在printf中与count 一起使用 */
        printf("在<写> __data[%d]:>%d,arg:>%s\n", count, data[count], (char *)arg);
        count++;
        pthread_cond_signal(&my_read_cond);
        usleep(100000);
        pthread_mutex_unlock(&my_write_mutex);
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