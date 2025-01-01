#include "user.h"
/*           对同一共享资源的read write 使用 两种锁的缺点
    因为在write中的锁对read没有影响，故出现对资源出现了竟态的形象
    eg:  当write过后 data[count]更新后； count++没有被下次write使用，反而被read
    例如打印中的
            在<写> __data[1]:>22,arg:>write1
            在<读> __data[2]:>0,arg:>read3
            在<读> __data[1]:>22,arg:>read3
*/
// 互斥锁静态初始化  相比与动态初始化  不需要手动释放
pthread_mutex_t read_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t my_read_cond = PTHREAD_COND_INITIALIZER;

pthread_mutex_t write_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t my_write_cond = PTHREAD_COND_INITIALIZER;

#define BUF_SIZE 5
static int data[BUF_SIZE];
static int count = 0; // 数组内索引
// static int write_allow = 1; //=1:允许写， =0：允许读   作为是否阻塞线程的标志位
void *mutex_read(void *arg)
{
    while (1)
    {

        pthread_mutex_lock(&read_lock);
        while (!count)
        { // 如果没有数据可读
            pthread_cond_wait(&my_read_cond, &read_lock);
        }
        // 下买你的做法，无法清零 源缓冲区数据
        printf("在<读> __data[%d]:>%d,arg:>%s\n", count, data[count], (char *)arg);
        count--;
        usleep(100000); // 可以看出上锁后以一次次读还是 一次去全读
        // write_allow++;
        if (count == BUF_SIZE - 1)
        {
            pthread_cond_signal(&my_write_cond);
        }

        pthread_mutex_unlock(&read_lock);
    }
}
void *mutex_write(void *arg)
{
    unsigned int itmp = 1;
    while (1)
    {
        pthread_mutex_lock(&write_lock);
        while (count > BUF_SIZE - 1)
        {
            pthread_cond_wait(&my_write_cond, &write_lock);
        }

        data[count] = itmp++;
        /*count++运算尽量不要在printf中与count 一起使用 */
        printf("在<写> __data[%d]:>%d,arg:>%s\n", count, data[count], (char *)arg);
        count++;
        usleep(100000);
        // write_allow = 0;
        pthread_cond_signal(&my_read_cond);
        pthread_mutex_unlock(&write_lock);
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
/**               打印结果  目的是两个线程随意打印
 *                 现象： 打印出现 索引 异常问题
 * ./mutex
在<写> __data[0]:>1,arg:>write1
在<写> __data[1]:>2,arg:>write1
在<读> __data[2]:>0,arg:>read3
在<写> __data[1]:>3,arg:>write1
在<读> __data[2]:>0,arg:>read3
在<写> __data[1]:>4,arg:>write1
在<读> __data[2]:>0,arg:>read3
在<写> __data[1]:>5,arg:>write1
在<读> __data[1]:>5,arg:>read3
在<读> __data[1]:>5,arg:>read3
在<写> __data[1]:>6,arg:>write1
在<读> __data[1]:>6,arg:>read3
在<写> __data[0]:>7,arg:>write1
在<读> __data[1]:>6,arg:>read3
在<写> __data[0]:>8,arg:>write1
在<读> __data[1]:>6,arg:>read3
在<写> __data[0]:>9,arg:>write1
在<读> __data[1]:>6,arg:>read3
在<写> __data[0]:>10,arg:>write1
在<写> __data[1]:>11,arg:>write1
在<读> __data[2]:>0,arg:>read3
在<写> __data[1]:>12,arg:>write1
在<读> __data[2]:>0,arg:>read3
在<写> __data[1]:>13,arg:>write1
在<读> __data[2]:>0,arg:>read3
在<写> __data[1]:>14,arg:>write1
在<读> __data[2]:>0,arg:>read3
在<读> __data[1]:>14,arg:>read3
在<写> __data[0]:>15,arg:>write1
在<读> __data[1]:>14,arg:>read3
在<写> __data[0]:>16,arg:>write1
在<读> __data[1]:>14,arg:>read3
在<写> __data[0]:>17,arg:>write1
在<读> __data[1]:>14,arg:>read3
在<写> __data[0]:>18,arg:>write1
在<读> __data[1]:>14,arg:>read3
在<写> __data[0]:>19,arg:>write1
在<读> __data[1]:>14,arg:>read3
在<写> __data[0]:>20,arg:>write1
在<读> __data[1]:>14,arg:>read3
在<写> __data[0]:>21,arg:>write1
在<写> __data[1]:>22,arg:>write1
在<读> __data[2]:>0,arg:>read3
在<读> __data[1]:>22,arg:>read3
在<写> __data[0]:>23,arg:>write1
在<读> __data[1]:>22,arg:>read3
在<写> __data[1]:>24,arg:>write1
在<读> __data[1]:>24,arg:>read3
在<写> __data[0]:>25,arg:>write1
在<读> __data[1]:>24,arg:>read3
在<写> __data[0]:>26,arg:>write1
在<读> __data[1]:>24,arg:>read3
在<写> __data[1]:>27,arg:>write1
在<读> __data[1]:>27,arg:>read3
在<写> __data[0]:>28,arg:>write1
在<读> __data[1]:>27,arg:>read3
在<写> __data[1]:>29,arg:>write1
在<读> __data[1]:>29,arg:>read3
在<写> __data[0]:>30,arg:>write1
在<读> __data[1]:>29,arg:>read3
在<写> __data[0]:>31,arg:>write1
在<读> __data[1]:>29,arg:>read3
在<写> __data[0]:>32,arg:>write1
^Cmake: *** 正在删除文件“mutex”
make: *** [Makefile:6: mutex] 中断

*/