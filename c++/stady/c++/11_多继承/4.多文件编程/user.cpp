#include "hand.h"
void person::information(void) const // 常函数  声明定义  都要加const
{
    cout << "名字：" << name << " 年龄：" << age << endl;
}
person::person(int a, const string &n) : age(a)
{
    this->name = n;
    cout << " in class person" << endl;
}