/*
    UNIX 域套接字（Unix Domain Socket, UDS）是一种 进程间通信（IPC） 机制，
    它与 网络套接字（TCP/UDP） 类似，但它们的通信范围仅限于 本地系统，不经过网络传输。
    因此，它不需要 IP 地址和端口号。

    <UNIX 流式套接字>
    如果需要循环，则可以添加循环，每次accept后，将cfd保存到数组中，然后循环遍历数组，进行读写操作
    当前程序 ，只有一个accept，没有循环，所以只能连接一个客户端
    这种当客户端关闭连接时，服务器会关闭连接，如果需要服务器主动关闭连接，则需要在客户端关闭连接时，服务器也关闭连接
*/
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

#define MY_SOCK_PATH "/tmp/somepath"
#define LISTEN_BACKLOG 50

#define handle_error(msg)             \
    do                                \
    {                                 \
        printf("errno: %d ;", errno); \
        perror(msg);                  \
        exit(EXIT_FAILURE);           \
    } while (0);
char buf[BUFSIZ];
void signal_handler(int signo)
{
    // 截收ctrl+c信号，删除套接字文件s
    if (signo == SIGINT)
    {

        system("sudo rm /tmp/somepath"); // 删除套接字文件
        unlink(MY_SOCK_PATH);
        exit(signo);
    }
}

int main(int argc, const char *argv[])
{
    int sfd, cfd;
    struct sockaddr_un my_addr, peer_addr;
    socklen_t peer_addr_size;
    signal(SIGINT, signal_handler); // 使用信号处理删除套接字文件

    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sfd == -1)
    {
        handle_error("socket");
    }

    memset(&my_addr, 0, sizeof(my_addr));
    /* Clear structure */
    my_addr.sun_family = AF_UNIX;
    strncpy(my_addr.sun_path, MY_SOCK_PATH, sizeof(my_addr.sun_path) - 1); // 指定套接字文件路径

    if (bind(sfd, (struct sockaddr *)&my_addr, sizeof(my_addr)) == -1)
    {
        handle_error("bind");
    }

    if (listen(sfd, LISTEN_BACKLOG) == -1)
    {
        handle_error("listen");
    }
    peer_addr_size = sizeof(peer_addr);
    cfd = accept(sfd, (struct sockaddr *)&peer_addr, &peer_addr_size);
    if (cfd == -1)
    {
        handle_error("accept");
    }
    else
    {
        fputs("accpet is success\n", stdout);
        fflush(stdout);
        while (1)
        {
            if (!recv(cfd, buf, sizeof(buf), 0))
            {
                break;
            }
            printf("get data: %s\n", buf);
        }
    }
    close(cfd);
    close(sfd);
    unlink(MY_SOCK_PATH);
    return 0;
}