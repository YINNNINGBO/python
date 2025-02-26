#include "client_use.h"

char buf[BUF_SIZE] = {0};     // 缓冲区
char arg_buf[BUF_SIZE] = {0}; // 命令缓冲区

char client_arg_buf[BUF_SIZE] = {0}; // 存储客户端参数
char source_file_name[40] = {0};
char copy_file_name[40] = {0};
int client_read_fd = 0;        // 读取文件描述符
int client_write_fd = 0;       // 写入文件描述符
char send_file_name[20] = {0}; // 保存接收到的文件名
int read_zip_fd = -1;          // 保存文件描述符

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

    return ptcp->fd;
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
    if ((client_read_fd = open(argv, O_RDONLY)) < 0)
    {
        ERROR_EXIT("open");
    }
}

// 创建文件
void create_file(const char *argv)
{
    if ((client_write_fd = open(argv, O_WRONLY | O_CREAT, 0666)) < 0)
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

// 打开源文件 发送生成文件名
void push_file(p_tcp str_tcp, const char *soure_name, const char *copy_file_name)
{

    if (whether_have_file(soure_name)) // 判断当前目录是否有该文件
    {
        // 没有文件  ，提示发错
        my_client_send(str_tcp, "0", 1);
        puts("当前目录没有该源文件，退出该模式\n");
        return; // 退出当前模式
    }
    else
    {
        my_client_send(str_tcp, "1", 1); //
    }
    open_file(soure_name);                                                   // 文件存在 打开源文件
    write_file(str_tcp->fd, (char *)copy_file_name, strlen(copy_file_name)); // 发送文件名
    puts("已经发发送文件名\n");
    while (1)
    {
        bzero(buf, BUF_SIZE);
        int read_size = 0;
        if ((read_size = read_file(client_read_fd, buf, BUF_SIZE))) // 读取文件内容
        {
            my_client_send(str_tcp, buf, read_size);
            bzero(buf, BUF_SIZE);
        }
        if (read_size == 0)
        {
            close(client_read_fd); // 关闭源文件
            puts("exit");
            fflush(stdout);
            // my_client_send(str_tcp->fd, "exit", strlen("exit")); // 源文件发送完，发送exit  当前模式结束指令
            break; // 退出循环
        }
    }
}

/******获取服务端数据***********/
void show_file(p_tcp str_tcp)
{
    bzero(client_arg_buf, sizeof(client_arg_buf));
    // char *tmp_buf = malloc(40);

    // 发送命令
    puts("************************发送命令(exit:退出当前模式)***********************");
    while (scanf("%s", client_arg_buf) > 0) // client   在终端 接收用户命令
    {
        if (client_arg_buf[strlen(client_arg_buf) - 1] == '\n')
        {
            client_arg_buf[strlen(client_arg_buf) - 1] = '\0';
        }
        printf("客户端发送命令%s\n", client_arg_buf);                         // 显示输入命令
        if (!my_client_send(str_tcp, client_arg_buf, strlen(client_arg_buf))) // 向服务端发送数据
        {
            if (!strncmp(client_arg_buf, "exit", 4))
            {
                bzero(client_arg_buf, strlen(client_arg_buf));
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
            // if (tmp_ret == 0){

            // }
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
    if (scanf("%s %s", source_file_name, copy_file_name) > 0) // client   在终端 接收用户命令
    {
        // 创建文件
        printf("source_file_name:%s , copy_file_name:%s\n", source_file_name, copy_file_name);

        // 设置接收超时
        struct timeval recv_timeout;
        recv_timeout.tv_sec = 1; // 1 秒
        recv_timeout.tv_usec = 0;
        setsockopt(str_tcp->fd, SOL_SOCKET, SO_RCVTIMEO, &recv_timeout, sizeof(recv_timeout));
        // 向服务端发送要获取的文件名
        if (!(my_client_send(str_tcp, source_file_name, strlen(source_file_name))))
        {
            // 接收文件名发聩
            read(str_tcp->fd, buf, 1);
            if (buf[0] == '0') // 文件存在
            {
                puts("服务端没有索要的文件，退出该模式");
                return; // 退出当前模式
            }
            create_file(copy_file_name); // 直接对client_write_fd赋值
            bzero(buf, BUF_SIZE);        // 刷新缓冲区
            int tmp_ret = 0;
            while ((tmp_ret = recv(str_tcp->fd, buf, BUF_SIZE, 0)) > 0)
            {
                // if (!compare_last_n_chars(buf, "exit", 4)) // 如果接收到exit  说明  发送完
                // {
                //     puts("**********************接收文件完成**************************");
                //     fflush(stdout);
                //     close(client_write_fd);
                //     return; // 退出当前模式
                //    }
                write_file(client_write_fd, buf, tmp_ret);
                bzero(buf, BUF_SIZE); // 刷新缓冲区
            }

            if (errno == EAGAIN || errno == EWOULDBLOCK)
            {
                printf("Timeout\n");
                puts("**********************接收文件完成**************************");
                fflush(stdout);
                recv_timeout.tv_sec = 0; // 0 秒
                recv_timeout.tv_usec = 0;
                setsockopt(str_tcp->fd, SOL_SOCKET, SO_RCVTIMEO, &recv_timeout, sizeof(recv_timeout));
                close(client_write_fd);
                return; // 退出当前模式
            }
            // if (tmp_ret == 0)
            // {
            //     puts("**********************接收文件完成**************************");
            //     fflush(stdout);
            //     close(client_write_fd);
            //     return; // 退出当前模式
            // }
        }
    }
}

/**********************发送文件包所需函数***********/
int client_send_file_name(p_tcp str_tcp)
{
    // 1.压缩当前所有文件名
    if (system("zip -r tmp.zip ./*") < 0)
    {
        ERROR_EXIT("system");
    }
    // 2.接收文件名
    puts("输入临时写入压缩包文件名\n");
    bzero(send_file_name, 20);
    scanf("%s", send_file_name);
    if (send_file_name[strlen(send_file_name) - 1] == '\n')
    {
        send_file_name[strlen(send_file_name) - 1] = 0;
    }
    // 3.发送文件名
    my_client_send(str_tcp, send_file_name, strlen(send_file_name));

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
            my_client_send(str_tcp, buf, ret_num);
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