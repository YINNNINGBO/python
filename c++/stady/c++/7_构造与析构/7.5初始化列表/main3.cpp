#include <iostream>
using namespace std;
// C类中有多个成员类 A B 的情况：  初始化列表的顺序只与C 类中声明成员类的顺序有关
class A
{
public:
    // 没有基本数据类型  故构造函数没有使用初始化列表
    A(void)
    {
        cout << " A(void)" << endl;
    }
};
class B
{
public:
    // 没有基本数据类型  故构造函数没有使用初始化列表
    B(void)
    {
        cout << " B(void)" << endl;
    }
};
class C
{
    A a; // 先成名A  类子成员
    B b;

public:
    // 没有基本数据类型  故没有使用初始化列表
    C(A aa, B bb) : b(bb), a(aa)
    {
        cout << " C(A aa, B bb):b(bb),a(aa)" << endl;
    }
};

int main(void)
{
    A aa;
    B bb;
    C cc(aa, bb);
    /**
     * C中先声明的A 在声明的B 成员类，所以在初始化时页先调用A的构造函数
     */
    return 0;
}
/*
./main3
 A(void)
 B(void)
 C(A aa, B bb):b(bb),a(aa)
*/