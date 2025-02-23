#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BROADCAST_PORT 8888
#define BROADCAST_IP "255.255.255.255" // 是一个特殊的广播地址 表示去那是1 的广播地址

int main()
{
    int sockfd;
    struct sockaddr_in broadcast_addr;
    char *message = "Hello, this is a broadcast message!";

    // 1. 创建 UDP 套接字
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // 2. 设置广播选项
    int broadcast_enable = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast_enable, sizeof(broadcast_enable)) < 0)
    {
        perror("setsockopt");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    1
        // 3. 设置广播地址
        memset(&broadcast_addr, 0, sizeof(broadcast_addr));
    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_port = htons(BROADCAST_PORT);
    broadcast_addr.sin_addr.s_addr = inet_addr(BROADCAST_IP);

    // 4. 发送广播数据
    if (sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&broadcast_addr, sizeof(broadcast_addr)) < 0)
    {
        perror("sendto");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Broadcast message sent: %s\n", message);

    // 5. 关闭套接字
    close(sockfd);
    return 0;
}