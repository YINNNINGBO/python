#include <iostream>
using namespace std;
/*
应用场景：构造函数对数据成员初始化时,可以完成数据成员的初始化

*/
class A
{
    int m;
    string str1;

public:
    // 构造函数
    A(int data = 0, string str = "NULL") : m(data), str1(str)
    {

        cout << "A(int data = 0, string str =  NULL ) : m(data), str1(str);m = " << m << "; str1 = " << str1 << endl;
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
    A a1 = A(2, "hehe");

    return 0;
}
/*
./main
A(int data = 0, string str =  NULL ) : m(data), str1(str);m = 2; str1 = hehe
*/