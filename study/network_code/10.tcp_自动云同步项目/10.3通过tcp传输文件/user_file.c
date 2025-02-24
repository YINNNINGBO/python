#include "user_file.h"
#include "tcp.h"
extern int read_fd; // 在 客户端文件中定义 确保server  client 的 read_fd  write_fd  不冲突
extern int write_fd;

void open_file(const char *argv)
{
    if ((read_fd = open(argv, O_RDONLY)) < 0)
    {
        ERROR_EXIT("open");
    }
}

// 创建文件
void create_file(const char *argv)
{
    if ((write_fd = open(argv, O_WRONLY | O_CREAT, 0666)) < 0)
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
