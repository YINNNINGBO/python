#include <iostream>
using namespace std;
/**
 * 构造函数的重载问题：
 *  explicit 的使用，增加可读性，代码更严谨
 */
class A
{
private:
    int a;

public:
    A(void)
    {
        cout << "A->无参构造函数" << endl;
        a = 0;
    }
};
class B
{
private:
    int a;

public:
    B(void)
    {
        cout << "B->无参构造函数" << endl;
        a = 0;
    }
    // 重载的构造函数使用explicit   关键字后：只能
    //  B b1 = 1;  就回报错
    //(不添加explicit ：B b1 = 1;这样不报错)
    explicit B(int aa)
    {
        cout << "B->含参构造函数" << endl;
        a = aa;
    }
    void printf(void)
    {
        cout << "B->参数 a = " << a << endl;
    }
};
class C
{
    int c1, c2;

public:
    explicit C(int cc1, int cc2)
    {
        cout << "C->含参构造函数" << endl;
        c1 = cc1;
        c2 = cc2;
    }
    C(void)
    {
        cout << "C->无参构造函数" << endl;
        c1 = 0;
        c2 = 0;
    }
    void cprintf(void)
    {
        cout << "c->参数 c1 = " << c1 << " c2 = " << c2 << endl;
    }
};
int main()
{
    /* error：conversion from ‘int’ to non-scalar type ‘A’ requested*/
    // A a1 = 1; // 编译器会找  参数只有一个且为int类型的构造函数，并没有 error

    // B b1 = 1; // 隐式转换： 调用  带参的构造函数（不使用explicit，可以这样定义）
    B b1 = B(1); // 显示转换：同：B b1(1) 使用explicit 后的构造函数  这样用，更严谨，可读性更强
    b1.printf();
    // C c1 = C(1, 2); 多个参数的 类型转换构造函数 可以直接这样使用
    C c1;
    c1.cprintf();
    return 0;
}
/*
./main
B->含参构造函数
B->参数 a = 1
C->无参构造函数
c->参数 c1 = 0 c2 = 0
rm -r main.o main
 */