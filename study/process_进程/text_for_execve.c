#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, const char **argv) {
  printf("***i am printf for you fun :execve.... my pid is:%d,my father pid "
         "is:%d\n ",
         getpid(), getppid());
  return 0;
}