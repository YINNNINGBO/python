├── main  : main.c 
├── Makefile 
├── obj   : .o  目标文件 
├── README.txt  说明
└── user  : func.c  func.h  依赖文件


双向环形链表 通常是没有头节点（虚拟节点）
其实双向链表在查找的时候，不用刻意找前一个节点，因为即便遍历到当前节点，也可以通过->prev 的方式在拿到前一个节点