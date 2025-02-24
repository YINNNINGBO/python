#include "user.h"
int main(int argc, const char *argv[])
{
    DIR *dir;           // 定义一个目录指针
    struct dirent *ptr; // 定义一个目录项指针

    if ((dir = opendir("../")) == NULL) // 打开上层目录
    {
        perror("opendir");
        return 1;
    }
    while ((ptr = readdir(dir)) != NULL) // 读取目录项
    {
        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
        {
            continue; // 跳过当前目录和上层目录
        }
        printf("文件名: %s\t", ptr->d_name);
        switch (ptr->d_type)
        {
        case DT_REG:
            printf("\ttypr: file\n");
            break;
        case DT_DIR:
            printf("\ttypr: dir\n");
            break;
        case DT_LNK:
            printf("\ttypr: symbolic link\n"); // 符号链接
            break;
        default:
            printf("\ttypr: other or don`t know\n");
        }
    }
    return 0;
}