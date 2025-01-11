#include <iostream>
using namespace std;
/*
    当初始化列表的成员是常量时：必须要使用初始化列表
*/
// 全局变量
int data = 100;
class A
{
private:
    int a;
    const int b;

public:
    // 正确
    A(void) : a(::data), b(100)
    {
        cout << "A(int aa , int bb):a(aa),b(bb)" << "a = " << a << "; b = " << b << endl;
    }
    // 错误
    // A(void)
    // {
    //     a = data;
    //     b = 100;
    //     cout << "A(void) " << "a = " << a << "; b = " << b << endl;
    // }
    //      错误
    // A(int aa = ::data, const int bb)
    // {

    //     b = bb;
    //     cout << "A(int aa ,const int bb)" << "a = " << a << "; b = " << b << endl;
    // }
};

int main(void)
{
    A a1;
    return 0;
}
/*
./main2
A(int aa , int bb):a(aa),b(bb)a = 100; b = 100
*/