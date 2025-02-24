#include "tcp.h"

int main(int argc, const char *argv[])
{
    ARGC_NUM(argc);                             // 参数个数判断
    p_tcp str_tcp = (p_tcp)malloc(sizeof(tcp)); // 分配内存
    bzero(str_tcp, sizeof(tcp));                // 清零
    while (!my_socket(str_tcp, SERVER, argv))
        ; // 创建套接字   失败继续创建
    socklen_t addr_len = sizeof(str_tcp->client_addr);
    if ((str_tcp->fd_for_client = accept(str_tcp->fd, (struct sockaddr *)&str_tcp->client_addr, &addr_len)) < 0) // 接受连接
    {
        ERROR_EXIT("accept");
    }
    // 接收数据 并打印
    while (1)
    {
        if (my_recv(str_tcp) == 0)
        {
            close(str_tcp->fd_for_client);
            break;
        }
    }

    // 关闭套接字
    close(str_tcp->fd);
    close(str_tcp->fd_for_client);
    free(str_tcp);
    return 0;
}
