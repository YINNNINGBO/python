/**
 * @file socket.c
 * @brief 使用select函数实现TCP服务器端的基本框架
 * @author Yin
 */
#include <stdio.h>
#include <string.h>
#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <sys/select.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> // close
#include <stdlib.h>

#define server_port 8888          // 端口号
#define server_ip "192.168.1.215" // 服务器IP地址
#define MY_DEBUG(exp, msg)                                                     \
    do                                                                         \
    {                                                                          \
        if (exp)                                                               \
        {                                                                      \
            perror(msg);                                                       \
            fprintf(stderr, " [%s:%d] errno=%d\n", __FILE__, __LINE__, errno); \
            exit(-1);                                                          \
        }                                                                      \
    } while (0)

int main(int argc, const char *argv[])
{
    int server_fd, message_fd;                    // 服务器套接字， 通信套接字
    struct sockaddr_in listen_addr, message_addr; // 服务器的监听结构体， 通信结构体
    char arr_buf[1028] = {0};                     // 用于存储接收的数据
    do
    {
        // 1. 创建套接字
        server_fd = socket(AF_INET, SOCK_STREAM, 0); // ipv4协议，TCP协议
        MY_DEBUG(server_fd < 0, "socket error");

        // 2. 绑定服务器ip
        memset(&listen_addr, 0, sizeof(listen_addr));                                                                 // 清空结构体
        listen_addr.sin_family = AF_INET;                                                                             // ipv4协议
        listen_addr.sin_port = htons(server_port);                                                                    // 端口号转换为网络字节序
        listen_addr.sin_addr.s_addr = inet_addr(server_ip);                                                           // IP地址转换为网络字节序
        MY_DEBUG(inet_pton(AF_INET, server_ip, &listen_addr.sin_addr) != 1, "inet_pton");                             // 另一种IP地址转换方式
        MY_DEBUG(bind(server_fd, (const struct sockaddr *)&listen_addr, (socklen_t)sizeof(listen_addr)) < 0, "bind"); // 绑定端口
        printf("server connected: %s:%d\n", inet_ntoa(listen_addr.sin_addr), ntohs(listen_addr.sin_port));            // 打印客户端IP地址和端口号
                                                                                                                      // 打印服务器IP地址和端口号
        // 3. 监听端口
        MY_DEBUG(listen(server_fd, 5) < 0, "listen error"); // 监听端口，最大连接数为5

        // 4. 建立连接
        socklen_t message_addr_len = sizeof(message_addr);                                                   // 定义通信地址长度
        message_fd = accept(server_fd, (struct sockaddr *)&message_addr, &message_addr_len);                 // 等待客户端连接
        MY_DEBUG(message_fd < 0, "accept error");                                                            // 接受连接请求
        printf("Client connected: %s:%d\n", inet_ntoa(message_addr.sin_addr), ntohs(message_addr.sin_port)); // 打印客户端IP地址和端口号
        while (1)
        {
            memset(arr_buf, 0, 1028);
            // 这里 <= 0 是为了防止客户端断开连接时，read函数返回0 然后进入死循环

            if (read(message_fd, arr_buf, 1028) <= 0)
            {
                perror("read id failed !\n");
                exit(0);
                close(server_fd);
                close(message_fd); // 关闭套接字
            }
            puts(arr_buf);
        }
        close(server_fd);
        close(message_fd); // 关闭套接字
    } while (0);

    return 0;
}
