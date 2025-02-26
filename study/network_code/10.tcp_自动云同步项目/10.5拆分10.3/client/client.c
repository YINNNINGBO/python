#include "client_use.h"

int main(int argc, const char *argv[])
{
    ARGC_NUM(argc, 2);                          // <0 可执行文件><1 ip><2 源文件><3 生成文件>参数个数判断
    p_tcp str_tcp = (p_tcp)malloc(sizeof(tcp)); // 分配内存
    bzero(str_tcp, sizeof(tcp));                // 清零
    while (!my_socket(str_tcp, argv))
        ; // 创建套接字   失败继续创建
    int tmp_ret = 0;
    while (1)
    {
        // 读取客户端模式指令  ：查看文件  ，下载文件  上串 ，同步 ，退出
        puts("****************发送指令：<look> <getf> <push> <sync> <exit>*************************");
        fflush(stdout);
        bzero(client_arg_buf, sizeof(client_arg_buf));
        if ((tmp_ret = read(STDIN_FILENO, client_arg_buf, 100)) != -1)
        {
            if (!my_client_send(str_tcp, client_arg_buf, strlen(client_arg_buf))) // 将命令发送给服务端
            {
                // 上传文件
                if (!strncmp(client_arg_buf, "push", 4))
                {
                    puts("当前状态时push,<输入本地文件名>  <发送到服务端目的文件名>\n");
                    scanf("%s %s", source_file_name, copy_file_name);
                    push_file(str_tcp, source_file_name, copy_file_name);
                }
                // 查看文件信息
                if (!strncmp(client_arg_buf, "look", 4))
                {
                    client_arg_buf[0] = '\0';
                    show_file(str_tcp);
                }
                // 下载文件
                if (!strncmp(client_arg_buf, "getf", 4))
                {
                    puts("当前状态时getf,<输入服务端文件名>  <发送到本地目的文件名>\n");
                    // scanf("%s", source_file_name); // 这里用 source_file_name  代表服务端源文件名
                    get_file_for_server(str_tcp); // 发送要下载的文件名  ，并接收
                }
                // 同步文件
                if (!strncmp(client_arg_buf, "sync", 4))
                {
                    puts("当前状态时sysc,输入你想要的最终文件名\n");
                    client_send_file_name(str_tcp); // 打包文件，并发送
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
