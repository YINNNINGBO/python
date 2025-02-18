/*
    UNIX 域套接字（Unix Domain Socket, UDS）是一种 进程间通信（IPC） 机制，
    它与 网络套接字（TCP/UDP） 类似，但它们的通信范围仅限于 本地系统，不经过网络传输。
    因此，它不需要 IP 地址和端口号。
    <UNIX 数据报套接字>  UNIX　域套接字（Unix Domain Socket, UDS）是一种 进程间通信（IPC） 机制，
    它与 网络套接字（TCP/UDP） 类似，但它们的通信范围仅限于 本地系统，不经过网络传输。
    因此，它不需要 IP 地址和端口号。
    不同于TCP ,客户端关闭后，服务端依然可以接收数据，但服务端关闭后，客户端无法发送数据
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
    int sfd;
    struct sockaddr_un my_addr, peer_addr;
    socklen_t peer_addr_size;
    signal(SIGINT, signal_handler); // 使用信号处理删除套接字文件

    sfd = socket(AF_UNIX, SOCK_DGRAM, 0);
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

    // if (listen(sfd, LISTEN_BACKLOG) == -1)
    // {
    //     handle_error("listen");
    // }
    // peer_addr_size = sizeof(peer_addr);
    // cfd = accept(sfd, (struct sockaddr *)&peer_addr, &peer_addr_size);
    // if (cfd == -1)
    // {
    //     handle_error("accept");
    // }
    else
    {

        fputs("accpet is success\n", stdout);
        fflush(stdout);
        peer_addr_size = sizeof(peer_addr);
        while (1)
        {
            int tmp_ret = recvfrom(sfd, buf, BUFSIZ, 0, (struct sockaddr *)&peer_addr, (socklen_t *)&peer_addr_size);
            if (tmp_ret == 0)
            {
                break;
            }
            else if (tmp_ret == -1)
            {
                handle_error("recvfrom");
            }
            printf("get data: %s\n", buf);
        }
    }
    close(sfd);
    unlink(MY_SOCK_PATH);
    return 0;
}