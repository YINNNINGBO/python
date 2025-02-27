/**实现读取文件的最后一一行* **/
#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp;
    char line[1024];
    char last_line[1024] = "";

    fp = fopen("text.txt", "r");
    if (fp == NULL)
    {
        perror("Failed to open file");
        return 1;
    }

    // fgets 按行读取文件  只要当前行数据不是NULL 就继续读取
    while (fgets(line, sizeof(line), fp) != NULL)
    { // 成功读取后 将当前行数据赋值给last_line
        snprintf(last_line, sizeof(last_line), "%s", line);
    }
    // 读到最后一行后 退出循环  打印最后一行数据
    fclose(fp);

    printf("Last line: %s", last_line);
    return 0;
}