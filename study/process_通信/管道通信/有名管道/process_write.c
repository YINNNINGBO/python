/*
              有名管道   又称：先进先出管道
            相比匿名管道， 两个进程不需要有父子关系或兄弟关系
            一个管道只能做到类半双工， 有个管道可以做到类型全双工 （匿名同理）
            使用 api: mkfifo (const char *pathname, mode_t mode);
           pathname :临时文件 一般创建再/tmp/xxx   路径下
            mode     : 权限  eg: 0664

*/
// 这个文件实现向有名管道中读
#include "process.h"

int main(int argc, const char **argv)
{
    // // 检测参数
    // if (argc < 2)
    // {
    //     fprintf(stderr, "请填写要传入的信息:%s ", argv[1]);
    //     exit(EXIT_FAILURE);
    // }

    // 创建管道
    if (mkfifo(FIFO_PATHNAME, 0664) < 0)
    {
        perror("mkfifo is failed!");
        if (errno == EEXIST) // 判断是否是文件已经创建
        {
            unlink(FIFO_PATHNAME);
            _exit(EXIT_FAILURE);
        }
    }
    // 打开fifo文件
    // get this proces  pid
    pid_t read_pid = getpid();
    int fd = open(FIFO_PATHNAME, O_RDWR | O_CREAT, 0664);
    if (fd < 0)
    {
        perror("open fifo file   is error!");
        _exit(EXIT_FAILURE);
    }
    // 从管道文件中写取数据

    char tmp_arr[TEM_BUF_SIZE];
    sprintf(tmp_arr, "I'm write process, my pid is %d,\n", read_pid);

    // 写入数据到管道
    if (write(fd, tmp_arr, strlen(tmp_arr)) < 0)
    {
        perror("Error writing to FIFO");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Message written to FIFO: %s", tmp_arr);
    while (1)
        ;
    // 关闭设备文件
    close(fd);

    return 0;
}
