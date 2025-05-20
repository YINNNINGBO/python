生成自定义静态库


hello.c   ： 自定义链接库的原文件
libmyhello.a  :    生成的自定义静态连接库
my.c     ： 调用自定义静态连接库的测试文件

/*******************************************************/
linux@linux-vir--mac:~/Desktop/gitee_linux_c/EG/c_IO_list/my_lib$ gcc hello.c -c 
linux@linux-vir--mac:~/Desktop/gitee_linux_c/EG/c_IO_list/my_lib$ ls
hello.c  hello.o
linux@linux-vir--mac:~/Desktop/gitee_linux_c/EG/c_IO_list/my_lib$ ar rcs libmyhello.a hello.o
linux@linux-vir--mac:~/Desktop/gitee_linux_c/EG/c_IO_list/my_lib$ vim my.c
linux@linux-vir--mac:~/Desktop/gitee_linux_c/EG/c_IO_list/my_lib$ ls
hello.c  hello.o  libmyhello.a  my.c

/***************************************************/
hello.c：
#include <stdio.h>

void hello(void){
	printf("hello world!");
	return ;
}


my.c:
#include <stdio.h>
extern  void hello(); 
int main(){
	hello();
	return 0;
}


/**************************************************/
调用自定义静态连接库 生成可执行文件（ libmyhello.a ）
方法1：linux@linux-vir--mac:~/Desktop/gitee_linux_c/EG/c_IO_list/my_lib$ gcc my.c -o text -L. -lmyhello
//   -L.  指的是当前路径下连接库文件
方法2：linux@linux-vir--mac:~/Desktop/gitee_linux_c/EG/c_IO_list/my_lib$ gcc my.c -o text -libmyhello.a


