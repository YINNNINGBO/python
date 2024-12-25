#include "user.h"

/**
 * sem_init 用于线程中   匿名信号量         sem_destroy销毁   退出时自动清理
 * sem_open 用于进程中   有名（命名）信号量  sem_unlink销毁    退出时自动清理
 */

// 定义共享内存路径和大小
#define SHM_FILE_PATH "/shm_example"
#define SHM_FILE_SIZE 1024

// 定义信号量名称
#define SEM_EMPTY "/sem_empty" // 控制共享内存是否空
#define SEM_FULL "/sem_full"   // 控制共享内存是否有数据
#define SEM_MUTEX "/sem_mutex" // 控制父子进程交替

int main()
{
    // 创建或打开共享内存
    int fd = shm_open(SHM_FILE_PATH, O_RDWR | O_CREAT, 0664);
    if (fd < 0)
    {
        perror("shm_open failed");
        exit(EXIT_FAILURE);
    }

    // 设置共享内存大小
    if (ftruncate(fd, SHM_FILE_SIZE) < 0)
    {
        perror("ftruncate failed");
        exit(EXIT_FAILURE);
    }

    // 映射共享内存到虚拟内存
    char *shm_ptr = mmap(NULL, SHM_FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shm_ptr == MAP_FAILED)
    {
        perror("mmap failed");
        shm_unlink(SHM_FILE_PATH);
        exit(EXIT_FAILURE);
    }

    // 创建信号量

    sem_t *sem_empty = sem_open(SEM_EMPTY, O_CREAT, 0664, 1); // 初始值为1，表示共享内存为空
    sem_t *sem_full = sem_open(SEM_FULL, O_CREAT, 0664, 0);   // 初始值为0，表示共享内存没有数据
    sem_t *sem_mutex = sem_open(SEM_MUTEX, O_CREAT, 0664, 1); // 初始值为1，控制父子进程交替

    if (sem_empty == SEM_FAILED || sem_full == SEM_FAILED || sem_mutex == SEM_FAILED)
    {
        perror("sem_open failed");
        shm_unlink(SHM_FILE_PATH);
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork failed");
        _exit(EXIT_FAILURE);
    }

    if (pid == 0) // 子进程
    {
        // 子进程：读取共享内存数据
        for (int i = 0; i < 5; i++) // 读取5次
        {
            sem_wait(sem_full);  // P操作，等待直到共享内存有数据     1-1 = 0
            sem_wait(sem_mutex); // P操作，获取父子进程交替的控制权   1-1 = 0

            // 读取并打印数据
            printf("子进程读取数据: %s\n", shm_ptr);

            sem_post(sem_mutex); // V操作，释放控制权                    0+1 = 1
            sem_post(sem_empty); // V操作，表示共享内存为空，可以写入数据 0+1 =1

            usleep(100000); // 延迟一下，模拟读取操作
        }
        exit(0);
    }
    else // 父进程
    {
        // 父进程：写入共享内存数据
        for (int i = 0; i < 5; i++) // 写入5次
        {
            sem_wait(sem_empty); // P操作，等待直到共享内存为空:    1  -1  =0
            sem_wait(sem_mutex); // P操作，获取父子进程交替的控制权 1  -1  = 0

            // 写入数据到共享内存
            sprintf(shm_ptr, "父进程写入数据: %d", i + 1);
            printf("父进程写入数据: %s\n", shm_ptr);

            sem_post(sem_mutex); // V操作，释放控制权             0  +1  =1
            sem_post(sem_full);  // V操作，表示共享内存有数据，可以供子进程读取   0 +1 =1

            usleep(100000); // 延迟一下，模拟写入操作
        }

        waitpid(pid, NULL, 0); // 等待子进程结束

        // 清理工作
        sem_close(sem_empty);      // 关闭信号量
        sem_close(sem_full);       // 关闭信号量
        sem_close(sem_mutex);      // 关闭信号量
        sem_unlink(SEM_EMPTY);     // 删除信号量
        sem_unlink(SEM_FULL);      // 删除信号量
        sem_unlink(SEM_MUTEX);     // 删除信号量
        shm_unlink(SHM_FILE_PATH); // 删除共享内存对象
    }

    // 解除映射
    if (munmap(shm_ptr, SHM_FILE_SIZE) < 0) // 解除共享内存的映射
    {
        perror("munmap failed"); // 打印解除映射失败的错误信息
    }

    // 关闭文件描述符
    close(fd); // 关闭共享内存文件描述符

    return 0; // 程序结束
}
