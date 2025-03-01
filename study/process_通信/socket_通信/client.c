#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/my_socket"

int main()
{
    int client_fd;
    struct sockaddr_un addr;
    const char *message = "Hello from client!";

    // 创建套接字
    client_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_fd == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // 连接到服务器
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);
    if (connect(client_fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1)
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
linux@linux-vir--mac:~/Desktop/gitee_linux_c/study/process_通信/socket_通信$ ./client
数据已发送
*/