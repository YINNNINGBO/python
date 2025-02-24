#include "tcp.h"

/*********************函数声明*********************/
void server_push_file(p_tcp str_tcp);        // 处理客户端上传单个文件
void close_socket(p_tcp str_tcp);            // 关闭套接字并释放内存
void download_file_to_client(p_tcp str_tcp); // 处理客户端下载单个文件
// server 的读写文件描述
int read_fd = 0;  // 读取文件描述符
int write_fd = 0; // 写入文件描述符
int main(int argc, const char *argv[])
{
    ARGC_NUM(argc, 2);                          // 参数个数判断
    p_tcp str_tcp = (p_tcp)malloc(sizeof(tcp)); // 分配内存
    bzero(str_tcp, sizeof(tcp));                // 清零
    while (!my_socket(str_tcp, SERVER, argv))
        ; // 创建套接字   失败继续创建
    socklen_t addr_len = sizeof(str_tcp->client_addr);
    if ((str_tcp->fd_for_client = accept(str_tcp->fd, (struct sockaddr *)&str_tcp->client_addr, &addr_len)) < 0) // 接受连接
    {
        ERROR_EXIT("accept");
    }
    // 循环检测接收到的数据并处理
    while (1)
    {
        int tmp_ret1 = 0;
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
/*关闭套套接字*/
// 函数声明：关闭套接字并释放内存
// 参数：p_tcp str_tcp - 指向TCP结构体的指针
void close_socket(p_tcp str_tcp)
{
    // 关闭服务器端的套接字文件描述符
    close(str_tcp->fd);
    // 关闭客户端的套接字文件描述符
    close(str_tcp->fd_for_client);
    // 释放TCP结构体所占用的内存
    free(str_tcp);
}
/*处理客户端上传文件   返回 1 退出当前模式 */
void server_push_file(p_tcp str_tcp)
{
    // 接收文件名  并创建文件
    bzero(arg_buf, sizeof(arg_buf)); // 清零
    read_file(str_tcp->fd_for_client, arg_buf, BUF_SIZE);
    printf("文件名：%s\n", arg_buf);
    create_file((const char *)arg_buf);
    bzero(arg_buf, sizeof(arg_buf)); // 再次清空
    // 接收数据 并打印
    while (1)
    {
        bzero(arg_buf, sizeof(arg_buf)); // 清零
        int tmp_ret = my_server_use_recv(str_tcp);
        if (tmp_ret >= 0)
        {
            if (tmp_ret == 0)
            {
                close(write_fd); // 客户端关闭  通信套接字关闭
                break;
            }
            else if (tmp_ret > 0)
            {
                // 判断是不是当前模式结束指令
                if (!compare_last_n_chars(arg_buf, "exit", 4))
                {
                    puts("************************服务端退出 push 模式****************************");
                    fflush(stdout);
                    // 写完文件后，清空缓冲区
                    bzero(arg_buf, BUF_SIZE);
                    // 关闭文件
                    close(write_fd);
                    break; // 退出循环
                }
                write_file(write_fd, arg_buf, tmp_ret);
            }
        }
    }
}
void download_file_to_client(p_tcp str_tcp)
{
    // puts("************************发送文件到客户端***************************");
    // fflush(stdout);
    // 接收发送来的文件名

    if (read_file(str_tcp->fd_for_client, arg_buf, BUF_SIZE) > 0) // 接收文件名
    {
        printf("客户端要下载的文件名：%s\n", arg_buf);
        // 读取本地文件
        open_file(arg_buf);
        while (1)
        {
            char buf[BUFSIZ] = {0};
            int read_size = 0;
            if (!(read_size = read_file(read_fd, buf, BUFSIZ))) // 读取文件内容
            {
                close(read_fd);                     // 关闭源文件
                my_server_send(str_tcp, "exit", 4); // 源文件发送完，发送exit  当前模式结束指令
                break;
            }
            else
            {
                my_server_send(str_tcp, buf, read_size);
            }
        }
        // int tmp_ret = 0;
        // while ((tmp_ret = read_file(read_fd, buf, BUF_SIZE)) > 0)
        // {

        //     // 发送给客户端
        //     my_send(str_tcp, buf, BUF_SIZE);
        // }
        // if (tmp_ret == 0) // 读取完毕
        // {
        //     my_send(str_tcp, "exit", strlen("exit")); // 发送结束标志
        //     puts("***********************服务端文件读取完毕******************************");
        //     fflush(stdout);
        //     close(read_fd);
        // }
    }
}