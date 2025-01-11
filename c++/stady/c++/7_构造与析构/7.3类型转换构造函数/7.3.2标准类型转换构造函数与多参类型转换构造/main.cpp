#include <iostream>
using namespace std;
// 标准的类型转换构造函数 使用，及多参的类型转换构造函数的应用
class MyClass
{
private:
    int value;

public:
    // 类型转换构造函数：从 int 转换为 MyClass
    MyClass(int val) : value(val)
    {
        cout << "Type conversion constructor called" << endl;
    }

    void print()
    {
        cout << "Value: " << value << endl;
    }
};
class MyClass2
{
private:
    int x, y;

public:
    // 类型转换构造函数，带两个参数
    MyClass2(int a, int b = 0) : x(a), y(b)
    {
        cout << "Type conversion constructor called" << endl;
    }

    void print()
    {
        cout << "x: " << x << ", y: " << y << endl;
    }
};
int main()
{
    MyClass obj1 = 42; // 隐式调用类型转换构造函数
    obj1.print();

    MyClass obj2(99); // 显式调用类型转换构造函数
    obj2.print();
    /**********************************/
    MyClass2 obj3 = 42; // 使用默认值，将 42 转换为 MyClass
    obj1.print();

    MyClass2 obj4 = MyClass2(10, 20); // 显式调用
    obj2.print();
    return 0;
}
/*
./main
Type conversion constructor called
Value: 42
Type conversion constructor called
Value: 99
Type conversion constructor called
Value: 42
Type conversion constructor called
Value: 99
rm -r main.o main
*/