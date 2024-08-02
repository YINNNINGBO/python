#include <iostream>
#include <cstring>
using namespace std; 
// 类模板对象作函数参数
// 一般有三种传入方式：
// 1.指定传入类型 最常用
// 2.参数模板化
// 3.整个类模板化
template <class T1 ,class T2 =  int >
class Person{
	private:
	T1 m_name;
	T2 m_age;
	public:
	//  这里 必须 + const   
		Person(const T1& n,const T2& a):m_name(n),m_age(a) {}
		T1 get_n() const {return m_name;}
		T2 get_a() const {return m_age;}
		void p_Person(void)const ;

};
template <class T1 ,class T2  >
void  Person<T1, T2>::p_Person() const
{
	cout << "名字" << m_name << "  年龄：" << m_age << endl;  
}
// *******《 1 》********
void My_p_Per0(Person<string> * p)
{
	p->p_Person();
}
void text0(){
	// 在c++ 中  对const（参数类型） 很严格
	// 像是 ("章三",45 )  这样的就是两个长量
	// 在函数定义中  就必须 + ' const ' 修饰
	Person<string> *p1 = new Person<string>("章三",45);
	 My_p_Per0(p1);
	delete p1;
}
// *******《 2 》********
template <class T1,class T2>
void My_p_Per2(Person<T1 , T2> * p)
{
	p->p_Person();
	cout <<"T1的类型" << typeid(T1).name() << endl;
	cout <<"T2的类型" << typeid(T2).name() << endl;
}
void text1(){
	// 在c++ 中  对const（参数类型） 很严格
	// 像是 ("章三",45 )  这样的就是两个长量
	// 在函数定义中  就必须 + ' const ' 修饰
	Person<string> *p1 = new Person<string>("李四",35);
	 My_p_Per2(p1);
	delete p1;
}
// *******《 3 》********
template <class T> // 和2一样 相当于 函数模板结合类模板
				   // 这时的T 是  class Person
void My_p_Per3(T * p)
{
	p->p_Person();
	cout <<"T的类型" << typeid(T).name() << endl;
}
void text2(){
	Person<string> *p1 = new Person<string>("王五",28);
	My_p_Per3(p1);
	delete p1;
}
int main(void)
{
	text0();
	text1();
	text2();
	return 0;
}
