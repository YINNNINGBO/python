#include <iostream>
using namespace std;
/*******************************内联函数********************/
// 增加执行效率    本质上没有函数的跳转（函数跳转需要在 栈区申请空间） 不需要参数传递
//  适合简单的函数  ，不是一定会被内敛  ，只是建议编译器声明为内敛，具体取决于编译器自身选择

inline int add(const int a, const int b)
{
    return (a + b);
}
int main()
{
    int a = add(1, 2); // 在本地翻译为 ： int a = 1+2;
    cout << "内敛函数 = " << a << endl;
    return 0;
}