#include "../USER/user.h"

int main(int argc, const char *argv[])
{
    int *fd = (int *)malloc(sizeof(int));
    char *buf = (char *)malloc(1024); // 动态分配内存，避免栈溢出
    // 创建套接字
    create_socket(fd, SERVER_PORT, SERVER_IP, TYPE_SERVER);

    // 连接客户端、
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    int client_fd = accept(*fd, (struct sockaddr *)&addr, &addr_len);
    IF_DEBUG((client_fd < 0), "accept error");
    printf("<------Client connected successfully!------------>\n");
    printf("Client IP: %s, Port: %d\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port)); // 打印客户端IP和端口
    // 读取数据并打印子啊客户端
    while (1)
    {
        bzero(buf, 1024); // 清空缓冲区);
        int ret = recvMsg(client_fd, &buf);
        if (ret < 0)
        {
            perror("read error");
            break; // 读取错误，退出循环
        }
        else if (ret == 0)
        {
            printf("Client exiting!\n");
            break; // 客户端断开连接，退出循环
        }
        else
        {
            printf("get client string :%s \n", buf);
        }
    }

    // 关闭套接字
    close_socket(*fd);

    return 0;
}