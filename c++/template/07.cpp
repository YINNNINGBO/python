#include <iostream>
#include <cstring>
using namespace std;
//类模板中成员函数的创建时间
//被调用 才真正创建成员函数最主要的原因就是：
//只有被调用  编译器才能确定 模板的参数类型，才能做到创建成员函数，
//否则 无法创建
template <class NameType ,class AgeType = int>// 表明类模板中有两种类型的  参数
class Person
{
	private:
		NameType m_name;
		AgeType m_age;
	public:
		Person(NameType n,AgeType a):m_name(n),m_age(a) {}
		NameType get_name(void)const {return m_name;}
		// get_name、get_age 两个函数 在下放没有调用
		// 所以没有真正生成该成元函数的代码（二进制吗）
		AgeType get_age(void)const  {return m_age;}
		//Person_printf  函数在和后续程序中被调用 所以生成了该成员函数的二进制码
		//更节省空间！！！！！
		void Person_printf(void){
			//这里  在同一类定义过程中 对private  直接调用即可
			cout << "姓名：" << m_name << "年龄" << m_age << endl;
		}
};
void text0()
{
	Person<string,int>* p1  =  new Person<string,int>("沙和尚",400);
	Person<string>* p2  =  new Person<string>("猪八戒",300);
	Person  p3("白龙马",432);
	p1->Person_printf();
	p2->Person_printf();
	p3.Person_printf();
}
int main(void)
{
	text0();
	return 0;
}
