#include <iostream>
#include <cstring> // string 类型的头文件
using namespace std;
//***** 类模板*******
class Person
{
	private:
		string m_name;
		int m_age;
	public:
		Person(string n,int a):m_name(n),m_age(a) {}
		string get_name(void)const {return m_name;}
		int get_age(void)const  {return m_age;}
		void Person_printf(void){
			cout << "姓名：" << m_name << "年龄" << m_age << endl;
		}
};
void text0(){
//	括号内（参数）写道 类名后
	Person*  p1 = new Person("孙悟空",500) ;
	p1->Person_printf();

}
int main(void)
{
	text0();
	return 0;
}
