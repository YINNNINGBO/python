#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_BUF_LEN 100
#define OPEN_FILE "1.txt"
#define DXECVE_PATH                                                            \
  "/home/linux/Desktop/gitee_linux_c/study/process_进程/text_for_execve"
int main(int argc, const char **argv) {
  char buf[MAX_BUF_LEN];
  int fd = open(OPEN_FILE, O_RDWR | O_CREAT, 0665);
  if (fd < 0) {
    perror("open file is failed!\n");
    return -1;
  }
  printf("在创建子进程之前，当前是父进程%d\n", getpid());
  pid_t pid = fork();
  if (pid < 0) {
    // fork  error
    perror("fork is failed!\n");
    return -1;
  } else if (pid == 0) {
    //子进程
    sprintf(buf, "i am child process %d,my father process is %d\n", getpid(),
            getppid());
    puts(buf);
    int ret_data = write(fd, buf, strlen(buf));
    if (ret_data < 0) {
      perror("child  write is failed!\n");
    }
    // 执行 execve
    char *args[] = {"./text_for_execve", NULL};
    sleep(1); // 等待疫苗保证  父进程 先被exit 杀死  使子进程成为孤儿进程
    close(fd);
    ret_data = execve(DXECVE_PATH, args, NULL);
    if (ret_data < 0) {
      perror("execeve is failed!!\n");
      return -1;
    }

  } else {
    //父进程s
    int ret_state = 0;
    //  sleep(1);
    sprintf(buf, "i am father process :%d,my childe process is %d\n", getpid(),
            pid);
    puts(buf);
    int ret_data = write(fd, buf, strlen(buf));
    if (ret_data < 0) {
      perror("father process write is failed !\n");
    }
    /*这里是等待子进程运行结束，注释掉之后，子进程可能成为孤儿进程，孤儿进程的父进程是init进程**/
    // pid_t ret_pid = waitpid(pid, &ret_state, 0);
    // if (ret_pid < 0) {
    //   perror("waitpid is failed in father process!\n");
    // }
    close(fd);
    exit(0);
  }
  return 0;
}