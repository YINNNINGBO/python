#include <iostream>
using namespace std;
/**
 *  什么时函数重载？  ：
 *  同一作用域 ，函数名相同；型参个数，类型,参数循序不同
 * c++编译器将 型参和函数名  合成一个新的函数名 ，依次来区分同名不同参的函数 (与返回值无关)
 *
 * 可使用命令 nm 可执行文件名  来查看  <符号表>： 列出文件中的函数和变量名称、地址以及它们的类型。
 *  0000000000001209 T _Z4swapPiS_     //  int *  ,int*           swap(int *a, int *b)          地址大小 1
    000000000000127e T _Z4swapRfRi     // float & ,int &          swap(float &a, int &b)                3
    00000000000012c7 T _Z4swapRiRf     // int &   , float &       swap(int &a, float &b)                4
    000000000000123a T _Z4swapRiS_S_   // int &, int & ,int &     swap(int &a, int &b, int &c)          2
 */

/**
 *交换  int  类型
 */
void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
void swap(int &a, int &b, int &c)
{
    int tmp = a;
    a = b;
    b = c;
    c = a;
}
// 不同长度类型可以强转 静态转换 ，但是较大的数据转到较小的字节 ，会发生精度丢失
void swap(float &a, int &b)
{
    float f_a = a;
    int i_b = b;
    static_cast<int>(a);
    static_cast<float>(b);
    a = i_b;
    b = f_a;
}
void swap(int &a, float &b)
{
    int f_a = a;
    float i_b = b;
    static_cast<float>(a);
    static_cast<int>(b);
    a = i_b;
    b = f_a;
}
/********************************重载函数 的 优先级**************************************/
// 优先调用  型参类型更匹配的
// 完全匹配 > 常量转换 > 升级转换 > 降级匹配 > 省略号匹配
void bar(int i)
{
    cout << "bar(int i)" << endl;
}
void bar(const char c)
{
    cout << "bar(const char c)" << endl;
}

void far(int c)
{
    cout << "far(int c)" << endl;
}
void far(char c)
{
    cout << "far(char c)" << endl;
}

void hum(int c, ...)
{
    cout << "hum(int c, ...)" << endl;
}
void hum(int c, int j)
{
    cout << "hum(int c,int j)" << endl;
}
/******************************二义性*****************************/
void func(unsigned int c)
{
    cout << "func(int c)" << endl;
}
void func(double c)
{
    cout << "func(double c)" << endl;
}
void f(int a, int b, int c = 100)
{
    cout << "f(int a ,int b , int c =100)" << endl;
}
void f(int a, int b)
{
    cout << "f(int a, int b)" << endl;
}
int main()
{
    int a = 10, b = 20;
    float c = 1.1, d = 2.2;
    char ch = '1';
    short s = 10;
    // int int
    cout << "a = " << a << "; b = " << b << endl;
    swap(a, b);
    cout << "swap(int a,int b )" << "a = " << a << "; b = " << b << endl;
    // float int
    cout << "a = " << a << "; c = " << c << endl;
    swap(c, a);
    cout << "swap(float c,int a )" << "c = " << c << "; a = " << a << endl; // 精度会丢失
    // int float
    cout << "b = " << b << "; d = " << d << endl;
    swap(b, d);
    cout << "swap(int b,float d )" << "b = " << b << "; d = " << d << endl; // 精度会丢失

    bar(a);       // bar(int i)         完全匹配
    bar(ch);      // bar(const char c)  常量转换
    far(s);       // far(int c)         升级转换
    hum(10, 2.3); // hum(int c, int j)  降级转换  float -> int : 降级

    // 二义性
    // func(a);   报错   都是升级转换   编译器无法区分
    // f(a,b);    报错   默认参数也会带来
    return 0;
}