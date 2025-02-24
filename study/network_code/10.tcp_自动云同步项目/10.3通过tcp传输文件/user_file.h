#ifndef __USER_FILE_H__
#define __USER_FILE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

extern int read_fd;
extern int write_fd;
void open_file(const char *argv);
void create_file(const char *argv);
int write_file(int fd, char *arr, int size);
int read_file(int fd, char *arr, int size);

#endif /* __USER_FILE_H__ */