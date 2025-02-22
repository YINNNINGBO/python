#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_EVENTS 10
#define BUFFER_SIZE 1024
#define PORT 8888

// 函数声明：setnonblocking
// 功能：将指定的文件描述符（套接字）设置为非阻塞模式
void setnonblocking(int sock)
{
    // 使用fcntl函数获取文件描述符的当前状态标志
    int opts = fcntl(sock, F_GETFL);
    // 如果获取失败，输出错误信息并退出程序
    if (opts < 0)
    {
        perror("fcntl(F_GETFL)");
        exit(EXIT_FAILURE);
    }
    // 将当前状态标志设置为非阻塞模式（O_NONBLOCK）
    opts = (opts | O_NONBLOCK);
    // 使用fcntl函数将新的状态标志设置回文件描述符
    if (fcntl(sock, F_SETFL, opts) < 0)
    {
        // 如果设置失败，输出错误信息并退出程序
        perror("fcntl(F_SETFL)");
        exit(EXIT_FAILURE);
    }
}

int main()
{
    int listen_sock, conn_sock, nfds, epollfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    struct epoll_event ev, events[MAX_EVENTS]; // evebts  存放就绪事件  在epoll_wait调用前是空的，调用后存放的是已经就绪的事件
    char buffer[BUFFER_SIZE];

    // 创建TCP socket
    if ((listen_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // 设置地址重用
    int opt = 1;
    setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 绑定地址
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    if (bind(listen_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("bind");
        close(listen_sock);
        exit(EXIT_FAILURE);
    }

    // 监听连接
    if (listen(listen_sock, SOMAXCONN) < 0)
    {
        perror("listen");
        close(listen_sock);
        exit(EXIT_FAILURE);
    }

    // 创建epoll实例
    epollfd = epoll_create1(0);
    if (epollfd == -1)
    {
        perror("epoll_create1"); //  如果创建epoll实例失败，打印错误信息
        exit(EXIT_FAILURE);
    }

    // 添加监听socket到epoll
    ev.events = EPOLLIN; //  设置事件类型为可读事件
    ev.data.fd = listen_sock;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listen_sock, &ev) == -1)
    {
        perror("epoll_ctl: listen_sock");
        exit(EXIT_FAILURE);
    }

    printf("Server running on port %d...\n", PORT);

    while (1)
    {
        nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        if (nfds == -1)
        {
            perror("epoll_wait");
            break;
        }
        /*遍历说有的就绪事件如果 = 监听套接字说明有新连接，
            如果=其他套接字，说明有数据可读
        */
        for (int n = 0; n < nfds; ++n)
        {
            if (events[n].data.fd == listen_sock)
            {
                // 处理新连接
                conn_sock = accept(listen_sock,
                                   (struct sockaddr *)&client_addr,
                                   &client_len);
                if (conn_sock < 0)
                {
                    perror("accept");
                    continue;
                }

                printf("New connection from %s:%d\n",
                       inet_ntoa(client_addr.sin_addr),
                       ntohs(client_addr.sin_port));
                // 设置通信套接字为非阻塞模式
                setnonblocking(conn_sock);                                   //  设置新连接的套接字为非阻塞模式
                ev.events = EPOLLIN | EPOLLET;                               //  设置epoll事件，监听可读事件和边缘触发模式
                ev.data.fd = conn_sock;                                      //  将新连接的套接字描述符与事件关联
                if (epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock, &ev) == -1) //  将新连接的套接字添加到epoll实例中
                {
                    perror("epoll_ctl: conn_sock"); //  如果添加失败，打印错误信息
                    close(conn_sock);               //  关闭新连接的套接字
                }
            }
            else
            {
                // 处理数据
                int fd = events[n].data.fd;
                ssize_t count;

                while ((count = read(fd, buffer, BUFFER_SIZE)) > 0)
                {
                    printf("Received: %.*s", (int)count, buffer);
                    if (write(fd, buffer, count) != count)
                    {
                        perror("write");
                        break;
                    }
                }

                if (count == 0)
                {
                    // 客户端关闭连接
                    printf("Client disconnected\n");
                    close(fd);
                }
                else if (count == -1 && errno != EAGAIN)
                {
                    perror("read");
                    close(fd);
                }
            }
        }
    }

    close(listen_sock);
    close(epollfd);
    return 0;
}
