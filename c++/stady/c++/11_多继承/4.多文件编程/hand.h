#ifndef __HAND_H__
#define __HAND_H__

#include <iostream>
#include <string>
using namespace std;

class person
{
private:
    int age;     // 年龄
    string name; // 姓名
public:
    person(int a = 0, const string &n = "");
    void information(void) const;
};

#endif /* __HAND_H__ */