#include "tcp.h"
#include "user_file.h"
char client_arg_buf[BUF_SIZE] = {0}; // 存储客户端参数
char source_file_name[40] = {0};
char copy_file_name[40] = {0};
int read_fd = 0;  // 读取文件描述符
int write_fd = 0; // 写入文件描述符
void push_file(p_tcp str_tcp, const char *soure_name, const char *copy_file_name);
void show_file(p_tcp str_tcp);
void get_file_for_server(p_tcp str_tcp); // 下载文件
int main(int argc, const char *argv[])
{
    ARGC_NUM(argc, 2);                          // <0 可执行文件><1 ip><2 源文件><3 生成文件>参数个数判断
    p_tcp str_tcp = (p_tcp)malloc(sizeof(tcp)); // 分配内存
    bzero(str_tcp, sizeof(tcp));                // 清零
    while (!my_socket(str_tcp, CLIENT, argv))
        ; // 创建套接字   失败继续创建
    int tmp_ret = 0;
    while (1)
    {
        // 读取客户端模式指令  ：查看文件  ，下载文件  上串 ，同步 ，退出
        puts("****************发送指令：<look> <getf> <push> <sync> <exit>*************************");
        fflush(stdout);
        if ((tmp_ret = read(STDIN_FILENO, client_arg_buf, 100)) != -1)
        {

            if (!my_client_send(str_tcp, client_arg_buf, strlen(client_arg_buf))) // 将命令发送给服务端
            {
                // 上传文件
                if (!strncmp(client_arg_buf, "push", 4))
                {
                    puts("当前状态时push,输入你的文件名\n");
                    scanf("%s %s", source_file_name, copy_file_name);
                    push_file(str_tcp, source_file_name, copy_file_name);
                }
                // 查看文件信息
                if (!strncmp(client_arg_buf, "look", 4))
                {
                    show_file(str_tcp);
                }
                // 下载文件
                if (!strncmp(client_arg_buf, "getf", 4))
                {
                    puts("当前状态时getf,输入你要下载的文件名\n");
                    // scanf("%s", source_file_name); // 这里用 source_file_name  代表服务端源文件名
                    get_file_for_server(str_tcp); // 发送要下载的文件名  ，并接收
                }
                // 同步文件
                if (!strncmp(client_arg_buf, "sync", 4))
                {
                    show_file(str_tcp);
                }
                // 退出
                if (!strncmp(client_arg_buf, "exit", 4))
                {
                    // my_client_send(str_tcp, "exit", strlen("exit"));
                    close(str_tcp->fd);
                    return 0; // 退出程序
                }
            }
        }
    }

    return 0;
}

// 打开源文件 发送生成文件名
void push_file(p_tcp str_tcp, const char *soure_name, const char *copy_file_name)
{
    open_file(soure_name);                                                   // 打开源文件
    write_file(str_tcp->fd, (char *)copy_file_name, strlen(copy_file_name)); // 写入文件名
    puts("已经发发送文件名\n");
    while (1)
    {
        bzero(buf, BUF_SIZE);
        int read_size = 0;
        if ((read_size = read_file(read_fd, buf, BUF_SIZE))) // 读取文件内容
        {
            my_client_send(str_tcp, buf, read_size);
            bzero(buf, BUF_SIZE);
        }
        if (read_size == 0)
        {
            close(read_fd); // 关闭源文件
            puts("exit");
            fflush(stdout);
            write_file(str_tcp->fd, "exit", strlen("exit")); // 源文件发送完，发送exit  当前模式结束指令
            break;                                           // 退出循环
        }
    }
}

/******获取服务端数据***********/
void show_file(p_tcp str_tcp)
{
    bzero(client_arg_buf, 100);

    // 发送命令
    puts("************************发送命令****************************");
    while (fgets(client_arg_buf, 100, stdin) != NULL) // client   在终端 接收用户命令
    {
        if (client_arg_buf[strlen(client_arg_buf) - 1] == '\n')
        {
            client_arg_buf[strlen(client_arg_buf) - 1] = '\0';
        }
        printf("客户端发闪送命令%s\n", client_arg_buf);                       // 显示输入命令
        if (!my_client_send(str_tcp, client_arg_buf, strlen(client_arg_buf))) // 向服务端发送数据
        {
            if (!strncmp(client_arg_buf, "exit", 4))
            {
                // 说明是退出当前模式的指令
                puts("************************退出当前模式****************************");
                fflush(stdout);
                break;
            }
            // 成功发送
            puts("************************接收服务端反馈****************************");
            int tmp_ret = 0;
            printf("反馈数据长度是%ld\n", strlen(client_arg_buf));
            bzero(buf, BUF_SIZE);                                         // 刷新缓冲区
            while ((tmp_ret = read_file(str_tcp->fd, buf, BUF_SIZE)) > 0) // 接收服务端反馈
            {
                // 检查最后一个字符是不是 exit
                if (!compare_last_n_chars(buf, "exit", 4))
                {
                    printf("服务端反馈数据发送完\n");
                    puts("************************发送命令***************************");
                    break; // 当检测到exit时退出内层循环
                }
                fputs(buf, stdout);
                fflush(stdout);
                bzero(buf, BUF_SIZE);
            }

            fflush(stdout);
        }

        // bzero(client_arg_buf, 100); // 清空命令缓冲区
    }
}
/**
 * @function: 下载文件
 * @str_tcp:  tcp结构体
 * @source_file_name:  源文件名
 * @return
 */
void get_file_for_server(p_tcp str_tcp)
{
    puts("**********************输入要获取的服务端源文件名**************************");
    fflush(stdout);
    bzero(source_file_name, 40);
    bzero(copy_file_name, 40);
    while (scanf("%s %s", source_file_name, copy_file_name) > 0) // client   在终端 接收用户命令
    {
        // 创建文件
        printf("source_file_name:%s , copy_file_name:%s\n", source_file_name, copy_file_name);

        if (!(my_client_send(str_tcp, source_file_name, strlen(source_file_name)))) // 向服务端发送要获取的文件名
        {
            create_file(copy_file_name); // 直接对write_fd赋值
            bzero(buf, BUF_SIZE);        // 刷新缓冲区
            while (read_file(str_tcp->fd, buf, BUF_SIZE) > 0)
            {
                if (!compare_last_n_chars(buf, "exit", 4)) // 如果接收到exit  说明  发送完
                {
                    puts("**********************接收文件完成**************************");
                    fflush(stdout);
                    close(write_fd);
                    return; // 退出当前模式
                }
                write_file(write_fd, buf, strlen(buf));
                bzero(buf, BUF_SIZE); // 刷新缓冲区
            }
        }
    }
}