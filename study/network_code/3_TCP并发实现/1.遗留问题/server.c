/**
 * 服务端代码  循环接收客户端发来的数据
 *
 */
#include "head.h"
#define LISTEN_NUM 5 ///< 监听队列的长度
int main(int argc, const char *argv[])
{
    static int sock_fd, conn_fd;
    char buff[100]; // 缓冲区
    // 先判断参数是否合法 =3 ./server
    if (argc != 3)
    {
        fprintf(stdout, "%s <ip_addr> <port>\n", argv[0]);
        exit(0);
    }
    do
    {
        // 定义一个socket
        sock_fd = socket(AF_INET, SOCK_STREAM, 0); // ipv4 tcp
        if (sock_fd < 0)
        {
            fprintf(stderr, "socket failed , errno:%d\n", errno);
            exit(-1);
        }
        // 设置端口复用
        /*当前阶段不建议频繁使用
        目的(purpose)：解决当前先关闭服务端再关闭客户端后，再次使用出现的端口被占用的问题*/
        int opt = 1;
        setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
        // 定义一个地址结构体
        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(atoi(argv[2])); // 端口号
        if (inet_aton(argv[1], &server_addr.sin_addr) == 0)
        {
            fprintf(stderr, "Invalid address\n"); // ip地址
            exit(EXIT_FAILURE);
        }
        if (!!bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)))
        {
            fprintf(stderr, "bind is failed!,errno = %d\n", errno);
            exit(-1);
        }
        // 监听
        if (listen(sock_fd, LISTEN_NUM) < 0)
        {
            fprintf(stderr, "listen failed, errno:%d\n", errno);
            exit(-1);
        }
        // 建立连接
        conn_fd = accept(sock_fd, (struct sockaddr *)NULL, NULL);
        if (conn_fd < 0)
        {
            fprintf(stderr, "accept failed, errno:%d\n", errno);
            exit(-1);
        }
    } while (0);
    puts("*******************连接成功 ，接收发送的数据:*******************\n");

    // 循环接收数据
    while (1)
    {
        memset(buff, 0, sizeof(buff));
        int ret = read(conn_fd, buff, sizeof(buff));
        if (ret < 0)
        {
            fprintf(stderr, "read failed, errno:%d\n", errno);
            exit(-1);
        }
        else if (ret == 0)
        {
            fprintf(stderr, "server close\n");
            break;
        }
        else
        {
            fprintf(stdout, "recv data: %s\n", buff);
        }
        // 打印数据
    }

    // 关闭连接
    close(sock_fd);
    close(conn_fd);
    return 0;
}

/*
linux@linux-vir--mac:~/Desktop/gitee_linux_c/study/network_code/2_server_clinet$ ./server 0 8888
*******************连接成功 ，接收发送的数据:*******************

recv data: The World!!!
*/