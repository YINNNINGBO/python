
#ifndef __USER_H__
#define __USER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>    /* For O_* constants */
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <errno.h>

#define SHM_FILE_PATH "/shm_example"
#define SHM_FILE_SIZE 1024

#endif /* __USER_H__ */