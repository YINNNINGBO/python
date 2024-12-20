#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define OPEN_CREATE "1.txt"
#define MAX_BUF_LEN 100
int main(int argc, const char **argv) {
  char buf[MAX_BUF_LEN];
  // 打开并创建文件
  int fd = open(OPEN_CREATE, O_RDWR | O_CREAT, 0665);
  if (fd == -1) {
    perror("open file is error!\n");
    return -1;
  }
  //从标准数据接收数据
  ssize_t ret_byte_num = read(fileno(stdin), buf, MAX_BUF_LEN);
  if (ret_byte_num < 0) {
    perror("read is error!\n");
  }
  puts("输入要读取的内容");
  puts(buf);
  //将数据写入文件内
  ret_byte_num = write(fd, buf, MAX_BUF_LEN);
  if (ret_byte_num < 0) {
    perror("write is error! \n");
  }
  if (lseek(fd, 0, SEEK_SET) < 0) {
    perror("lseek id failed");
    close(fd);
    return 1;
  }
  memset(buf, 0, MAX_BUF_LEN);
  //将数据从fd 中读出
  ret_byte_num = read(fd, buf, MAX_BUF_LEN);
  if (ret_byte_num < 0) {
    perror("read is failed!\n");
  }
  puts("输出文件内的内容");
  puts(buf);
  return 0;
}