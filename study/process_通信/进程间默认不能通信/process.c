#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

/********不同进程默认是不能通信的*********/
int num = 1;
int main(int argc, const char **argv) {

  pid_t pid = fork();
  if (pid == 0) {
    //子进程
    num = 2;
    printf("子进程%d中  num = %d\n", getpid(), num);
  } else {
    //父进程
    sleep(1);
    printf("父进程%d中  num = %d\n", getpid(), num); //父进程中打印结果还是 1
  }
  return 0;
}