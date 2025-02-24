#ifndef __USER_FILE_IO_H__
#define __USER_FILE_IO_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*************************参数个数检测*****************************/
#define ARGC_NUM(argc)                                                          \
    do                                                                          \
    {                                                                           \
        if (3 != argc)                                                          \
        {                                                                       \
            printf("Usage: %s <source_file_name> <save_file_name>\n", argv[0]); \
            exit(EXIT_FAILURE);                                                 \
        }                                                                       \
    } while (0)

/* 错误提示 原因 位置*/
#define ERROR_EXIT(msg)                                          \
    do                                                           \
    {                                                            \
        perror("msg");                                           \
        printf("file is %s , line is %d\n", __FILE__, __LINE__); \
        exit(EXIT_FAILURE);                                      \
    } while (0)
#endif /* __USER_FILE_IO_H__ */