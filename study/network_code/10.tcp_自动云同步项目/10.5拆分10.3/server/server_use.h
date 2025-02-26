#ifndef __SERVER_USE_H__
#define __SERVER_USE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <strings.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <dirent.h>
// 外部变量
#define BUF_SIZE 1024 // 缓冲区大小
#define PORT 8888     // 端口号
#define SERVER 1      // 1表示服务器
#define CLIENT 2      // 2表示客户端

extern char buf[BUF_SIZE];
extern char arg_buf[BUF_SIZE];
extern int server_read_fd;
extern int server_write_fd;
extern char write_zip_name[20]; // 写入压缩文件名
extern int write_zip_fd;        // 写入压缩文件描述符
/*检测参数数量*/
#define ARGC_NUM(arg, num)                       \
    do                                           \
    {                                            \
        if (arg != num)                          \
        {                                        \
            printf("error: argc too few!!! \n"); \
            exit(-1);                            \
        }                                        \
    } while (0)
/* 错误提示 原因 位置*/
#define ERROR_EXIT(msg)                                          \
    do                                                           \
    {                                                            \
        perror("msg");                                           \
        printf("file is %s , line is %d\n", __FILE__, __LINE__); \
        exit(EXIT_FAILURE);                                      \
    } while (0)
/***************自定义tcp通信结构体 */
typedef struct
{
    int fd; // 文件描述符
    int fd_for_client;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
} *p_tcp, tcp;

/***************************函数声明*****************/
int my_socket(p_tcp ptcp, const char *t_argv[]);

int my_server_use_recv(p_tcp ptcp);

// int my_client_send(p_tcp ptcp, const char *msg, int len);

int my_server_send(p_tcp ptcp, const char *str, int len);

void show_server_info(p_tcp str_tcp);

int compare_last_n_chars(const char *big_str, const char *son_str, size_t n);

void open_file(const char *argv);

void create_file(const char *argv);

int write_file(int fd, char *arr, int size);

int read_file(int fd, char *arr, int size);

/*********************函数声明*********************/
void server_push_file(p_tcp str_tcp);         // 处理客户端上传单个文件
void close_socket(p_tcp str_tcp);             // 关闭套接字并释放内存
void download_file_to_client(p_tcp str_tcp);  // 处理客户端下载单个文件
void recv_file_make_zip(p_tcp str_tcp);       // 处理客户端下载多个文件
void unzip_file(const char *zip_name);        // 解压文件
int whether_have_file(const char *file_name); // 判断当前目录，该文件是否存在

#endif /* __SERVER_USE_H__ */