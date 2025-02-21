#include "main.h"
/* 创建套接字 并绑定地址 并监听
 * 参数 **argv
 */

// 服务端 函数
void create_socket(const char **arg)
{
    // 创建套接字
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd < 0)
    {
        ERRR_EXIT("socket");
    }

    // 绑定地址
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(atoi(arg[2]));
    bzero(&saddr.sin_addr, sizeof(saddr.sin_addr));
    if (!inet_aton(arg[1], &saddr.sin_addr))
    {
        fprintf(stderr, "Invalid address\n");
        exit(EXIT_FAILURE);
    }
    if (bind(sfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
    {
        close(sfd);
        ERRR_EXIT("bind");
    }
    // 监听
    if (listen(sfd, 10) < 0)
    {
        close(sfd);
        ERRR_EXIT("listen");
    }
}

// 接受连接  成功返回客户端信息 失败返回NULL
P_caddr my_accpet(int fd)
{
    P_caddr p_client = (P_caddr)malloc(sizeof(caddr));
    // 接受连接
    bzero(&p_client->caddr, sizeof(p_client->caddr));
    p_client->client_len = sizeof(p_client->caddr);
    if ((p_client->for_client_fd = accept(fd, (struct sockaddr *)&p_client->caddr, &p_client->client_len)) < 0)
    {
        my_free(p_client);
        ERRR_EXIT("accept");
    }
    else
    {
        printf("get client:%s\n", inet_ntoa(p_client->caddr.sin_addr));
        return p_client;
    }
}
// 接收客户端信息
int recv_client_msg(int fd)
{
    while (1)
    {
        memset(buf, 0, sizeof(buf));
        ssize_t tmp_ret = recv(fd, buf, sizeof(buf), 0);
        if (tmp_ret < 0)
        {
            ERRR_EXIT("recv");
        }
        else if (tmp_ret == 0)
        {
            printf("client close\n");
            close(fd); // 客户端关闭连接  关闭文件描述符
            return 0;
        }
        else
        {
            if (strcmp(buf, "exit\n") == 0)
            { // 检测师傅是要退出
                printf("client exit\n");
                close(fd);
            }
            else
            {
                printf("get  client msg:%s\n", buf);
            }
        }
    }
}
// 释放客户端指针
void my_free(P_caddr p_client)
{
    // 关闭客户端文件描述符
    close(p_client->for_client_fd);
    // 释放客户端指针
    free(p_client);
    // 将客户端指针置为空
    p_client = NULL;
}