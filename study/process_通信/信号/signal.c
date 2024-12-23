#include "user.h"

// 信号处理函数
void signal_handler(int signum)
{
    puts("信号处理函数被调用!\n");
    return;
}

int main(int argc, const char **argv)
{
    // SIGNAL  是 ctrl c 信号
    // 用ps -elf | grep 当前执行文件 查看进程号
    //  然后  使用  kill -9  进程号   关闭可执行文件
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