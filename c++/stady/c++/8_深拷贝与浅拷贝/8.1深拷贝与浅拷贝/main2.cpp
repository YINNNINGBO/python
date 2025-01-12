#include <iostream>
using namespace std;
/**
 * 一般情况使用编译器送的：拷贝构造函数就够用了，但是个别特殊情况不行
 * 下列是修改方案  避免使用浅拷贝，使用深拷贝（自定义拷贝构造函数）
 */
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
    return 0;
}

/**
 * ./main2
    A(int i = 0)
*/