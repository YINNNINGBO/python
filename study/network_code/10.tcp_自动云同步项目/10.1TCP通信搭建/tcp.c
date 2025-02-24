#include "tcp.h"
char buf[BUF_SIZE] = {0}; // 缓冲区

/*if this file is server.c socket->listen ;if this file is client.c socket->connect
 *   ptcp: 通信结构体
 *   server_or_client: 1= server ；2= client
 *  @return: 通信套接字  0:fail
 */
int my_socket(p_tcp ptcp, int server_or_client, const char *t_argv[])
{
    // 生成套接字
    if ((ptcp->fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
        return 0;
    }
    // 设置地址重用
    int opt = 1;
    setsockopt(ptcp->fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (server_or_client == SERVER) // 如果当前是服务器
    {
        // 设置服务器地址
        ptcp->server_addr.sin_family = AF_INET;                             // 协议族
        ptcp->server_addr.sin_port = htons(PORT);                           // 端口号
        if (inet_pton(AF_INET, t_argv[1], &ptcp->server_addr.sin_addr) < 0) // IP地址
        {
            ERROR_EXIT("servre inet_pton");
        }
        if (bind(ptcp->fd, (struct sockaddr *)&ptcp->server_addr, (socklen_t)sizeof(ptcp->server_addr)) < 0)
        {
            ERROR_EXIT("bind");
        }
        if (listen(ptcp->fd, 5) < 0)
        {
            ERROR_EXIT("listen");
        }
    }
    else if (server_or_client == CLIENT) // 如果当前是客户端
    {
        // 设置服务器地址
        ptcp->server_addr.sin_family = AF_INET;                             // 协议族
        ptcp->server_addr.sin_port = htons(PORT);                           // 端口号
        if (inet_pton(AF_INET, t_argv[1], &ptcp->server_addr.sin_addr) < 0) // IP地址
        {
            ERROR_EXIT("client inet_pton");
        }
        if (connect(ptcp->fd, (struct sockaddr *)&ptcp->server_addr, (socklen_t)sizeof(ptcp->server_addr)) < 0)
        {
            ERROR_EXIT("connect");
        }
    }
    return ptcp->fd;
}

/**
 * @breif: 服务端接收客户端的连接
 * @参数： ptcp: 通信结构体
 * @return :  sucess=1; fail=0
 */
int my_recv(p_tcp ptcp)
{
    int ret = 0;
    do
    {
        ret = recv(ptcp->fd_for_client, buf, BUF_SIZE, 0);
    } while (ret == 0 && ret == EINTR);
    if (ret < 0)
    {
        ERROR_EXIT("recv");
    }
    else if (ret == 0)
    {

        printf("client close \n");
        return 0;
    }
    else
    {
        // 打印客户端IP地址和发送的数据
        printf("client ip :%s;send str:%s\n", inet_ntoa(ptcp->client_addr.sin_addr), buf);
    }
    return ret;
}

/**
 * @breif: 客户端接收客户端的连接
 * @return :  sucess=1; fail=0
 */
int my_send(p_tcp ptcp, const char *str, int len)
{
    int ret = 0;
    if ((ret = send(ptcp->fd, str, len, 0)) < 0)
    {
        ERROR_EXIT("send");
    }
    return 0;
}
