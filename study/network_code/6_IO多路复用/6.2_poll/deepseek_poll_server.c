#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define MAX_CLIENTS 1024 // 最大客户端数量
#define BUFFER_SIZE 4096 // 接收缓冲区大小
#define PORT 8888        // 服务端口

int main()
{
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    struct pollfd fds[MAX_CLIENTS + 1]; // +1 用于监听套接字
    int nfds = 0;                       // 当前监控的文件描述符数量
    char buffer[BUFFER_SIZE];

    // 创建 TCP 套接字
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // 设置 SO_REUSEADDR 选项（避免端口占用）
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
    {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 绑定地址
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 监听
    if (listen(server_fd, 10) == -1)
    {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    // 初始化 pollfd 数组
    memset(fds, 0, sizeof(fds));
    fds[0].fd = server_fd;  // 监听套接字
    fds[0].events = POLLIN; // 监控可读事件
    nfds = 1;

    while (1)
    {
        // 调用 poll 等待事件
        int ret = poll(fds, nfds, -1); // -1 表示无限等待
        if (ret == -1)
        {
            if (errno == EINTR)
            {
                continue; // 被信号中断，重试
            }
            perror("poll");
            break;
        }

        // 处理所有触发的事件
        for (int i = 0; i < nfds; i++)
        {
            if (fds[i].revents == 0)
            {
                continue; // 无事件发生
            }

            // 检查是否为监听套接字的新连接
            if (fds[i].fd == server_fd)
            {
                // 接受新连接
                // 使用多路复用，所以这里不需要循环  一旦数据有来，就会触发
                client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
                if (client_fd == -1)
                {
                    perror("accept");
                    continue;
                }

                printf("New client connected: %s:%d\n",
                       inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

                // 将新客户端加入 pollfd 数组
                if (nfds >= MAX_CLIENTS + 1)
                {
                    fprintf(stderr, "Too many clients\n");
                    close(client_fd);
                    continue;
                }
                fds[nfds].fd = client_fd;
                fds[nfds].events = POLLIN;
                nfds++;
            }
            else
            {
                // 处理客户端数据
                ssize_t n = recv(fds[i].fd, buffer, BUFFER_SIZE, 0);
                if (n <= 0)
                {
                    // 客户端关闭连接或出错
                    if (n == 0)
                    {
                        printf("Client closed connection\n");
                    }
                    else
                    {
                        perror("recv");
                    }
                    close(fds[i].fd);
                    // 从 pollfd 数组中移除（将最后一个元素覆盖当前项）
                    fds[i] = fds[nfds - 1];
                    nfds--;
                    i--; // 重新检查当前位置
                }
                else
                {
                    // 回显数据给客户端
                    buffer[n] = '\0';
                    printf("Received: %s", buffer);
                    if (send(fds[i].fd, buffer, n, 0) == -1)
                    {
                        perror("send");
                    }
                }
            }
        }
    }

    // 关闭所有套接字
    for (int i = 0; i < nfds; i++)
    {
        close(fds[i].fd);
    }

    return 0;
}