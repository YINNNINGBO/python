#include <iostream>
#include <cstring>
using namespace std;

class String
{
private:
    char *str;

public:
    String(const char *str = "null")
    {
        this->str = new char[strlen(str) + 1];
        strcpy(this->str, str);
    }
    // 拷贝构造
    String(const String &that)
    {
        cout << "拷贝构造" << endl;
        this->str = new char[strlen(that.str) + 1];
    }
    // 拷贝赋值构造 (可能会有 s1 =  s1)
    String &operator=(const String &that)
    {
        cout << "拷贝赋值构造" << endl;
        if (this != &that)
        {
            // 释放原空间
            delete[] str; // 多个字节
            this->str = new char[strlen(that.str) + 1];
            strcpy(this->str, that.str);
        }
        return *this;
    }
    void printf(void)
    {
        cout << "str = " << str << endl;
    }
    // 析构函数
    ~String(void)
    {
        cout << "析构函数" << endl;
        delete str;
    }
    const char *c_str(void) const
    {
        return this->str;
    }
};
int main()
{
    if (1)
    {
        String s1 = "Hello"; // 类型转化构造函数

        String s2 = s1; // 拷贝构造函数
        s2.printf();

        String s3 = String("world");
        s2 = s3; // 拷贝赋值构造
        s3.printf();
        cout << s2.c_str() << endl; // string::c_str  c++字符串转c字符串
    }

    return 0;
}
/**
 *
    ./main1

    拷贝构造
    str =
    拷贝赋值构造
    str = world
    world
    析构函数
    析构函数
    析构函数
 *
 */