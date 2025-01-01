#include <iostream>
/*     有问题文件       */
using namespace std;

int &add(const int &a, const int &b)
{
    int tmp = 0; // 局部变量 函数退出后被释放，回收
    tmp = a + b;
    return tmp; // 有风险
}
int main()
{
    int a = 10, b = 20;
    int &tmp = add(a, b); // 引用被回收的变量  危险  野指针
    cout << " 返回引用 add() = :" << tmp << endl;
    return 0;
}
