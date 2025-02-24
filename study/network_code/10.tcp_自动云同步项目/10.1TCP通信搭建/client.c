#include "tcp.h"

int main(int argc, const char *argv[])
{
    ARGC_NUM(argc);                             // 参数个数判断
    p_tcp str_tcp = (p_tcp)malloc(sizeof(tcp)); // 分配内存
    bzero(str_tcp, sizeof(tcp));                // 清零
    while (!my_socket(str_tcp, CLIENT, argv))
        ; // 创建套接字   失败继续创建
    while (1)
    {
        char buf[1024] = {0};
        fgets(buf, sizeof(buf), stdin);
        my_send(str_tcp, buf, strlen(buf));
    }
    return 0;
}