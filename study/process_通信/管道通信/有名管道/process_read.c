/*
              有名管道   又称：先进先出管道
            相比匿名管道， 两个进程不需要有父子关系或兄弟关系
            一个管道只能做到类半双工， 有个管道可以做到类型全双工 （匿名同理）
            使用 api: mkfifo (const char *pathname, mode_t mode);
           pathname :临时文件 一般创建再/tmp/xxx   路径下
            mode     : 权限  eg: 0664

*/
// 这个文件实现享有名管道中写
#include "process.h"

int main(int argc, const char **argv)
{
    // 打开管道文件
    int fd = open(FIFO_PATHNAME, O_RDONLY);
    if (fd < 0)
    {
        perror("open fifo file is failed!");
        _exit(EXIT_FAILURE);
    }
    // 送终端中读取数据
    char tmp_arr[TEM_BUF_SIZE];

    if (read(fd, tmp_arr, TEM_BUF_SIZE) < 0)
    {
        perror("read is failed!!");
        _exit(EXIT_FAILURE);
    }
    puts(tmp_arr);
    // 等待read进程

    // if (waitpid(read_pid, NULL, 0) < 0)
    // {
    //     perror("wait is error!");
    //     _exit(EXIT_FAILURE);
    // }
    // 删除文件
    close(fd);
    if (unlink(FIFO_PATHNAME) < 0)
    {
        perror("unlink is failed!");
        _exit(EXIT_FAILURE);
    }
    return 0;
}
