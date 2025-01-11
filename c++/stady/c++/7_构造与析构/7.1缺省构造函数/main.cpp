#include <iostream>
using namespace std;
/**构造函数在创建类的时候自动调用
 * 缺省构造函数
 *  类内没有定义构造函数时：  编译器会送一个没有参数的构造函数
 */
class Student
{
    // 默认私有成员
    string name;
    int age;

public:
    // 公有成员
    /**
     * 构造函数
     */
    Student(const string &n, int a)
    {
        name = n;
        age = a;
        cout << "student name = " << name << "; age =  " << age << endl;
    }
};
class Teacher
{
    // 默认私有成员
    string name;
    int age;

public:
    // 公有成员
    Teacher(const string &n, int a);
};
// 将构造函数定义在类的外卖呢
Teacher::Teacher(const string &n, int a)
{
    name = n;
    age = a;
    cout << "teacher name = " << name << "; age =  " << age << endl;
}
class A
{
private:
    int i;

public:
    A(void)
    {
        cout << "类A的无参构造函数" << endl;
        i = 0;
    }
};
class B
{
private:
    int i; // 基本类型成员变量
    A m_a; // 类 类型成员 变量
};

int main()
{
    Student s1("张飞", 21); // 创建s1时  ，类内的构造函数会自动执行
    Teacher t1("诸葛亮", 18);
    A a1; // 同样会调用无参构造函数A
    B b1; // 类B中的子类A同样会触发A的构造函数对  ，而B.i 没有被初始化
    return 0;
}