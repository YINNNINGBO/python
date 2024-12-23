#include "user.h"

// 信号处理函数
void signal_handler(int signum)
{
    puts("信号处理函数被调用!\n");
    exit(signum); // 没有这句话   SIGINT  就不能用 ctrl C 关闭
}

int main(int argc, const char **argv)
{

    if (signal(SIGINT, signal_handler) == SIG_ERR)
    {
        perror("signal is failed");
        fprintf(stderr, "Error code: %d\n", errno); // 输出错误码
        _exit(EXIT_FAILURE);
    }
    while (1)
    {
        sleep(1);
        puts("你好!\n");
    }
    return 0;
}