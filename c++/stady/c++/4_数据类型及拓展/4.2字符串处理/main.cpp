#include <iostream>
using namespace std;
int main()
{
    /*定义*/
    string s1;
    string s2("aaa");
    string s3 = string("bbb");
    string s4 = "ccc";
    /*字符串的拷贝*/
    string s5 = s2; // 直接使用 '= '拷贝
    /**
     * 不同于  c语言的
     * char *p5 = "aaa";
     * char *p2  =  p5 是将两个指针指向同一个地址
     * 而c++  = 是
     * s5 ,与s2  指向不同地址  但是不同地址存储的数据相同
     */
    /*字符串的拼接*/
    s5 += s3;
    /*字符串的比较*/
    if (s3 == "bbb")
    { // 相当于c原因呢 strcmp
        cout << "true: s3 =" << s3 << endl;
    }
    /*字符串长度*/
    cout << "s5.length() =" << s5.length() << "; s5.size() =" << s5.size() << endl; // 没有算‘\n’
    cout << "s5 =" << s5 << endl;
    /*交换*/
    cout << "s2 = " << s2 << "; s3 = " << s3 << endl;
    swap(s2, s3);
    cout << "after swap(s2,s3)" << endl
         << "s2 = " << s2 << "; s3 = " << s3 << endl;
    return 0;
}