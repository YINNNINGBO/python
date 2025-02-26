#include "tcp.h"
char write_zip_name[20] = {0};
int write_zip_fd = -1;
void recv_file_make_zip(p_tcp str_tcp);
void unzip_file(const char *zip_name);
int main(int argc, const char *argv[])
{
    ARGC_NUM(argc);                             // 参数个数判断
    p_tcp str_tcp = (p_tcp)malloc(sizeof(tcp)); // 分配内存
    bzero(str_tcp, sizeof(tcp));                // 清零
    while (!my_socket(str_tcp, SERVER, argv))
        ; // 创建套接字   失败继续创建
    socklen_t addr_len = sizeof(str_tcp->client_addr);
    if ((str_tcp->fd_for_client = accept(str_tcp->fd, (struct sockaddr *)&str_tcp->client_addr, &addr_len)) < 0) // 接受连接
    {
        ERROR_EXIT("accept");
    }
    // 接收文件并生成压缩包
    recv_file_make_zip(str_tcp);
    // 解压压缩包文件，并删除zip
    unzip_file(write_zip_name);
    // 关闭套接字
    close(str_tcp->fd);
    close(str_tcp->fd_for_client);
    free(str_tcp);
    return 0;
}

// 接收文件并生成压缩包
void recv_file_make_zip(p_tcp str_tcp)
{
    // 接收文件名
    int tmp_ret = 0;
    bzero(write_zip_name, 20);
    if ((tmp_ret = read(str_tcp->fd_for_client, write_zip_name, 20)) < 0) // 修改读取长度为19
    {
        ERROR_EXIT("recv");
    }
    write_zip_name[19] = 0;         // 确保字符串以空字符结尾
    printf("%s\n", write_zip_name); // 显示依次文件名
    // 创建文件
    if ((write_zip_fd = open(write_zip_name, O_WRONLY | O_CREAT, 0666)) < 0)
    {
        ERROR_EXIT("open");
    }
    // 接收文件
    char server_read_buff[1024] = {0};
    while (1)
    {
        // 接收一次
        if ((tmp_ret = recv(str_tcp->fd_for_client, server_read_buff, 1024, 0)) < 0)
        {
            ERROR_EXIT("recv");
        }
        if (tmp_ret == 0)
        {
            close(str_tcp->fd_for_client);
            break;
        }
        // 写一次
        if (write(write_zip_fd, server_read_buff, tmp_ret) < 0)
        {
            ERROR_EXIT("write");
        }
    }
}
// 解压压缩包文件，并删除zip
void unzip_file(const char *zip_name)
{
    // 获取压缩包的前缀
    char front_name[20] = {0};
    int front_name_len = strlen(zip_name) - 4;
    for (int i = 0; i < front_name_len; i++)
    {
        front_name[i] = zip_name[i];
    }
    // 解压文件
    char cmd[100] = {0};
    sprintf(cmd, "unzip  %s -d %s", zip_name, front_name); // 现在的cmd是unzip 1.zip -d 1
    if (system(cmd) > 0)
    {
        ERROR_EXIT("system");
    }
    // 删除zip文件
    sprintf(cmd, "rm -rf %s", zip_name);
    system(cmd);
}