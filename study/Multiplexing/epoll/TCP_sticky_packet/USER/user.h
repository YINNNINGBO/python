#ifndef __USER_H__
#define __USER_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <malloc.h>
// 宏
#define SERVER_PORT 8888
#define SERVER_IP "192.168.1.215" // 这里使用字符串 转换字节序应该使用 inet_xxxxx
#define LISTEN_LEN 128
#define TYPE_SERVER 1
#define TYPE_CLIENT 0
// ------------------------错误提示
#define IF_DEBUG(esp, msg)                                                                 \
    do                                                                                     \
    {                                                                                      \
        if (esp)                                                                           \
        {                                                                                  \
            perror(msg);                                                                   \
            printf("----------errno = %d ; file: %s ; func: %s ; line: %d ------------\n", \
                   errno, __FILE__, __func__, __LINE__);                                   \
            exit(-1);                                                                      \
        }                                                                                  \
    } while (0)
//--------------------------------------API------------------------------------------
/**
 * @brief 创建套接字
 * @param fd 文件描述符
 * @param port 端口号
 * @param ip IP地址
 * @param type 套接字类型 (TYPE_SERVER 或 TYPE_CLIENT)
 * @note 该函数会根据 type 参数创建相应的套接字类型，服务器端使用 SOCK_STREAM，客户端使用 SOCK_DGRAM。
 * @return 返回 0 表示成功，-1 表示失败
 */
int create_socket(int *fd, int port, const char *ip, int type);

/**
 * @brief 连接服务器
 * @param fd 文件描述符
 * @param buf 缓冲区
 * @param size 缓冲区大小
 * @return >0:表示读取的字节数，0:表示连接关闭，-1:表示错误
 */
int readn(int fd, char *buf, int size);

int recvMsg(int cfd, char **msg);

/**
 * @brief 向套接字写入数据
 * @param fd 文件描述符
 * @param buf 缓冲区
 * @param size 要写入的长度
 * @return >0:表示写入的字节数，，-1:表示错误
 */
int writen(int fd, const char *buf, int size);

int sendMsg(int cfd, char *msg, int len);

/**
 * @brief 关闭套接字
 * @param fd 文件描述符
 * @return 0:表示成功，-1:表示失败
 */
int close_socket(int fd);

// 将字符串最后的换行变为字符串结束符
//  判断从终端输入的数据的最后一个字符是不是换行符，如果是，则将其替换为字符串结束符
//  这样可以避免发送多余的换行符 且不会影响输入的内容
void del_end_enter(char buf[]);
#endif /* __USER_H__ */
