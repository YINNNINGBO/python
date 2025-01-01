#include <iostream>
#include <cstdio>
using namespace std;
//  c++ 自己的申请内存  new:申请   delete：释放

int main()
{
    int *p1, *p2, *p3;
    // p1 = (int *)malloc(siezof(int));   free(p1); // c语言风格
    p1 = new int;      // c++ 风格
    p2 = new int(123); // 在堆中分配一个int类型内存空间，初始化 123
    p3 = new int[123]; // 在堆中分配123个int类型内存空间.
    // 使用于 c 相同

    // 释放
    delete p1;
    delete p2;
    /*数组内 释放全部数组的内存*/
    delete[] p3;

    /* 只释放数组中的一个内存 ，会造成 内存泄漏 */
    // delete p3;       报错
    return 0;
}