#include "tcp.h"

// const char *read_zip_name = "tmp.txt";
char write_zip_name[20] = {0}; // 保存接收到的文件名
int read_zip_fd = -1;          // 保存文件描述符
int client_send_file_name(p_tcp str_tcp);
int main(int argc, const char *argv[])
{
    ARGC_NUM(argc);                             // 参数个数判断
    p_tcp str_tcp = (p_tcp)malloc(sizeof(tcp)); // 分配内存
    bzero(str_tcp, sizeof(tcp));                // 清零
    while (!my_socket(str_tcp, CLIENT, argv))
        ; // 创建套接字   失败继续创建

    client_send_file_name(str_tcp);

    close(str_tcp->fd);
    free(str_tcp);
    close(read_zip_fd);
    return 0;
}

/*发送文件名*/
int client_send_file_name(p_tcp str_tcp)
{
    // 1.压缩当前所有文件名
    if (system("zip -r tmp.zip ./*") < 0)
    {
        ERROR_EXIT("system");
    }
    // 2.接收文件名
    puts("输入临时写入压缩包文件名\n");
    scanf("%s", write_zip_name);
    if (write_zip_name[strlen(write_zip_name) - 1] == '\n')
    {
        write_zip_name[strlen(write_zip_name) - 1] = 0;
    }
    // 3.发送文件名
    my_send(str_tcp, write_zip_name, strlen(write_zip_name));

    // 4.创建read  write 文件描述符
    if ((read_zip_fd = open("tmp.zip", O_RDONLY)) < 0)
    {
        ERROR_EXIT("open");
    }

    // 5.发送文件
    while (1)
    {
        bzero(buf, sizeof(buf));
        int ret_num = 0;
        //  从打包好的压缩包文件中读取数据
        if ((ret_num = read(read_zip_fd, buf, 1024)) > 0)
        {
            //  向服务端发送数据
            my_send(str_tcp, buf, ret_num);
        }
        if (ret_num == 0)
        {
            printf("发送完毕\n");
            close(read_zip_fd);
            break;
        }
    }
    // 6.关闭文件描述符 删除临时文件
    if (system("rm  -f tmp.zip") < 0)
    {
        ERROR_EXIT("system");
    }

    return 0;
}