#include <iostream>
// 如果没有定义拷贝赋值构造函数，编译器也有一个默认的，默认的也会出现free  double 的现象
using namespace std;
class A
{
private:
    int *pi;

public:
    // 使用编译器默认拷贝构造函数
    A(int i = 0)
    {
        cout << "A(int i = 0)" << endl;
        pi = new int(i);
    }
    A(const A &that)
    { // 使用 深拷贝  完成指针成员变量的拷贝
        pi = new int(*that.pi);
    }
    // 自定义拷贝赋值构造
    A &operator=(const A &that)
    {
        cout << "A &operator=(const A & that) " << endl;
        if (this != &that)
        {
            delete pi; // 先把源有的释放
            pi = new int(*that.pi);
        }
        return *this; // 为了支持 链式操作：a1= a2 =a3
    }
    ~A()
    {
        delete pi;
    }
};
int main()
{
    A a1(3);
    A a2 = a1; //
    A a3(a1);
    a2 = a1; // 这种情况：a2已经存在  再赋值  就是 拷贝赋值，
    return 0;
}