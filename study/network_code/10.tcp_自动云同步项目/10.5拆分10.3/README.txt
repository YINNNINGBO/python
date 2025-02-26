目录属性：
.
├── client                               //客户端代码
│   ├── client
│   ├── client.c
│   ├── client_use.c
│   ├── client_use.h
│   └── zhaolusi.jpg
├── find_whether_have_file              //查找文件是否存在测试程序
│   ├── main
│   └── opendir.c
├── Makefile
├── README.txt
└── server                              //服务端代码
    ├── server
    ├── server.c
    ├── server_use.c
    ├── server_use.h
    └── tmp.jpg

客户端：./client/client    <ip>       eg:  ./client/client  0          //（本机测试）
服务端：./server/server    <ip>       eg:  ./server/server  127.0.0.1  //（本机测试）

特点：
    连接通信后，执行一项功能不会直接关闭连接，而是等待用户输入指令(循环)，再执行对应的功能

优化方向：
    1.两端的自定义函数中功能重复度过高，可以优化（客户端和服务端代码重复度太高，显得代码有些臃肿，可以优化）
    2.数据的发送和传输 （没有提前发送具体的数据长度）
        导致接收端接收数据时，不知道具体要接收多少数据，只能循环接收，直到接收完毕，浪费资源
    3.没有使用并发，可以优化

缺陷：没有使用多主机测试：   使用linux内的函数和系统调用实现，可能不具有跨平台性