#include "user.h"
int main(int argc, const char **argv)
{
    puts("i am client!\n");
    int fd, error_sign = 0;
    struct sockaddr_in myaddr;
    char buf[BUF_SIZE];
    do
    {
        if (argc < 3)
        {
            fprintf(stderr, "in cliend %s 参数不足\n", argv[0]);
            error_sign = 1;
            break;
        }
        // 创建套接字
        fd = socket(AF_INET, SOCK_STREAM, 0);
        if (fd < 0)
        {
            perror("socket is failed! ");
            fprintf(stderr, "errno = %d", errno);
            error_sign = 1;
            break;
        }
        // 设置ip地址与端口号
        myaddr.sin_family = AF_INET;
        myaddr.sin_port = htons(atoi(argv[2]));                 //   将int 端口号  先转字符 在转网络（大端）字节序
        if (1 != inet_pton(AF_INET, argv[1], &myaddr.sin_addr)) // 将IP号以ipv4 的标准修改 字节序
        {
            fprintf(stderr, "inet_pton is failed!,errno = %d\n", errno);
            error_sign = 1;
            break;
        }
        // 向服务器发起连接请求
        if (connect(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0)
        {
            fprintf(stderr, "connect is failed!,errno = %d\n", errno);
            error_sign = 1;
            break;
        }
    } while (0);
    if (error_sign)
    {
        _exit(EXIT_FAILURE);
    }
    // 向服务器发送信息
    puts("*******************连接成功 ，输入向服务器发送的数据:*******************\n");
    while (1)
    {
        fgets(buf, BUF_SIZE, stdin);
        if (write(fd, buf, strlen(buf)) < 0)
        {
            perror("write is error!!!\n");
            exit(-1);
        }
    }
    close(fd);
    return 0;
}

/**
 * ./socket_server  127.0.0.1 8888
 */