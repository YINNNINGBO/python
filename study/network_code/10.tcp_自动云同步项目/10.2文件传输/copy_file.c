#include "user_file_IO.h"

/**
 * @brief  参数 <可执行文件> <源文件> <生成文件名>
 */
char buf[BUFSIZ] = {0};
int main(int argc, const char *argv[])
{
    ARGC_NUM(argc);
    int read_fd = 0, write_fd = 0;
    if ((read_fd = open(argv[1], O_RDONLY)) < 0)
    {
        ERROR_EXIT("open");
    }
    if ((write_fd = open(argv[2], O_WRONLY | O_CREAT, 0666)) < 0)
    {
        ERROR_EXIT("open");
    }
    while (1)
    {
        bzero(buf, sizeof(buf));
        int tmp_ret = read(read_fd, buf, sizeof(buf));
        if (tmp_ret < 0)
        {
            ERROR_EXIT("read");
        }
        else if (tmp_ret == 0)
        {
            break;
        }
        else
        {
            if (write(write_fd, buf, tmp_ret) < 0)
            {
                ERROR_EXIT("write");
            }
        }
    }
    return 0;
}