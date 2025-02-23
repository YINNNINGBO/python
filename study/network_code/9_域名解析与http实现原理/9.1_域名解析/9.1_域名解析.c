#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
/**域名解析并打印*/
/*
struct hostent {
    char  *h_name;      // 主机的规范名称
    char **h_aliases;   // 主机的别名列表（字符串数组，以 NULL 结尾）
    int    h_addrtype;  // 地址类型（如 `AF_INET` 或 `AF_INET6`，但仅支持 IPv4）
    int    h_length;    // 地址长度（IPv4 为 4 字节，IPv6 为 16 字节）
    char **h_addr_list; // 主机的 IP 地址列表（网络字节序，以 NULL 结尾）
};
*/
int main(int argc, const char *argv[])
{
    if (argc != 2)
    {
        printf("%s <host name>\n", argv[0]);
        exit(1);
    }
    // 打印主机别名
    struct hostent *host = gethostbyname(argv[1]);
    if (host == NULL)
    {
        herror("gethostbyname");
        exit(1);
    }

    if (host->h_aliases[0] == NULL)
    {
        printf("No aliases found for %s\n", argv[1]);
    }
    else
    {
        printf("Aliases for %s:\n", argv[1]);
        for (int i = 0; host->h_aliases[i] != NULL; i++)
        {
            printf("  %s\n", host->h_aliases[i]);
        }
    }
    // 打印协议类型
    printf("Protocol type: %s\n", host->h_addrtype == AF_INET ? "IPv4" : "IPv6");
    // 打印IP地址
    for (int i = 0; host->h_addr_list[i] != NULL; i++)
    {
        printf("NO[%d],ip address : %s\n", i, inet_ntoa(*(struct in_addr *)host->h_addr_list[i]));
    }
    // 销毁hostent结构体
    endhostent();
    return 0;
}
