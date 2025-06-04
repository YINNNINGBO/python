.
├── client   
│   ├── client.c
│   └── Makefile
├── Makefile
├── readme.txt
├── socket
│   ├── Makefile
│   └── server.c
└── USER
    ├── user.c
    └── user.h
Makefile 嵌套调用子文件夹中的Makefile  生成可执行文件
USER:存放封装的API
在当前目录使用 make后 会生成MIN文件 ，存放.o
