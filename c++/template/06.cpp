#include <iostream>
#include <cstring>
using namespace std;
//类模板没有自动类型推导   text0() 测试  是可以的
//类模板可以使用默认参数
//eg :  template <class NameType ,class AgeType = int>// 表明类模板中有两种类型的  参数
//    在定义时可以：
//					Person<string>  p1("猪八戒",300);
//
template <class NameType ,class AgeType = int>// 表明类模板中有两种类型的  参数
class Person
{
	private:
		NameType m_name;
		AgeType m_age;
	public:
		Person(NameType n,AgeType a):m_name(n),m_age(a) {}
		NameType get_name(void)const {return m_name;}
		AgeType get_age(void)const  {return m_age;}
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
