#include "tcp.h"
char buf[BUF_SIZE] = {0};     // 缓冲区
char arg_buf[BUF_SIZE] = {0}; // 命令缓冲区
/*if this file is server.c socket->listen ;if this file is client.c socket->connect
 *   ptcp: 通信结构体
 *   server_or_client: 1= server ；2= client
 *  @return: 通信套接字  0:fail
 */
int my_socket(p_tcp ptcp, int server_or_client, const char *t_argv[])
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
    if (server_or_client == SERVER) // 如果当前是服务器
    {
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
    }
    else if (server_or_client == CLIENT) // 如果当前是客户端
    {
        // 设置服务器地址
        ptcp->server_addr.sin_family = AF_INET;                             // 协议族
        ptcp->server_addr.sin_port = htons(PORT);                           // 端口号
        if (inet_pton(AF_INET, t_argv[1], &ptcp->server_addr.sin_addr) < 0) // IP地址
        {
            ERROR_EXIT("client inet_pton");
        }
        if (connect(ptcp->fd, (struct sockaddr *)&ptcp->server_addr, (socklen_t)sizeof(ptcp->server_addr)) < 0)
        {
            ERROR_EXIT("connect");
        }
    }
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
        ERROR_EXIT("recv");
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

/**
 * @breif: 客户端发送服务端数据
 * @return :  sucess=0;
 */
int my_client_send(p_tcp ptcp, const char *str, int len)
{
    int ret = 0;
    if ((ret = send(ptcp->fd, str, len, 0)) < 0)
    {
        ERROR_EXIT("send");
    }
    return 0;
}

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

    while (1)
    {
        // 读取用户输入的命令   使用通信套接字
        bzero(arg_buf, 100);
        if (read(str_tcp->fd_for_client, arg_buf, 100) > 0) // 接收命令
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