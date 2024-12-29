#ifndef __USER_H__
#define __USER_H__

#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/wait.h>

#define BUF_SIZE 50 // 缓冲区大小
#define BACKLOG 10  // 同使监听的客户端数量

#endif /* __USER_H__ */