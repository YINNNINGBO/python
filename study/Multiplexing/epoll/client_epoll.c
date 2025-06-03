//_________________________客户端————————————————————————————————
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>

int main(int arcg, const char *argv[])
{
    // 1. 创建用于通信的套接字
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
    {
        perror("socket");
        exit(0);
    }

    // 2. 连接服务器
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;                         // ipv4
    addr.sin_port = htons(8888);                       // 服务器监听的端口, 字节序应该是网络字节序
    addr.sin_addr.s_addr = inet_addr("192.168.1.215"); // INADDR_ANY  不能使用 inet_addr ；这个是转换字符串成网络32 bit 字节序，而 // INADDR_ANY 是一个宏，表示任意地址，通常用于服务器端绑定地址。
    int ret = connect(fd, (struct sockaddr *)&addr, (socklen_t)sizeof(addr));
    if (ret == -1)
    {
        perror("connect");
        printf("errno = %d\n", errno);
        exit(0);
    }
    // 通信
    puts("------------------------客户端开始通信------------------------");
    while (1)
    {
        // 读数据
        char recvBuf[1024];
        // 写数据
        // sprintf(recvBuf, "data: %d\n", i++);
        fgets(recvBuf, sizeof(recvBuf), stdin);
        write(fd, recvBuf, strlen(recvBuf) + 1);
        // 如果客户端没有发送数据, 默认阻塞
        read(fd, recvBuf, sizeof(recvBuf));
        printf("recv buf: %s\n", recvBuf);
        sleep(1);
    }

    return 0;
}