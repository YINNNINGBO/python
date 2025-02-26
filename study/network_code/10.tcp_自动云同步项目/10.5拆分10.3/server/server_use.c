#include "server_use.h"

char buf[BUF_SIZE] = {0};      // 缓冲区
char arg_buf[BUF_SIZE] = {0};  // 命令缓冲区
int server_read_fd = 0;        // 读取文件描述符
int server_write_fd = 0;       // 写入文件描述符server
char write_zip_name[20] = {0}; // 写入压缩文件名
int write_zip_fd = -1;         // 写入压缩文件描述符

/*if this file is server.c socket->listen ;if this file is client.c socket->connect
 *   ptcp: 通信结构体
 *   server_or_client: 1= server ；2= client
 *  @return: 通信套接字  0:fail
 */
int my_socket(p_tcp ptcp, const char *t_argv[])
{
    // 生成套接字
    if ((ptcp->fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
        return 0;
    }
    // 设置地址重用
    int opt = 1;
    setsockopt(ptcp->fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    // if (server_or_client == SERVER) // 如果当前是服务器
    // {
    // 设置服务器地址
    ptcp->server_addr.sin_family = AF_INET;                             // 协议族
    ptcp->server_addr.sin_port = htons(PORT);                           // 端口号
    if (inet_pton(AF_INET, t_argv[1], &ptcp->server_addr.sin_addr) < 0) // IP地址
    {
        ERROR_EXIT("servre inet_pton");
    }
    if (bind(ptcp->fd, (struct sockaddr *)&ptcp->server_addr, (socklen_t)sizeof(ptcp->server_addr)) < 0)
    {
        ERROR_EXIT("bind");
    }
    if (listen(ptcp->fd, 5) < 0)
    {
        ERROR_EXIT("listen");
    }
    // }
    // else if (server_or_client == CLIENT) // 如果当前是客户端
    // {
    //     // 设置服务器地址
    //     ptcp->server_addr.sin_family = AF_INET;                             // 协议族
    //     ptcp->server_addr.sin_port = htons(PORT);                           // 端口号
    //     if (inet_pton(AF_INET, t_argv[1], &ptcp->server_addr.sin_addr) < 0) // IP地址
    //     {
    //         ERROR_EXIT("client inet_pton");
    //     }
    //     if (connect(ptcp->fd, (struct sockaddr *)&ptcp->server_addr, (socklen_t)sizeof(ptcp->server_addr)) < 0)
    //     {
    //         ERROR_EXIT("connect");
    //     }
    // }
    return ptcp->fd;
}

/**
 * @breif: 服务端接收客户端的连接  仅限服务端使用
 * @参数： ptcp: 通信结构体
 * @return :  sucess=1; fail=0  exit:2
 */
int my_server_use_recv(p_tcp ptcp)
{
    int ret = 0;
    // do
    // {

    ret = read(ptcp->fd_for_client, arg_buf, BUF_SIZE);
    // } while (ret == 0 && ret == EINTR);
    if (ret < 0)
    {
        perror("read");
        return -1;
    }
    else if (ret == 0)
    {

        return 0;
    }
    else
    {
        return ret;
    }
}

// /**
//  * @breif: 客户端发送服务端数据
//  * @return :  sucess=0;
//  */
// int my_client_send(p_tcp ptcp, const char *str, int len)
// {
//     int ret = 0;
//     if ((ret = send(ptcp->fd, str, len, 0)) < 0)
//     {
//         ERROR_EXIT("send");
//     }
//     return 0;
// }

/**
 * @breif: 服务端发送客户端数据
 */
int my_server_send(p_tcp ptcp, const char *str, int len)
{
    int ret = 0;
    if ((ret = send(ptcp->fd_for_client, str, len, 0)) < 0)
    {
        ERROR_EXIT("send");
    }
    return 0;
}
/*服务端反馈服务端信息*/
void show_server_info(p_tcp str_tcp)
{
    // bzero(arg_buf, 100);
    FILE *fp; // 打开文件
    // // 设置接收超时为 0，恢复默认阻塞行为
    // struct timeval recv_timeout;
    // recv_timeout.tv_sec = 0;  // 秒
    // recv_timeout.tv_usec = 0; // 微秒

    // if (setsockopt(str_tcp->fd_for_client, SOL_SOCKET, SO_RCVTIMEO, &recv_timeout, sizeof(recv_timeout)) < 0)
    // {
    //     perror("setsockopt failed");
    // }
    while (1)
    {
        // 读取用户输入的命令   使用通信套接字
        bzero(arg_buf, sizeof(arg_buf));
        int tmp_ret = 0;
        if ((tmp_ret = recv(str_tcp->fd_for_client, arg_buf, 100, 0)) > 0) // 接收命令
        {
            if (!strncmp(arg_buf, "exit", 4))
            {
                puts("************************服务端退出 look 模式****************************");
                fflush(stdout);
                break;
            }
            puts(arg_buf); // 打印用户输入的命令
                           // fflush(stdout);
            fp = popen((const char *)arg_buf, "r");
            if (fp == NULL)
            {
                printf("Failed to run command\n");
                pclose(fp);
                exit(1);
            }
            // 接收到 exit  说明退出当前模式
            if (strcmp(arg_buf, "exit") == 0)
            {
                break;
            }
            else // 反之开始发送终端打印
            {
                bzero(arg_buf, 100); // 读取，发送用的是同一个缓冲区 清空缓冲区
                // 读取命令输出，直到没有更多输出
                char *arg_buf1 = NULL;
                while ((arg_buf1 = fgets(arg_buf, sizeof(arg_buf), fp)))
                {
                    puts(arg_buf);
                    fflush(stdout);
                    write(str_tcp->fd_for_client, arg_buf, strlen(arg_buf1));
                    bzero(arg_buf, 100);
                }
                if (arg_buf1 == NULL)
                {
                    write(str_tcp->fd_for_client, "exit", strlen("exit")); // 发送结束字符
                    printf("全部数据发送完\n");
                    pclose(fp);
                    continue; // 继续读取用户输入的命令
                }
            }
        }
        if (tmp_ret == 0)
        { // 客户端断开连接  主动关闭通信套接字
            puts("客户端断开连接");
            fflush(stdout);
            str_tcp->fd_for_client = 0;
            break;
        }
    }
}
/**
 * @breif:查询字符串的后n个字符 是不是str
 * @param: big_str: 查询的字符串   ;son_str : 查询是否要含的字符串  ;n: 查询big_str的后n位
 * @return: 成功返回 0  ；若前者>后者 返回 <0 ;反之返回 >0
 */
int compare_last_n_chars(const char *big_str, const char *son_str, size_t n)
{
    // 获取字符串长度
    size_t len1 = strlen(big_str);
    size_t len2 = strlen(son_str);

    // 如果字符串长度小于 n，直接比较整个字符串
    if (len1 < n || len2 < n)
    {
        return strncmp(big_str, son_str, n);
    }

    // 定位到后 n 个字符
    const char *last_n_str1 = big_str + (len1 - n);
    const char *last_n_str2 = son_str + (len2 - n);

    // 比较后 n 个字符
    return strncmp(last_n_str1, last_n_str2, n);
}
void open_file(const char *argv)
{
    if ((server_read_fd = open(argv, O_RDONLY)) < 0)
    {
        ERROR_EXIT("open");
    }
}

// 创建文件
void create_file(const char *argv)
{
    if ((server_write_fd = open(argv, O_WRONLY | O_CREAT, 0666)) < 0)
    {
        ERROR_EXIT("open");
    }
}

int write_file(int fd, char *arr, int size)
{
    int ret = 0;
    if ((ret = write(fd, arr, size)) < 0)
    {
        ERROR_EXIT("write");
    }
    else
    {
        return ret;
    }
}

int read_file(int fd, char *arr, int size)
{
    int ret = 0;
    if ((ret = read(fd, arr, size)) < 0)
    {
        ERROR_EXIT("read");
    }
    else if (ret == 0)
    {

        return 0;
    }
    else
    {
        return ret;
    }
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
    read(str_tcp->fd_for_client, buf, 1);
    if (buf[0] == '0') // 文件不存在
    {
        return; // 退出当前模式
    }

    // 接收文件名  并创建文件
    bzero(arg_buf, sizeof(arg_buf)); // 清零
    read_file(str_tcp->fd_for_client, arg_buf, BUF_SIZE);
    printf("文件名：%s\n", arg_buf);
    // 接收文件反馈 ，客户端是否有要发送的文件
    //  接收文件名发聩

    create_file((const char *)arg_buf);
    bzero(arg_buf, sizeof(arg_buf)); // 再次清空
    // 设置接收超时为 5 秒
    struct timeval recv_timeout;
    recv_timeout.tv_sec = 0;       // 秒
    recv_timeout.tv_usec = 500000; // 微秒

    if (setsockopt(str_tcp->fd_for_client, SOL_SOCKET, SO_RCVTIMEO, &recv_timeout, sizeof(recv_timeout)) < 0)
    {
        perror("setsockopt failed");
        close(str_tcp->fd_for_client);
        exit(EXIT_FAILURE);
    }
    // 接收数据 并打印
    while (1)
    {
        bzero(arg_buf, sizeof(arg_buf)); // 清零
        int tmp_ret = my_server_use_recv(str_tcp);
        if (tmp_ret >= 0)
        {
            if (tmp_ret == 0)
            {
                close(server_write_fd); // 客户端关闭  通信套接字关闭
                break;
            }
            else if (tmp_ret > 0)
            {
                // 判断是不是当前模式结束指令
                // if (!compare_last_n_chars(arg_buf, "exit", 4))
                // {
                //     puts("************************服务端退出 push 模式****************************");
                //     fflush(stdout);
                //     // 写完文件后，清空缓冲区
                //     bzero(arg_buf, BUF_SIZE);
                //     // 关闭文件
                //     close(server_write_fd);
                //     break; // 退出循环
                // }
                write_file(server_write_fd, arg_buf, tmp_ret);
            }
        }
        else if (tmp_ret < 0)
        {
            puts("************************服务端退出 push 模式****************************");
            recv_timeout.tv_sec = 0;  // 秒
            recv_timeout.tv_usec = 0; // 微秒

            if (setsockopt(str_tcp->fd_for_client, SOL_SOCKET, SO_RCVTIMEO, &recv_timeout, sizeof(recv_timeout)) < 0)
            {
                perror("setsockopt failed");
            }
            fflush(stdout);
            // 写完文件后，清空缓冲区
            bzero(arg_buf, BUF_SIZE);
            // 关闭文件
            close(server_write_fd);
            break; // 退出循环
        }
    }
}
void download_file_to_client(p_tcp str_tcp)
{
    // puts("************************发送文件到客户端***************************");
    // fflush(stdout);
    // 接收发送来的文件名
    bzero(arg_buf, sizeof(arg_buf));
    if (read_file(str_tcp->fd_for_client, arg_buf, BUF_SIZE) > 0) // 接收文件名
    {
        // 判断当前目录是否有该文件
        if (whether_have_file(arg_buf))
        {
            // 没有文件  ，提示发错
            my_server_send(str_tcp, "0", 1);
            return; // 退出当前模式
        }
        else
        {
            my_server_send(str_tcp, "1", 1); // 有文件  发送 1
        }

        printf("客户端要下载的文件名：%s\n", arg_buf);
        // 读取本地文件
        // int tmp = open("tmp.jpg", O_WRONLY | O_CREAT, 0666); //*********测试 */
        open_file(arg_buf);
        while (1)
        {
            bzero(buf, sizeof(buf));
            int read_size = 0;
            if (!(read_size = read_file(server_read_fd, buf, BUF_SIZE))) // 读取文件内容
            {
                close(server_read_fd); // 关闭源文件
                printf("文件发送完毕\n");
                // my_server_send(str_tcp, "exit", 4); // 源文件发送完，发送exit  当前模式结束指令
                break;
            }
            if (read_size > 0)
            {
                my_server_send(str_tcp, buf, read_size);
                // write(tmp, buf, read_size); //*********测试 */
                bzero(buf, sizeof(buf));
            }
        }
    }
}

/****************************发送文案包所需的函数****************************/

// 接收文件并生成压缩包
void recv_file_make_zip(p_tcp str_tcp)
{
    // 接收文件名
    int tmp_ret = 0;
    char get_zip_name[15] = {0}; // 接收的文件名
    bzero(write_zip_name, strlen(write_zip_name));
    bzero(get_zip_name, strlen(get_zip_name));
    if ((tmp_ret = read(str_tcp->fd_for_client, get_zip_name, sizeof(get_zip_name))) < 0) // 修改读取长度为19
    {
        ERROR_EXIT("recv");
    }
    printf("get  client all file in:%s\n", get_zip_name); // 显示文件名
    // 拼接压缩包文件名
    sprintf(write_zip_name, "%s.zip", get_zip_name);
    // write_zip_name[19] = 0;         // 确保字符串以空字符结尾
    // 创建文件
    if ((write_zip_fd = open(write_zip_name, O_WRONLY | O_CREAT, 0666)) < 0)
    {
        ERROR_EXIT("open");
    }
    // 接收文件

    // 设置接收超时
    struct timeval recv_timeout;
    recv_timeout.tv_sec = 1; // 1 秒
    recv_timeout.tv_usec = 0;
    setsockopt(str_tcp->fd_for_client, SOL_SOCKET, SO_RCVTIMEO, &recv_timeout, sizeof(recv_timeout));

    char server_read_buff[1024] = {0};
    while (1)
    {
        // 接收一次
        if ((tmp_ret = recv(str_tcp->fd_for_client, server_read_buff, 1024, 0)) < 0)
        {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
            {
                printf("Timeout\n");
                puts("**********************接收文件完成**************************");
                fflush(stdout);
                // 设置接收超时为 0，恢复默认阻塞行为
                struct timeval recv_timeout;
                recv_timeout.tv_sec = 0;  // 秒
                recv_timeout.tv_usec = 0; // 微秒
                if (setsockopt(str_tcp->fd_for_client, SOL_SOCKET, SO_RCVTIMEO, &recv_timeout, sizeof(recv_timeout)) < 0)
                {
                    perror("setsockopt failed");
                }

                close(write_zip_fd);
                return; // 退出当前模式
            }
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

/**
 * 查询是否含子文件
 * file_name:  文件名
 * return:  0:含有  1:没有
 **/
int whether_have_file(const char *file_name)
{
    DIR *dir;           // 定义一个目录指针
    struct dirent *ptr; // 定义一个目录项指针

    if ((dir = opendir("./")) == NULL) // 打开当前目录
    {
        perror("opendir");
        return 1;
    }
    // 读取目录项
    while ((ptr = readdir(dir)) != NULL) // 读取目录项
    {
        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
        {
            continue; // 跳过当前目录和上层目录
        }
        // 跳过目录
        if (ptr->d_type == DT_DIR)
        {
            continue;
        }
        if (strcmp(ptr->d_name, file_name) == 0)
        {
            closedir(dir);
            return 0;
        }
        else
        {
            // 说明当前文件与要查询的文件不同
            continue;
        }
    }
    // 说明当前目录下没有要查询的文件
    closedir(dir);
    return 1;
}