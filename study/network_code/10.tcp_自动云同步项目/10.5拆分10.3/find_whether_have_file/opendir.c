
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/types.h>
#include <dirent.h>

int whether_have_file(const char *file_name)
{
    DIR *dir;           // 定义一个目录指针
    struct dirent *ptr; // 定义一个目录项指针

    if ((dir = opendir("./")) == NULL) // 打开当前目录
    {
        perror("opendir");
        return 1;
    }
    // 读取目录项
    while ((ptr = readdir(dir)) != NULL) // 读取目录项
    {
        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
        {
            continue; // 跳过当前目录和上层目录
        }
        // 跳过目录
        if (ptr->d_type == DT_DIR)
        {
            continue;
        }
        if (strcmp(ptr->d_name, file_name) == 0)
        {
            closedir(dir);
            return 0;
        }
        else
        {
            // 说明当前文件与要查询的文件不同
            continue;
        }
    }
    // 说明当前目录下没有要查询的文件
    closedir(dir);
    return 1;
}
int main(int argc, char *argv[])
{
    char *file_name = argv[1];
    if (whether_have_file(file_name))
    {
        printf("no\n");
    }
    else
    {
        printf("yes\n");
    }
    return 0;
}