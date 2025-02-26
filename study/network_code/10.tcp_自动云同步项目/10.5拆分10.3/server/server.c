#include "server_use.h"

/*********************函数声明*********************/
void server_push_file(p_tcp str_tcp);        // 处理客户端上传单个文件
void close_socket(p_tcp str_tcp);            // 关闭套接字并释放内存
void download_file_to_client(p_tcp str_tcp); // 处理客户端下载单个文件
// server 的读写文件描述
int read_fd = 0;  // 读取文件描述符
int write_fd = 0; // 写入文件描述符

// 分配内存
int main(int argc, const char *argv[])
{
    ARGC_NUM(argc, 2); // 参数个数判断
    p_tcp str_tcp = (p_tcp)malloc(sizeof(tcp));
    bzero(str_tcp, sizeof(tcp)); // 清零
    while (!my_socket(str_tcp, argv))
        ; // 创建套接字   失败继续创建
    // 信号处理 处理ctrl+c

    socklen_t addr_len = sizeof(str_tcp->client_addr);
    if ((str_tcp->fd_for_client = accept(str_tcp->fd, (struct sockaddr *)&str_tcp->client_addr, &addr_len)) < 0) // 接受连接
    {
        ERROR_EXIT("accept");
    }
    // 循环检测接收到的数据并处理
    while (1)
    {
        int tmp_ret1 = 0;
        puts("*******************************等待客户端命令************************************\n");
        if ((tmp_ret1 = read_file(str_tcp->fd_for_client, arg_buf, BUF_SIZE)) == 0)
        {
            printf("客户端断开连接\n");
            close(str_tcp->fd_for_client);
            break;
        }
        printf("客户端发送的命令：%s\n", arg_buf);
        // 比较命令选项  查看look  下载:getf  上传:push 同步:sync  退出:exit
        if (strncmp(arg_buf, "look", 4) == 0)
        {
            bzero(arg_buf, sizeof(arg_buf)); // 清零
            // 查看文件
            puts("现在客户端要查看服务端文件");
            show_server_info(str_tcp);
            if (str_tcp->fd_for_client == 0) // 当客户端断开连接时
            {
                break;
            }
        }
        else if (strncmp(arg_buf, "push", 4) == 0)
        {
            // 上传文件
            puts("现在客户端要上传文件到服务端");
            server_push_file(str_tcp);
        }
        else if (strncmp(arg_buf, "getf", 4) == 0)
        {
            puts("现在客户端要上传文件到服务端");
            download_file_to_client(str_tcp);
            // 下载文件
        }
        else if (strncmp(arg_buf, "sync", 4) == 0)
        {
            puts("将接受文件包\n");
            recv_file_make_zip(str_tcp); // 处理客户端下载多个文件
            unzip_file(write_zip_name);
        }
        else if (strncmp(arg_buf, "exit", 4) == 0)
        {
            puts("客户端退出");
            close_socket(str_tcp);
            return 0;
        }
    }
    // 关闭套接字
    close_socket(str_tcp);
    return 0;
}