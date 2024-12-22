#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
//管道是单向通讯
/***匿名管道 测试
 *   管道是使用内核空间的   内存空间有限，且存储特殊
 *   故再read时，
 * 《因该一个字节一个字节去读取》* 将程序传入的 >2 个参数 pipe  参数
 *是长度为 2 一个字符串  0：管道读端 1：管道写端
 **/
int main(int argc, const char **argv) {
  //检测参数
  if (argc < 2) {
    fprintf(stderr, "%s.请填写要传入的信息", argv[0]);
    exit(EXIT_FAILURE);
  }

  //创建管道
  int pipefd[2];
  if (pipe(pipefd) < 0) {
    perror("pipe is failed!");
    _exit(EXIT_FAILURE);
  }
  //创建进程
  pid_t pid = fork();
  if (pid < 0) {
    perror("fork is error!!");
    exit(EXIT_FAILURE);
  } else if (pid == 0) {
    //子进程
    close(pipefd[1]); // 关闭管道 写
    char *str = "新学员信息!\n";

    write(STDOUT_FILENO, str, strlen(str));
    char buf;
    while (read(pipefd[0], &buf, 1)) {
      write(STDOUT_FILENO, &buf, 1);
    }
    putchar('\n');
    close(pipefd[0]);
    _exit(EXIT_FAILURE);
  } else {
    //父进程
    close(pipefd[0]); //关闭管道 读
    // char str[30] = "我是老学员!\n";
    int ret = write(pipefd[1], argv[1], strlen(argv[1])); //向管道内写
    if (ret < 0) {
      perror("write is failed!");
    }
    close(pipefd[1]); //写完关闭  写通道
    pid_t r_pid = waitpid(pid, NULL, 0);
    if (r_pid < 0) {
      _exit(EXIT_FAILURE);
    }
  }
  return 0;
}
/*
管道相关 概念要点简述

    ：管道在使用过程层中  在不同进程 分别有一对管道
    ：一堆管道中有 read  write  两个方向
    使用技巧  eg：
            在A进程中B进程数据read时 ，要关闭该进程内的write  在write后
在关闭write。


什么时匿名管道？
    ；  特点：
        没有名字：匿名管道在文件系统中没有名字，它是通过进程的文件描述符来访问的。
        只能在相关进程间通信：通常只能用于父进程和子进程之间或具有亲缘关系的进程之间通信，因为匿名管道需要由创建进程打开并传递文件描述符给子进程或其他相关进程。
        生命周期：匿名管道的生命周期是由创建它的进程决定的，当管道的两端都被关闭后，管道才会被销毁。
        创建方式：通过 pipe() 系统调用来创建。
使用技巧：
    先 使用pipe创建管道
    然后再fork  创建进程
*/