#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main()
{
    FILE *fp;
    char path[1035];

    char buf[100] = {0};
    // 使用popen执行ls -al命令并读取输出
    while (1)
    {
        // 读取用户输入的命令
        if (read(STDIN_FILENO, buf, 100) > 0)
        {
            fp = popen((const char *)buf, "r");
            if (fp == NULL)
            {
                printf("Failed to run command\n");
                exit(1);
            }
            // 读取命令输出，直到没有更多输出
            while (fgets(path, sizeof(path) - 1, fp) != NULL)
            {
                write(STDOUT_FILENO, path, strlen(path));
            }
        }
    }

    // 关闭文件指针
    pclose(fp);

    return 0;
}
