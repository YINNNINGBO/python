/**
 * @file UDP_client.c  UDP client
 */
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
char buf[BUFSIZE];
int main(int argc, const char *argv[])
{
    int sockfd;
    struct sockaddr_in server_addr; // 用于接收服务器端地址信息
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    socklen_t server_addr_len = sizeof(server_addr);

    // 创建socket   udp:SOCK_DGRAM( 数据报套接字)  tcp:SOCK_STREAM(流式套接字)
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        fprintf(stderr, "socket error! %s\n", strerror(errno));
        exit(1);
    }
    // 绑定地址

    bzero(&client_addr, sizeof(client_addr)); // 初始化清零
    bzero(&server_addr, sizeof(server_addr)); // 初始化清零

    // 导入服务器端口号和ip
    server_addr.sin_port = htons(atoi(argv[2])); // 客户端端口
    // 客户端ip
    if (inet_aton(argv[1], &server_addr.sin_addr) <= 0)
    {
        fprintf(stderr, "inet_pton error for %s\n", argv[1]);
        exit(1);
    }
    fputs("********************************************clinet****************************************\n", stdout);
    while (1)
    {
        // 数据发送
        bzero(buf, BUFSIZE); // 缓冲区清零
        fflush(stdout);
        scanf("%s", buf); // 从键盘输入数据
        printf("you input :%s,len: %ld \n", buf, strlen(buf));
        if (sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&server_addr, server_addr_len) <= 0)
        {
            fprintf(stderr, "sendto error! %s\n", strerror(errno));
            exit(1);
        }
        // sendto(sockfd, (void *)buf, strlen(buf) + 1, 0, (struct sockaddr *)&server_addr, server_addr_len);
        // 数据接收
        bzero(buf, BUFSIZE); // 清空缓冲区
        int ret_num = recvfrom(sockfd, buf, BUFSIZE, 0, (struct sockaddr *)&server_addr, &server_addr_len);
        if (ret_num == -1)
        {
            fprintf(stderr, "recvfrom error! %s\n", strerror(errno));
            exit(1);
        }
        else if (0 == ret_num)
        {
            fprintf(stderr, "server close\n");
            break;
        }
        else
        {
            // 数据成功接收
            printf("server ip: %s; port:%d; buf = %s\n", inet_ntoa(server_addr.sin_addr), ntohs(server_addr.sin_port), buf);
        }
    }

    // 关闭socket
    close(sockfd);
    return 0;
}

/*
linux@linux-vir--mac:~/Desktop/gitee_linux_c/study/network_code/4_UDP通信$ ./UDP_client 127.0.0.1 8888
********************************************clinet****************************************
fghjkl
you input :fghjkl,len: 6
server ip: 127.0.0.1; port:8888; buf = server success get data
*/