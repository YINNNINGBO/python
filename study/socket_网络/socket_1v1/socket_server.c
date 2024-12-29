#include "user.h"
int main(int argc, const char **argv)
{
    puts("i am server!\n");
    int fd, fd_of_accept, error_sign = 0;
    char buf[BUF_SIZE];
    struct sockaddr_in myaddr;
    // 判断可执行文件传入参数数量
    do
    {
        if (argc < 3)
        {
            fprintf(stdout, "in server%s:参数数量不足\n", argv[0]);
            error_sign = 1;
            break;
        }
        // 创建套接字
        /* socket(协议族,套接字类型,一般为 0) */
        fd = socket(AF_INET, SOCK_STREAM, 0); // ipv4,tcp,动选择协议
        if (fd < 0)
        {
            perror("socket is failed! ");
            fprintf(stderr, "errno = %d", errno);
            error_sign = 1;
            break;
        }
        // 向 myaddr  内的ip  与   端口号赋值
        myaddr.sin_family = AF_INET;
        myaddr.sin_port = htons(atoi(argv[2]));                 //   将int 端口号  先转字符 在转网络（大端）字节序
        if (1 != inet_pton(AF_INET, argv[1], &myaddr.sin_addr)) // 将IP号以ipv4 的标准修改 字节序
        {
            fprintf(stderr, "inet_aton is failed!,errno = %d\n", errno);
            error_sign = 1;
            break;
        }
        // 绑定通信结构体
        if (!!bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)))
        {
            fprintf(stderr, "bind is failed!,errno = %d\n", errno);
            error_sign = 1;
            break;
        }
        // 设置套接字监听模式
        if (!!listen(fd, BACKLOG))
        {
            // 设置可监听的数量
            fprintf(stderr, "listen is failed!,errno = %d\n", errno);
            error_sign = 1;
            break;
        }
        // 接受客户端连接请求
        fd_of_accept = accept(fd, NULL, NULL);
        if (fd_of_accept < 0)
        {
            fprintf(stderr, "accpet is failed!,errno = %d\n", errno);
            error_sign = 1;
            break;
        }
    } while (0);
    // 错误处理
    if (1 == error_sign)
    {
        _exit(EXIT_FAILURE);
    }
    // 处理客户端数据
    while (1)
    {
        memset(buf, 0, BUF_SIZE);
        if (read(fd_of_accept, buf, BUF_SIZE) < 0)
        {
            perror("read id failed !\n");
            exit(0);
        }
        puts(buf);
    }
    // 关闭文件描述符
    close(fd_of_accept);
    close(fd);
    return 0;
}

//./socket_server  127.0.0.1 8888