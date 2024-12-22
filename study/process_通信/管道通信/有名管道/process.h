#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define FIFO_PATHNAME "/tmp/mkfifo" // 创建有名管道 临时文件
#define TEM_BUF_SIZE 100            // 缓冲区 大小
