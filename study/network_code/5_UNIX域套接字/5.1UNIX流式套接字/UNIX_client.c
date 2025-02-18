/*
    UNIX 域套接字（Unix Domain Socket, UDS）是一种 进程间通信（IPC） 机制，
    它与 网络套接字（TCP/UDP） 类似，但它们的通信范围仅限于 本地系统，不经过网络传输。
    因此，它不需要 IP 地址和端口号。
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

int main(int argc, const char *argv[])
{
    int fd;
    struct sockaddr_un peer_addr;
    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd == -1)
    {
        handle_error("socket");
    }

    memset(&peer_addr, 0, sizeof(peer_addr));
    /* Clear structure */
    peer_addr.sun_family = AF_UNIX;
    strncpy(peer_addr.sun_path, MY_SOCK_PATH, sizeof(peer_addr.sun_path) - 1); // 指定套接字文件路径

    if (connect(fd, (struct sockaddr *)&peer_addr, sizeof(peer_addr)) == -1)
    {
        handle_error("connect");
    }
    else
    {
        fputs("connet is success\n", stdout);
        // fflush(stdout);
        while (1)
        {
            fputs("input: ", stdout);
            // fflush(stdout); // 刷新缓冲区，否则可能不会立即输出
            scanf("%s", buf);
            if (strcmp(buf, "exit") == 0)
            { // 输入exit退出
                break;
            }
            if (send(fd, buf, sizeof(buf), 0) <= 0)
            {
                handle_error("send");
                break;
            }

            // printf("get data: %s\n", buf);
        }
    }
    close(fd);
    // system("sudo rm /tmp/somepath"); // 删除套接字文件
    unlink(MY_SOCK_PATH);
    return 0;
}
