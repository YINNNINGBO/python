//   服务端程序  使用poll 实现多路复用（并发）
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <arpa/inet.h>
#define PORT 8888
#define IP_ADDR "192.168.1.215"
#define LINTEN_LEN 128
// 定义错误处理宏 表达式正确说明错误 提示错误信息
#define DEBUG(exp, msg)                                            \
    do                                                             \
    {                                                              \
        if (exp)                                                   \
        {                                                          \
            perror(msg);                                           \
            printf("func : %s; line: %d, \n", __func__, __LINE__); \
            exit(-1);                                              \
        }                                                          \
    } while (0)

int main(int argc, const char *argv[])
{
    // 设置全局变量
    int con_fd, lfd = -1;
    struct sockaddr_in addr;
    // 1. 创建监听的fd
    lfd = socket(AF_INET, SOCK_STREAM, 0);
    DEBUG(lfd < 0, "socket error:");
    // 2. 绑定 地址族结构体
    addr.sin_family = AF_INET;                 // ipv4
    addr.sin_port = htons(PORT);               // 服务器监听的端口, 字节序应该是网络字节序
    addr.sin_addr.s_addr = inet_addr(IP_ADDR); // 服务器监听的IP地址
    DEBUG(bind(lfd, (struct sockaddr *)&addr, sizeof(addr)) < 0, "bind error:");
    // 3. 设置监听
    DEBUG(listen(lfd, LINTEN_LEN) < 0, "listen error:");

    // 4. 设置poll结构体
    struct pollfd fds[1024];       // 定义poll结构体数组
    for (int i = 0; i < 1024; ++i) // 初始化poll 数组
    {
        fds[i].fd = -1;         // 初始化所有的文件描述符为-1, 表示没有使用
        fds[i].events = POLLIN; // 初始化事件类型为0
    }

    fds[0].fd = lfd;        // 将监听的lfd设置到poll结构体数组中
    fds[0].events = POLLIN; // 设置监听的事件类型为POLLIN, 读事件
    int max_index = 0;      // 最大的索引
    // 5. 循环等待连接请求
    while (1)
    {
        // 6. 调用poll函数, 阻塞等待事件发生
        int ret = poll(fds, max_index + 1, -1); // -1表示永久阻塞
        DEBUG(ret < 0, "poll error:");
        // 7. 遍历poll结构体数组, 检测哪个文件描述符发生了事件
        if (fds[0].revents & POLLIN) // 监听的lfd发生了读事件
        {
            // 接受连接请求, 这个调用不阻塞
            struct sockaddr_in cliaddr;
            socklen_t cliLen = sizeof(cliaddr);
            con_fd = accept(lfd, (struct sockaddr *)&cliaddr, &cliLen);
            DEBUG(con_fd < 0, "accept error:");
            // 遍历fds中没有使用的元素, 将新的通信套接字添加到poll结构体数组中
            for (int i = 1; i < 1024; ++i)
            {
                if (fds[i].fd < 0) // 找到一个没有使用的元素
                {
                    fds[i].fd = con_fd;                        // 将新的通信套接字添加到poll结构体数组中
                    fds[i].events = POLLIN;                    // 设置监听的事件类型为POLLIN, 读事件
                    max_index = i > max_index ? i : max_index; // 更新最大索引
                    break;
                }
            }
        }
        else
        {
            // 遍历poll结构体数组, 检测哪个文件描述符发生了事件
            for (int i = 1; i <= max_index; ++i)
            {
                if (fds[i].fd < 0) // 如果这个文件描述符没有使用, 跳过
                    continue;
                if ((fds[i].revents & POLLIN) && (fds[i].fd > 0)) // 如果这个文件描述符发生了读事件
                {
                    char buf[1024] = {0};
                    ssize_t n = read(fds[i].fd, buf, sizeof(buf) - 1);
                    if (n < 0)
                    {
                        perror("read error:");
                        close(fds[i].fd); // 关闭这个文件描述符
                        fds[i].fd = -1;   // 将这个文件描述符设置为-1, 表示没有使用
                    }
                    else if (n == 0)
                    {
                        printf("client closed\n");
                        close(fds[i].fd); // 关闭这个文件描述符
                        fds[i].fd = -1;   // 将这个文件描述符设置为-1, 表示没有使用
                    }
                    else
                    {
                        buf[n] = '\0'; // 添加字符串结束符
                        printf("recv: %s\n", buf);
                        write(fds[i].fd, buf, n); // 回写数据到客户端
                    }
                }
            }
        }
    }

    return 0;
}