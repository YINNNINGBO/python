#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main()
{
    int server_fd, client_fd;
    struct sockaddr_in addr;
    char buffer[100];

    // 创建套接字
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // 绑定套接字到 IP 地址和端口
    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);
    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1)
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

    return 0;
}

/*
./server
服务器正在等待连接...
接收到数据: Hello from client!
*/