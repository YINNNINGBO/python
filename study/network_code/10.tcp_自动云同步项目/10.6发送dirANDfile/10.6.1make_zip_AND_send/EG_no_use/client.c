#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ftw.h>

#define PORT 12345
#define BUFFER_SIZE 4096

int sock;
char *target_dir;

void send_data(const void *data, size_t len)
{
    size_t sent = 0;
    while (sent < len)
    {
        ssize_t n = send(sock, (char *)data + sent, len - sent, 0);
        if (n <= 0)
        {
            perror("send failed");
            exit(EXIT_FAILURE);
        }
        sent += n;
    }
}

uint64_t htonq(uint64_t val)
{
    return (((uint64_t)htonl(val)) << 32) | htonl(val >> 32);
}

void send_file(const char *path)
{
    FILE *fp = fopen(path, "rb");
    if (!fp)
    {
        perror("fopen failed");
        return;
    }

    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // 发送文件头
    uint8_t type = 'F';
    uint32_t path_len = htonl(strlen(path));
    uint64_t size = htonq(file_size);

    send_data(&type, 1);
    send_data(&path_len, 4);
    send_data(path, strlen(path));
    send_data(&size, 8);

    // 发送文件内容
    char buffer[BUFFER_SIZE];
    while (file_size > 0)
    {
        size_t read_size = fread(buffer, 1, sizeof(buffer), fp);
        if (read_size <= 0)
            break;
        send_data(buffer, read_size);
        file_size -= read_size;
    }

    fclose(fp);
}

int send_entry(const char *fpath, const struct stat *sb, int typeflag)
{
    if (typeflag == FTW_F)
    { // 文件
        // 跳过客户端程序自身
        if (strstr(fpath, "client") != NULL)
            return 0;

        char relative_path[PATH_MAX];
        strcpy(relative_path, &fpath[2]); // 去掉"./"
        send_file(relative_path);
    }
    else if (typeflag == FTW_D)
    { // 目录
        char relative_path[PATH_MAX];
        strcpy(relative_path, &fpath[2]);

        uint8_t type = 'D';
        uint32_t path_len = htonl(strlen(relative_path));

        send_data(&type, 1);
        send_data(&path_len, 4);
        send_data(relative_path, strlen(relative_path));
    }
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <server_ip> <target_dir>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    target_dir = argv[2];
    struct sockaddr_in server_addr;

    // 创建socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);

    // 连接服务器
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }

    // 发送目标目录名
    uint32_t dir_len = htonl(strlen(target_dir));
    send_data(&dir_len, 4);
    send_data(target_dir, strlen(target_dir));

    // 遍历当前目录
    ftw(".", send_entry, 20);

    close(sock);
    return 0;
}