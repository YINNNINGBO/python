#include "user.h"

int main(int argc, const char **argv)
{
    // 打开消息队列
    struct mq_attr my_attr;
    my_attr.mq_maxmsg = MAX_M_NUM;      // 10
    my_attr.mq_msgsize = MAX_ONE_M_len; // 50
    my_attr.mq_flags = 0;
    my_attr.mq_curmsgs = 0;
    mqd_t mq = mq_open(PATH_MQ, O_RDONLY, &my_attr);
    if (mq == (mqd_t)-1)
    {
        perror("read mq_open failed");
        fprintf(stderr, "Error code: %d\n", errno);
        _exit(EXIT_FAILURE);
    }

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
    // 清楚消息队列文件
    mq_close(mq);
    return 0;
}