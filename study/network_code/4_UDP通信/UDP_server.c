/**
 * UDP_server.c --  UDP server
 * sendto 与recvfrom 函数的最后两个参数都是对端的信息，是在使用 <可执行文件> <ip> <port> 时的后两个
 * 因为UDP不是向量连接的  所以开启先后没有要求
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <strings.h>
#define BUFSIZE 100
char buffer[BUFSIZ];
int main(int argc, const char *argv[])
{
    int sockfd;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr; // 用于接收客户端地址信息
    socklen_t client_addr_len = sizeof(client_addr);
    socklen_t server_addr_len = sizeof(server_addr);

    // 创建socket   udp:SOCK_DGRAM( 数据报套接字)  tcp:SOCK_STREAM(流式套接字)
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        fprintf(stderr, "socket error! %s\n", strerror(errno));
        exit(1);
    }
    // 绑定地址
    bzero(&server_addr, sizeof(server_addr)); // 初始化清零
    bzero(&client_addr, sizeof(client_addr)); // 初始化清零

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2])); // 服务器端口
    // 服务器IP
    if (inet_aton(argv[1], &server_addr.sin_addr) <= 0)
    {
        fprintf(stderr, "inet_pton error for %s\n", argv[1]);
        exit(1);
    }
    // 绑定地址
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        fprintf(stderr, "Bind error! %s\n", strerror(errno));
        exit(1);
    }
    fputs("********************************************server****************************************\n", stdout);

    while (1)
    {
        // recvfrom 最后的两个参数是客户端的地址信息
        int ret_num = recvfrom(sockfd, (void *)buffer, BUFSIZE, 0, (struct sockaddr *)&client_addr, &client_addr_len);
        if (ret_num == -1)
        {
            fprintf(stderr, "recvfrom error! %s\n", strerror(errno));
            exit(1);
        }
        else if (0 == ret_num)
        {
            fprintf(stderr, "client close\n");
            break;
        }
        else
        {
            printf("client ip: %s; port:%d; buf = %s\n",
                   inet_ntoa(client_addr.sin_addr),
                   ntohs(client_addr.sin_port), buffer);
            // 最后两个参数是客户端的地址信息
            sendto(sockfd, (void *)"server success get data\n", strlen("server success get data\n"), 0, (struct sockaddr *)&client_addr, client_addr_len);
        }
    }
    // 关闭socket
    close(sockfd);
    return 0;
}

/**
inux@linux-vir--mac:~/Desktop/gitee_linux_c/study/network_code/4_UDP通信$ ./UDP_server 0  8888
********************************************server****************************************
client ip: 127.0.0.1; port:56679; buf = fghjk

client ip: 127.0.0.1; port:56679; buf = fghjk
*/