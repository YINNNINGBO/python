#include <iostream>
#include <cstring> // string 类型的头文件
using namespace std;
//***** 类模板*******
template <class NameType ,class AgeType>// 表明类模板中有两种类型的  参数
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
void text0(){
	Person<string,int>*  p1 = new Person<string ,int>("孙悟空",500) ;
	p1->Person_printf();

}
int main(void)
{
	text0();
	return 0;
}
