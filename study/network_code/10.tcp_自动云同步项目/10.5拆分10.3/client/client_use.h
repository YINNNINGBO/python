#ifndef __CLIENT_USE_H__
#define __CLIENT_USE_H__

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
#include <sys/time.h>
#include <dirent.h>
// 外部变量
#define BUF_SIZE 1024 // 缓冲区大小
#define PORT 8888     // 端口号
#define SERVER 1      // 1表示服务器

extern char buf[BUF_SIZE];
extern char arg_buf[BUF_SIZE];
extern int client_read_fd;
extern int client_write_fd;
extern char client_arg_buf[BUF_SIZE]; // 存储客户端参数
extern char source_file_name[40];
extern char copy_file_name[40];
extern char send_file_name[20]; // 保存接收到的文件名
extern int read_zip_fd;         // 保存文件描述符
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

// int my_server_use_recv(p_tcp ptcp);

int my_client_send(p_tcp ptcp, const char *msg, int len);

// int my_server_send(p_tcp ptcp, const char *str, int len);

// void show_server_info(p_tcp str_tcp);

int compare_last_n_chars(const char *big_str, const char *son_str, size_t n);

void open_file(const char *argv);

void create_file(const char *argv);

int write_file(int fd, char *arr, int size);

int read_file(int fd, char *arr, int size);

void push_file(p_tcp str_tcp, const char *soure_name, const char *copy_file_name);
void show_file(p_tcp str_tcp);
void get_file_for_server(p_tcp str_tcp); // 下载文件
int client_send_file_name(p_tcp str_tcp);
int whether_have_file(const char *file_name); // 判断当前目录，该文件是否存在

#endif /* __CLIENT_USE_H__ */