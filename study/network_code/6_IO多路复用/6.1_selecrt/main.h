#ifndef __MAIN_H__
#define __MAIN_H__

#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <pthread.h>
// 错误提示宏
#define ERRR_EXIT(msg)                                             \
    do                                                             \
    {                                                              \
        perror(msg);                                               \
        printf("error: %d;at %s:%d\n", errno, __FILE__, __LINE__); \
        exit(EXIT_FAILURE);                                        \
    } while (0)

// 定义一个客户端地址结构体
// 存储通信套接字, 客户端地址, 客户端地址长度
typedef struct client_addr
{
    int for_client_fd;
    struct sockaddr_in caddr;
    socklen_t client_len;
} *P_caddr, caddr;

// 结构体 存储server_fd, read_fds, tmp_fds
typedef struct sfd_set
{
    int sfd, fd;     // 监听套接字与通信套接字
    fd_set read_fds; // 读事件集合
    fd_set tmp_fds;  // 临时事件集合
    P_caddr struct_client;
} *P_fd_sets, fd_sets;
/*外部变量*/
#define BUFSIZE 100
extern char buf[BUFSIZE]; // 缓冲区
extern int sfd, cfd;
extern struct sockaddr_in saddr;

// 自定义函数
void create_socket(const char **arg); // 创建套接字
P_caddr my_accpet(int fd);            // 接受客户端连接
int recv_client_msg(int fd);          // 接收客户端消息
void my_free(P_caddr p_client);       // 释放客户端地址结构体

#endif /* __MAIN_H__ */
