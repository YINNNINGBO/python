#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main()
{
    pid_t pid = fork();

    if (pid == 0)
    {
        // 子进程
        printf("I am child process, pid = %d\n", getpid());
    }
    else if (pid > 0)
    {
        // 父进程
        printf("I am parent process, pid = %d\n", getpid());
    }
    else
    {
        perror("fork");
        return 1;
    }
    return 0;
}