#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <dirent.h>

#define PORT 12345
#define BUFFER_SIZE 4096
#define PATH_BUFFER_SIZE 8192

void recv_all(int sock, void *buffer, size_t len)
{
    size_t received = 0;
    while (received < len)
    {
        ssize_t n = recv(sock, (char *)buffer + received, len - received, 0);
        if (n <= 0)
        {
            perror("recv failed");
            exit(EXIT_FAILURE);
        }
        received += n;
    }
}

void create_path(const char *path)
{
    char tmp[PATH_MAX];
    char *p = NULL;
    size_t len;

    snprintf(tmp, sizeof(tmp), "%s", path);
    len = strlen(tmp);
    if (tmp[len - 1] == '/')
        tmp[len - 1] = 0;

    for (p = tmp + 1; *p; p++)
    {
        if (*p == '/')
        {
            *p = 0;
            mkdir(tmp, 0777);
            *p = '/';
        }
    }
    mkdir(tmp, 0777);
}

uint64_t ntohq(uint64_t val)
{
    return (((uint64_t)ntohl(val)) << 32) | ntohl(val >> 32);
}

int main()
{
    int server_fd, client_sock;
    struct sockaddr_in address;

    // 创建socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // 绑定端口
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // 监听
    if (listen(server_fd, 3) < 0)
    {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1)
    {
        socklen_t addrlen = sizeof(address);
        if ((client_sock = accept(server_fd, (struct sockaddr *)&address, &addrlen)) < 0)
        {
            perror("accept failed");
            continue;
        }

        // 接收目标目录名
        uint32_t dir_len;
        recv_all(client_sock, &dir_len, 4);
        dir_len = ntohl(dir_len);

        char target_dir[PATH_MAX];
        recv_all(client_sock, target_dir, dir_len);
        target_dir[dir_len] = '\0';
        create_path(target_dir);

        // 接收文件数据
        while (1)
        {
            uint8_t type;
            if (recv(client_sock, &type, 1, MSG_PEEK) <= 0)
                break;
            recv_all(client_sock, &type, 1);

            if (type == 'D')
            { // 目录
                uint32_t path_len;
                recv_all(client_sock, &path_len, 4);
                path_len = ntohl(path_len);

                char path[PATH_MAX];
                recv_all(client_sock, path, path_len);
                path[path_len] = '\0';

                char full_path[PATH_BUFFER_SIZE];
                snprintf(full_path, sizeof(full_path), "%s/%s", target_dir, path);
                create_path(full_path);
            }
            else if (type == 'F')
            { // 文件
                uint32_t path_len;
                recv_all(client_sock, &path_len, 4);
                path_len = ntohl(path_len);

                char path[PATH_MAX];
                recv_all(client_sock, path, path_len);
                path[path_len] = '\0';

                uint64_t file_size;
                recv_all(client_sock, &file_size, 8);
                file_size = ntohq(file_size);

                char full_path[PATH_BUFFER_SIZE];
                snprintf(full_path, sizeof(full_path), "%s/%s", target_dir, path);
                create_path(full_path);

                FILE *fp = fopen(full_path, "wb");
                if (!fp)
                {
                    perror("fopen failed");
                    continue;
                }

                while (file_size > 0)
                {
                    char buffer[BUFFER_SIZE];
                    size_t read_size = file_size > sizeof(buffer) ? sizeof(buffer) : file_size;
                    recv_all(client_sock, buffer, read_size);
                    fwrite(buffer, 1, read_size, fp);
                    file_size -= read_size;
                }
                fclose(fp);
            }
        }

        printf("Received all files in directory: %s\n", target_dir);
        close(client_sock);
    }

    return 0;
}