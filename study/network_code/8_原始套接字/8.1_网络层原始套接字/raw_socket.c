#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip.h>

#define DEST_IP "127.0.0.1" // Change to target IP
#define SRC_IP "127.0.0.1"  // Change to source IP
#define DATA "Hello from raw socket!"

// Calculate IP header checksum
unsigned short checksum(void *b, int len)
{
    // 将输入的void指针转换为unsigned short指针，方便后续按16位处理
    unsigned short *buf = b;
    // 初始化sum为0，用于累加16位数据
    unsigned int sum = 0;
    // 用于存储最终的校验和结果
    unsigned short result;

    // 遍历输入数据，每次处理两个字节（16位）
    for (sum = 0; len > 1; len -= 2)
        // 将当前16位数据累加到sum中，并移动指针到下一个16位数据
        sum += *buf++;
    // 如果剩余长度为1，表示还有最后一个字节未处理
    if (len == 1)
        // 将最后一个字节转换为16位数据并累加到sum中
        sum += *(unsigned char *)buf;
    // 将sum的高16位和低16位相加
    sum = (sum >> 16) + (sum & 0xFFFF);
    // 如果相加结果超过16位，再次将高16位和低16位相加
    sum += (sum >> 16);
    // 取sum的补码，即对sum取反
    result = ~sum;
    // 返回最终的校验和结果
    return result;
}

int main()
{
    int sockfd;
    struct sockaddr_in dest_addr;
    char packet[4096];

    // Create raw socket
    if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0)
    {
        perror("socket() error");
        exit(EXIT_FAILURE);
    }

    // Set IP_HDRINCL to include our own IP header
    int one = 1;
    const int *val = &one;
    if (setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, val, sizeof(one)) < 0)
    {
        perror("setsockopt() error");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Destination address
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_addr.s_addr = inet_addr(DEST_IP);

    // Construct IP header
    struct iphdr *iph = (struct iphdr *)packet;
    iph->ihl = 5;
    iph->version = 4;
    iph->tos = 0;
    iph->tot_len = sizeof(struct iphdr) + strlen(DATA);
    iph->id = htons(54321);
    iph->frag_off = 0;
    iph->ttl = 255;
    iph->protocol = IPPROTO_RAW;
    iph->check = 0;
    iph->saddr = inet_addr(SRC_IP);
    iph->daddr = dest_addr.sin_addr.s_addr;

    // Calculate checksum
    iph->check = checksum((unsigned short *)packet, iph->tot_len);

    // Add data after IP header
    char *data = packet + sizeof(struct iphdr);
    memcpy(data, DATA, strlen(DATA));

    // Send packet
    if (sendto(sockfd, packet, iph->tot_len, 0,
               (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0)
    {
        perror("sendto() error");
    }
    else
    {
        printf("Packet sent. Length: %d\n", iph->tot_len);
    }

    close(sockfd);
    return 0;
}
