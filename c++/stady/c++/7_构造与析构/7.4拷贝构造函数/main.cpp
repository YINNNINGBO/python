#include <iostream>
using namespace std;
/*
如果类中没有拷贝构造函数  编译器会送一个:缺省的拷贝构造函数
编译器提供的的 默认缺省的拷贝构造函数：对基本数据类型按字节复制
                                    对类型
*/
class A
{
public:
    int m;
    // 构造函数
    A(int data = 0)
    {
        m = data;
        cout << "A(int data = 0);m = " << m << endl;
    }
    // 拷贝构造函数
    A(const A &that)
    {
        cout << "拷贝构造函数: A(const A& that )" << endl;
        m = that.m;
    }
    void printf(void)
    {
        cout << "m =  " << m << endl;
    }
};

int main()
{
    A a1;
    A a2(a1); // 编译器会调用 ：拷贝构造函数
    A a3 = a1;
    a2.printf();
    return 0;
}
/*
./main
A(int data = 0);m = 0
拷贝构造函数: A(const A& that )
拷贝构造函数: A(const A& that )
m =  0
rm -r main.o main
*/