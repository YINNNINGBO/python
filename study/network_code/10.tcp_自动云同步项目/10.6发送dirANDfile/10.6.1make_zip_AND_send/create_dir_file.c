#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

/**
 * 发送文件名  将当前目录下的文件打包成压缩包再创建一个目录，将压缩包放入目录中
 * 1.接收1个文件名
 * 2.将文件打包成压缩包（本质是一个文件）    zip -r 压缩包名 文件名
 * 3.创建一个文件   tmp.zip
 * 4.读取压缩包数据，写入新的压缩包中
 */

int main(int argc, char *argv[])
{
    int tmp_ret = 0;
    int read_zip_fd = 0, write_zip_fd = 0;
    char zip_file_name[40] = {0}; // 接收临时写入压缩包文件名
    char tmp_arg_buf[60] = {0};   // 处理解压命令
    char buf[BUFSIZ] = {0};       // 读取临时压缩包数据

    // 压缩当前所有文件到tmp.zip
    if ((tmp_ret = system("zip -r tmp.zip *")) < 0) // tmp.zip为临时压缩包名
    {
        perror("system");

        exit(EXIT_FAILURE);
    }
    // 创建read tmp.zip文件的fd
    if ((read_zip_fd = open("tmp.zip", O_RDONLY)) < 0)
    {
        perror("open");
        printf("line is %d\n", __LINE__);
        exit(EXIT_FAILURE);
    }

    puts("输入你要创建的压缩包文件名\n");
    // 接收文件名
    scanf("%s", zip_file_name);
    printf("创建的写入压缩包文件名为:%s\n", zip_file_name);

    // 创建写入压缩包文件
    if ((write_zip_fd = open(zip_file_name, O_WRONLY | O_CREAT, 0666)) < 0)
    {
        perror("open");
        printf("line is %d\n", __LINE__);
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        // 读取压缩包数据，写入新的压缩包中
        if ((tmp_ret = read(read_zip_fd, buf, sizeof(buf))) < 0)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }
        if (tmp_ret == 0)
        {
            break;
        }
        if ((tmp_ret = write(write_zip_fd, buf, tmp_ret)) < 0)
        {
            perror("write");
            exit(EXIT_FAILURE);
        }
        bzero(buf, sizeof(buf)); // 数据清除
    }

    // 删除临时压缩包
    // if ((tmp_ret = system("rm -rf tmp.zip")) < 0)
    // {
    //     perror("system");
    //     exit(EXIT_FAILURE);
    // }

    // // 解压写入临时压缩包
    // bzero(tmp_arg_buf, sizeof(tmp_arg_buf));
    // sprintf(tmp_arg_buf, "unzip %s", zip_file_name);
    // if ((tmp_ret = system(tmp_arg_buf)) < 0)
    // {
    //     perror("system");
    //     exit(EXIT_FAILURE);
    // }

    // // 删除写入的压缩包
    // bzero(tmp_arg_buf, sizeof(tmp_arg_buf));
    // sprintf(tmp_arg_buf, "rm -rf %s", zip_file_name);
    // if ((tmp_ret = system(tmp_arg_buf)) < 0)
    // {
    //     perror("system");
    //     exit(EXIT_FAILURE);
    // }

    // 关闭文件
    close(read_zip_fd);
    close(write_zip_fd);
    return 0;
}
