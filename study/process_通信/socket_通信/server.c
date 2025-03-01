/*
1. Socket 的基本概念
    Socket 是一种通信机制，允许进程通过网络或本地进行数据交换。
    UNIX 域套接字：用于同一台机器上的进程通信，性能更高。
    网络套接字：用于不同机器上的进程通信，基于 TCP 或 UDP 协议。
2. 使用 UNIX 域套接字进行进程间通信
2.1 服务器端（接收数据）
    创建套接字。
    绑定套接字到本地文件。
    监听连接请求。
    接受客户端连接。
    接收数据并处理。
    关闭连接。
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/my_socket"

int main()
{
    int server_fd, client_fd;
    struct sockaddr_un addr;
    char buffer[100];

    // 创建套接字
    // 使用AF_UNIX协议族，SOCK_STREAM类型，协议为0（默认TCP）
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd == -1)
    {
        // 如果创建套接字失败，输出错误信息并退出程序
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // 绑定套接字到本地文件
    // 清空addr结构体
    memset(&addr, 0, sizeof(struct sockaddr_un));
    // 设置地址族为AF_UNIX
    addr.sun_family = AF_UNIX;
    // 将SOCKET_PATH复制到addr.sun_path中，注意留出终止符的位置
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);
    unlink(SOCKET_PATH); // 如果文件已存在，先删除
    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1)
    {
        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 监听连接请求
    if (listen(server_fd, 5) == -1)
    {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("服务器正在等待连接...\n");

    // 接受客户端连接
    client_fd = accept(server_fd, NULL, NULL);
    if (client_fd == -1)
    {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 接收数据
    ssize_t num_bytes = read(client_fd, buffer, sizeof(buffer));
    if (num_bytes == -1)
    {
        perror("read");
    }
    else
    {
        buffer[num_bytes] = '\0';
        printf("接收到数据: %s\n", buffer);
    }

    // 关闭连接
    close(client_fd);
    close(server_fd);
    unlink(SOCKET_PATH); // 删除套接字文件

    return 0;
}

/*
linux@linux-vir--mac:~/Desktop/gitee_linux_c/study/process_通信/socket_通信$ ./server
服务器正在等待连接...
接收到数据: Hello from client!
*/