#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>    /* For O_* constants */
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define SHM_FILE_SIZE 1024
#define SHM_FILE_PATH "shm_fd"
int main(int argc, const char **argv)
{
    // 创建共享内存
    int fd = shm_open(SHM_FILE_PATH, O_RDWR | O_CREAT, 0664);
    if (fd < 0)
    {
        perror("shm_open is failed!");
        _exit(EXIT_FAILURE);
    }
    // 设置共享内存大小
    if (ftruncate(fd, SHM_FILE_SIZE) < 0)
    {
        perror("ftruncate is failed!");
        _exit(EXIT_FAILURE);
    }
    // 映射到虚拟内存
    char *re_addr = mmap(NULL, SHM_FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (re_addr == MAP_FAILED)
    {
        perror("mmap is failed!");
        shm_unlink(SHM_FILE_PATH);
        return EXIT_FAILURE;
    }

    // 创建父子进程
    pid_t pid = fork();
    char tmp_arr[100];
    if (pid < 0)
    {
        perror("fork is error!");
        _exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        // 子进程
        // if(read(fd,tmp_arr,100) < 0){
        //     perror("child process read is failed!");
        //     return EXIT_FAILURE;
        // }
        fprintf(stdout, "得到父进程消息->: %s", re_addr);
    }
    else
    {
        // 父进程
        sprintf(tmp_arr, "我是父进程%d,我告诉子进程他是%d\n", getpid(), pid);
        strcpy(re_addr, tmp_arr);
        // if (write(fd, tmp_arr, strlen(tmp_arr)) < 0)
        // {
        //     perror("father process write to child process is failed!");
        //     _exit(EXIT_FAILURE);
        // }
        // 等待子进程读取
        waitpid(pid, NULL, 0);
        // 删除共享内存对象 之许哟啊做一次
        if (shm_unlink(SHM_FILE_PATH) < 0)
        {
            perror("shm_unlink is failed!!");
            _exit(EXIT_FAILURE);
        }
    }

    // 释放内存映射， 关闭文件描述符   父子进程都要做的
    // 解除映射
    if (munmap(re_addr, SHM_FILE_SIZE) < 0)
    {
        perror("munmap");
    }

    // 关闭文件
    close(fd);
    return 0;
}