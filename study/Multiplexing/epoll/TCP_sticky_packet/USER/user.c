#include "user.h"

int create_socket(int *fd, int port, const char *ip, int type)
{
    // 创建套接字
    *fd = socket(AF_INET, SOCK_STREAM, 0);
    IF_DEBUG((*fd < 0), "socket error");
    if (type)
    {
        // 服务器端
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = inet_addr(SERVER_IP); // 绑定到所有可用的接口
        // 绑定
        int ret = bind(*fd, (struct sockaddr *)&addr, sizeof(addr));
        IF_DEBUG((ret < 0), "bind error");
        // 设置监听
        ret = listen(*fd, LISTEN_LEN);
        IF_DEBUG((ret < 0), "listen error");
    }
    return 0;
}

int readn(int fd, char *buf, int size)
{
    char *pt = (char *)buf;
    int count = size;
    while (count > 0)
    {
        int len = recv(fd, pt, count, 0);
        if (len == -1)
        {
            return -1;
        }
        else if (len == 0)
        {
            return size - count;
        }
        pt += len;
        count -= len;
    }
    // printf("readn = %s\n", buf + 4);
    return size;
}
int recvMsg(int cfd, char **msg)
{
    // 接收数据
    // 1. 读数据头
    int len = 0;
    readn(cfd, (char *)&len, 4);
    len = ntohl(len);
    // printf("数据块大小: %d\n", len);

    // 根据读出的长度分配内存，+1 -> 这个字节存储\0
    char *buf1 = (char *)malloc(len + 1);
    int ret = readn(cfd, buf1, len);
    if (ret != len)
    {
        close(cfd);
        free(buf1);
        buf1 = NULL;
        return -1;
    }
    buf1[len] = '\0';
    memcpy(*msg, buf1, len);
    // free(buf);
    return ret;
}

int writen(int fd, const char *msg, int size)
{
    // printf("writen = %s\n", (const char *)msg + 4);
    const char *buf = msg;
    int count = size;
    while (count > 0)
    {
        int len = send(fd, buf, count, 0);
        if (len == -1)
        {
            close(fd);
            return -1;
        }
        else if (len == 0)
        {
            continue;
        }
        buf += len;
        count -= len;
    }

    // printf("line :%d ; sendn = %s\n", __LINE__, msg + 4);
    return size;
}

int sendMsg(int cfd, char *msg, int len)
{
    if (msg == NULL || len <= 0 || cfd <= 0)
    {
        return -1;
    }
    // printf("in sendMsg, msg = %s, len = %d\n", msg, len);
    //  申请内存空间: 数据长度 + 包头4字节(存储数据长度)
    char *data = (char *)malloc(len + 4);
    int bigLen = htonl(len);
    memcpy(data, &bigLen, 4);
    memcpy(data + 4, msg, len);
    // 发送数据
    // printf("sendMsg data = %s,len = %d\n", data + 4, ntohl(*(int *)(data + 0)));
    int ret = writen(cfd, data, len + 4);
    // 释放内存
    free(data);
    return ret;
}

int close_socket(int fd)
{
    IF_DEBUG((close(fd) < 0), "close error");
    fd = -1; // 将文件描述符设置为无效值
    return 0;
}

void del_end_enter(char buf[])
{

    if (buf[strlen(buf) - 1] == '\n')
    {
        buf[strlen(buf) - 1] = 0; // 替换为字符串结束符
    }
    return;
}
