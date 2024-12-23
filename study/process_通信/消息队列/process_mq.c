#include "user.h"
/**
 * 消息队列   实现父子进程间通信
 */

int main(int argc, const char **argv)
{
    // 创建消息队列队列文件
    //********************写的一方**********************
    struct mq_attr my_attr;

    my_attr.mq_maxmsg = MAX_M_NUM;      // 10
    my_attr.mq_msgsize = MAX_ONE_M_len; // 50
    my_attr.mq_flags = 0;
    my_attr.mq_curmsgs = 0;
    mqd_t mq = mq_open(PATH_MQ, O_RDWR | O_CREAT, 0666, &my_attr);
    if (mq == (mqd_t)-1)
    {
        perror("mq_open failed");
        fprintf(stderr, "Error code: %d\n", errno);
        _exit(EXIT_FAILURE);
    }
    // 创建进程
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork is failed!");
        _exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        // 子进程
        char buf[MAX_ONE_M_len];
        // 设置超时时间（5秒后超时）
        struct timespec timeout;
        clock_gettime(CLOCK_REALTIME, &timeout); // 获取当前时间
        timeout.tv_sec += 5;                     // 设置超时为当前时间后 5 秒
        timeout.tv_nsec = 0;                     // 设置微妙等待为0
        for (int i = 0; i < 10; i++)
        {
            sleep(1);
            // 切记 这一类读取，接收数据的函数的参数中的长度是最大长度  不能用strlen
            if (mq_timedreceive(mq, buf, MAX_ONE_M_len, 0, &timeout) < 0)
            {
                perror("mq_timedsend is failed!!");
            }
            else
            {
                fprintf(stdout, "我是子进程,接收%s", buf);
            }
        }
    }
    else
    { // 父进程
        char buf[MAX_ONE_M_len];
        // 设置超时时间（5秒后超时）
        struct timespec timeout;
        clock_gettime(CLOCK_REALTIME, &timeout); // 获取当前时间
        timeout.tv_sec += 5;                     // 设置超时为当前时间后 5 秒
        timeout.tv_nsec = 0;                     // 设置微妙等待为0
        for (int i = 0; i < 10; i++)
        {
            sleep(1);
            sprintf(buf, "第:%d条信息,来自进程%d\n", i + 1, getpid());
            printf("buf size = %ld\n", strlen(buf));
            if (mq_timedsend(mq, buf, strlen(buf) + 1, 0, &timeout) < 0)
            {
                perror("mq_timedsend is failed!!");
            }
            // else
            // {
            //     printf("子进程接收到: %s\n", buf); // 打印接收到的消息
            // }
            memset(buf, 0, MAX_ONE_M_len);
        }
    }
    // 清楚消息队列文件
    mq_close(mq);
    // 清除消息队列
    mq_unlink(PATH_MQ);

    return 0;
}