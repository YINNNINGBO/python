#include "main.h"
/**
 * @file main.c
 * 程序效果：服务端通过io多路复用与多线程实现并发
 *
 * 遗留问题：line:44   puts("有客户端连接\n");    打印多次   原因未知 >>>>>>>
 */
// 全局变量

char buf[BUFSIZE] = {0}; // 缓冲区
int sfd, cfd;            // server_fd client_fd
struct sockaddr_in saddr;
void *pthread_handle(void *arg); // 线程处理函数
int main(int argc, const char **argv)
{
    P_caddr client_struct;
    P_fd_sets fd_sets = malloc(sizeof(fd_sets)); // 创建fd_sets结构体  用于向线程传递参数

    pthread_t tid;
    fd_set readfds; // 读文件描述符集合
    fd_set rd_tmp;
    if (argc != 3)
    {
        printf("Usage: %s <port> ,<ip>\n", argv[0]);
        exit(1);
    }
    create_socket(argv); // 创建套接字
    // 创建fd_set
    FD_ZERO(&readfds);
    FD_SET(sfd, &readfds); // 将sfd加入fd_set
    // 让内核监听sfd
    while (1)
    {
        rd_tmp = readfds;
        // 调用select函数  最后一个参数为NULL表示一直阻塞等待
        int ret = select(FD_SETSIZE, &rd_tmp, NULL, NULL, NULL);
        if (ret < 0)
        {
            ERRR_EXIT("select");
        }
        if (FD_ISSET(sfd, &rd_tmp)) // FD_ISSER判断当有客户端连接时，fd_set中sfd的值会发生变化，故使用初值
        {
            // 创建子线程
            puts("有客户端连接\n");
            fd_sets->fd = sfd; // 参数覆盖
            fd_sets->read_fds = readfds;
            fd_sets->tmp_fds = rd_tmp;
            fd_sets->struct_client = malloc(sizeof(caddr));              // 创建结构体
            pthread_create(&tid, NULL, pthread_handle, (void *)fd_sets); // 创建线程,并传入需要参数
            pthread_detach(tid);                                         // 线程分离
        }
    }
    my_free(client_struct); // 释放内存
    close(sfd);
    return 0;
}

// 线程处理 函数
void *pthread_handle(void *arg)
{
    P_fd_sets tmp_sets = (P_fd_sets)arg;

    tmp_sets->struct_client = my_accpet(sfd);
    FD_SET(tmp_sets->struct_client->for_client_fd, &tmp_sets->read_fds); // 将cfd加入初始fd_set
    for (int i = 0; i < FD_SETSIZE; i++)
    {
        if ((tmp_sets->struct_client->for_client_fd == i) &&
            (FD_ISSET(tmp_sets->struct_client->for_client_fd, &tmp_sets->read_fds)))
        {
            fputs("有数据待接收\n", stdout);
            if (!recv_client_msg(tmp_sets->struct_client->for_client_fd)) // 接收客户端消息
            {
                puts("客户端断开连接\n");
                FD_CLR(tmp_sets->struct_client->for_client_fd, &tmp_sets->read_fds); // 将cfd从fd_set中移除
                FD_CLR(tmp_sets->sfd, &tmp_sets->tmp_fds);                           // 关闭cfd
                // bzero(tmp_sets, sizeof(fd_sets));                                    // 清零内存
                //  pthread_exit(NULL);
            }
        }
    }

    return NULL;
}