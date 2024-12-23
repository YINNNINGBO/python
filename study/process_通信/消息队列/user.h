#ifndef __USER_H__
#define __USER_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <mqueue.h>
#include <string.h>
#include <time.h>

#define PATH_MQ "/te_mq2" // 创建队列文件名
#define MAX_M_NUM 10      // 队列的信息条数
#define MAX_ONE_M_len 50  // 每条信息的长度

#endif