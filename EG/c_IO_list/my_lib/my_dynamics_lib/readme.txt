生成动态连接库命令

动态库 不会从当前目录去查找连接库，只会从系统目录取查找
设置库加载路径
运行前需要让系统能找到动态库：

方法：（设置环境变量）临时设置 LD_LIBRARY_PATH

bash
	export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
<

解释 .: 的含义
单个点.：
	表示当前工作目录（current directory）
	这是Unix/Linux系统中对当前目录的标准表示法
冒号:：
	是Linux系统中路径分隔符（类似Windows中的分号;）
	用于分隔多个库搜索路径
组合.:：
	表示将"当前目录"添加到库搜索路径中
	相当于告诉系统："除了原来的库搜索路径外，还要在当前目录查找动态库"

>
/****************************************/

生成动态库命令：
gcc -c -fPIC math.c -o math.o
// -fPIC  ： 指生成与位置无关代码 动态库需要
gcc -shared -o libmath.so math.o

使用动态库编译生成可执行文件命令：
gcc main.c -L. -lmath -o main

/************************************* /
main.c :
#include <stdio.h>
#include "math.h"            //注意这里使用的是头文件调用动态库

int main() {
    printf("3 + 5 = %d\n", add(3, 5));
    printf("8 - 2 = %d\n", sub(8, 2));
    return 0;
}

math.c:
#include "math.h"

int add(int a, int b) {
    return a + b;
}

int sub(int a, int b) {
    return a - b;
}

math.h:

#ifndef MATH_H
#define MATH_H

int add(int a, int b);
int sub(int a, int b);

#endif

