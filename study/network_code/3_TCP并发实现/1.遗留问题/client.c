#include "head.h"

/**
 *  客户端代码  循环向服务端发送的数据
 */
#include "head.h"
#define BUF_SIZE 100
char buf[BUF_SIZE] = {0};
int main(int argc, const char *argv[])
{
    static int sock_fd;
    // 先判断参数是否合法 =3 ./server
    if (argc != 3)
    {
        fprintf(stdout, "%s <ip_addr> <port>\n", argv[0]);
        exit(0);
    }
    do
    {
        // 定义一个socket
        sock_fd = socket(AF_INET, SOCK_STREAM, 0); // ipv4 tcp
        if (sock_fd < 0)
        {
            fprintf(stderr, "socket failed , errno:%d\n", errno);
            exit(-1);
        }

        // 定义一个地址结构体
        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(atoi(argv[2])); // 端口号
        if (inet_aton(argv[1], &server_addr.sin_addr) == 0)
        {
            fprintf(stderr, "Invalid address\n"); // ip地址
            exit(EXIT_FAILURE);
        }
        // 发送连接请求
        if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        {
            fprintf(stderr, "connect failed, errno:%d\n", errno);
            exit(-1);
        }

    } while (0);
    // 循环接收数据
    puts("*******************连接成功 ，输入向服务器发送的数据:*******************\n");
    while (1)
    {
        printf("input->");
        fgets(buf, BUF_SIZE, stdin);
        if (write(sock_fd, buf, strlen(buf)) < 0)
        {
            perror("write is error!!!\n");
            exit(-1);
        }
        memset(buf, 0, BUF_SIZE);
    }
    // 关闭连接
    close(sock_fd);
    return 0;
}
/***
linux@linux-vir--mac:~/Desktop/gitee_linux_c/study/network_code/2_server_clinet$ ./client 127.0.0.1 8888
*******************连接成功 ，输入向服务器发送的数据:*******************

input->The World!!!
input->
 */