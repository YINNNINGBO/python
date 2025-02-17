/**
 * 实现多线程并发  服务端代码  循环接收客户端发来的数据
 */
#include "head.h"

#define LISTEN_NUM 5   ///< 监听队列的长度
static char buff[100]; // 缓冲区
void *rece_client_data(void *arg);
// 客户端地址  升级为全局变量
static struct sockaddr_in client_addr; // static 修饰的变量 作用是延长变量的生命周期，而非作用域，作用域仍然是局部的
static socklen_t client_addr_len = sizeof(client_addr);

int main(int argc, const char *argv[])
{
    int sock_fd, conn_fd;

    // 先判断参数是否合法 =3 ./server
    if (argc != 3)
    {
        fprintf(stdout, "%s <ip_addr> <port>\n", argv[0]);
        exit(0);
    }
    /**************多线程******************8*/
    pthread_t tid;
    do
    {
        // 定义一个socket
        sock_fd = socket(AF_INET, SOCK_STREAM, 0); // ipv4 tcp
        if (sock_fd < 0)
        {
            fprintf(stderr, "socket failed , errno:%d\n", errno);
            exit(-1);
        }
        // 设置端口复用
        /*当前阶段不建议频繁使用
        目的(purpose)：解决当前先关闭服务端再关闭客户端后，再次使用出现的端口被占用的问题*/
        int opt = 1;
        setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
        // 定义一个地址结构体
        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(atoi(argv[2])); // 端口号
        if (inet_aton(argv[1], &server_addr.sin_addr) == 0)
        {
            fprintf(stderr, "Invalid address\n"); // ip地址
            exit(EXIT_FAILURE);
        }
        if (!!bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)))
        {
            fprintf(stderr, "bind is failed!,errno = %d\n", errno);
            exit(-1);
        }
        // 监听
        if (listen(sock_fd, LISTEN_NUM) < 0)
        {
            fprintf(stderr, "listen failed, errno:%d\n", errno);
            exit(-1);
        }

    } while (0);
    puts("*******************连接成功 ，接收发送的数据:*******************\n");
    // 使用并发，子进程处理多个客户端的接收数据
    while (1)
    {
        // 建立连接
        conn_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &client_addr_len); // 每次循环都会创建一个新的连接 该函数会阻塞
        if (conn_fd < 0)
        {
            fprintf(stderr, "accept failed, errno:%d\n", errno);
            exit(-1);
        }
        // 创建线程
        if (!pthread_create(&tid, NULL, (void *)rece_client_data, (void *)&conn_fd))
        { // return = 0 is success
            // close(sock_fd);
            pthread_detach(tid); // 线程分离  使其自行回收
        }
    }

    // 关闭连接
    close(sock_fd);
    close(conn_fd);
    return 0;
}
/*处理  接收客户端数据*/
void *rece_client_data(void *arg)
{
    int conn_fd = *(int *)arg;
    while (1)
    {
        memset(buff, 0, sizeof(buff));
        int ret = read(conn_fd, buff, sizeof(buff));
        if (ret < 0)
        {
            fprintf(stderr, "read failed, errno:%d\n", errno);
            exit(-1);
        }
        else if (ret == 0)
        {
            fprintf(stderr, "server close\n");
            break;
        }
        else
        {
            // 这里的client_addr是在accept函数中获取的；
            printf("get client,ip:%s,port:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
            fprintf(stdout, "recv data: %s\n", buff); // 打印数据
        }
    }
    return NULL;
}

/*
linux@linux-vir--mac:~/Desktop/gitee_linux_c/study/network_code/3_TCP并发实现/3.TCP并发$ ./server 0 8888
*******************连接成功 ，接收发送的数据:*******************

get client,ip:127.0.0.1,port:36564
recv data: 234

get client,ip:127.0.0.1,port:37158
recv data: qwefewqa

server close
server close
^C
*/

/***********************************************************遗留问题*************************************/
/*                 1.僵尸进程问题                    客户端关闭后，服务端进程不会退出，会变成僵尸进程
e$ ps -eLf| grep 60509
linux      60509   22976   60509  0    1 04:02 pts/5    00:00:00 ./server 0 8888
linux      60581   60509   60581  0    1 04:02 pts/5    00:00:00 [server] <defunct>
linux      60994   60509   60994  0    1 04:05 pts/5    00:00:00 [server] <defunct>
linux      61296   60227   61296  0    1 04:07 pts/1    00:00:00 grep --color=auto 60509
*/