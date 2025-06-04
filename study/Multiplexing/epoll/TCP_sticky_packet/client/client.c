#include "../USER/user.h"

int main(int argc, const char *argv[])
{
    int *fd = (int *)malloc(sizeof(int));
    char buf[1024];
    // 创建套接字
    create_socket(fd, SERVER_PORT, SERVER_IP, TYPE_CLIENT);

    // 连接服务器
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERVER_PORT);
    addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    int ret = connect(*fd, (struct sockaddr *)&addr, sizeof(addr));
    IF_DEBUG((ret < 0), "connect error");
    puts("<------Connected to server successfully!------------>");
    // 读取终端输入，并发送
    while (1)
    {
        bzero(buf, sizeof(buf));
        printf("Enter message to send: ");
        fgets(buf, sizeof(buf), stdin);
        // 删除末尾的换行符
        del_end_enter(buf); // 这里删除末尾的换行符后 ，字符串的长度-1，so 使用 strlen(buf) 而不是 strlen(buf) + 1
                            // 若使用 strlen(buf) + 1 ， 则发送多一个字节
        // 发送数据
        if (sendMsg(*fd, buf, strlen(buf)) > 0) // 加1是为了包括字符串结束符
        {
            printf("Sent message: %s\n", buf);
        }
        else
        {
            perror("send error");
            break; // 发送错误，退出循环
        }
    }

    // 关闭套接字
    close_socket(*fd);
    free(fd);
    return 0;
}