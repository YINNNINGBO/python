#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main()
{
    int client_fd;
    struct sockaddr_in addr;
    const char *message = "Hello from client!";

    // 创建套接字
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // 连接到服务器
    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) <= 0)
    {
        perror("inet_pton");
        close(client_fd);
        exit(EXIT_FAILURE);
    }
    if (connect(client_fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1)
    {
        perror("connect");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    // 发送数据
    if (write(client_fd, message, strlen(message)) == -1)
    {
        perror("write");
    }
    else
    {
        printf("数据已发送\n");
    }

    // 关闭连接
    close(client_fd);

    return 0;
}

/*
./client
数据已发送
*/