#include <iostream>
using namespace std;
//
class A
{
private:
    string name;
    const int age;
    int *pi;

public:
    // 两个参数的构造函数
    A(string nn = "null", const int aa = 0) : name(nn), age(aa)
    {
        cout << "A(string nn = null,const int aa = 0)" << endl;
    }
    // 三个参数的构造函数
    // 初始化列表不能使用 this指针 error: A(string nn , const int aa ,int * p) : name(nn), age(aa),this->pi(p)
    A(string nn, const int aa, int *p) : name(nn), age(aa), pi(new int(*p))
    {
        cout << "A(string nn, const int aa, int *p)" << endl;
    }
    // 析构函数
    ~A(void)
    {
        cout << "析构函数被调用" << endl;
        delete pi;
    }

    // 验证 常成员变量 的初始化
    void printf(void) const
    {
        cout << "name = " << name << "; age = " << age << endl;
    }
};
int main(void)
{
    // if (1)
    // {
    //     A a1 = A("张飞", 21);
    //     a1.printf(); // 普通类可以调用常函数
    //     // 因为调用的构造函数  没有指针，而析构函数又释放指针 在调用析构函数时会发送段错误
    // }
    // a1生命周期结束对应的析构函数被调用

    /*内有堆内存对象 声明周期结束  不会调用析构*/
    // if (1)
    // {

    //     int num = 99;
    //     A *a2 = new A("诸葛亮", 18, &num);
    //     // delete a2;
    // }

    // 内有堆内存对象  只能使用 delete 时，调用析构函数
    int num = 99;
    A *a2 = new A("诸葛亮", 18, &num);
    delete a2;

    return 0;
}