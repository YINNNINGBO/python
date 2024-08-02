#include <iostream>
#include <cstring>
using namespace std;
//模板的局限性
//有些特定数据类型，需要用具体化方式做特殊实现
//对比两数据是否相等
class Person{

	string m_name;
	int m_age;
	public:
		Person(const string& name, int age):m_name(name),m_age(age){}
		string get_name(void)const{
			return m_name;
		}
		int get_age(void)const{
			return m_age;
		}

};

template <class T>
//  这里的参数 也用  const 修饰了   否则 会报错
bool myCompare(const T &a,const T &b ){
	if( a ==  b){
		return true;
	}else {
		return false;
	}
}

//利用 具体化Person的版本实现代码，具体化有先调用
template <>
// 该模板  是基于 template <class T>   所以 上面的不能珊
// 且这个定义在 template <class T>  下面
// 其中的参数   是否用    'const '  修饰 必须相同
bool myCompare(const Person &p1,const Person &p2 ){
	if(  p1.get_name() ==  p2.get_name() &&  p1.get_age() == p2.get_age()){
		return true;
	}else {
		return false;
	}
}

void text1(void )
{
	Person p1("Tom",18);
	Person p2("jake",16);//
	// 注意这里时比较class 中的string&  使用函数模板的显示类型<const string&> 
	bool ret = myCompare<const string>(p1.get_name(),p2.get_name());
	if(ret){
		cout << "p1 == p2" << endl;
	}else{
		cout << "p1 != p2" << endl;
	}
}

void text2(void )
{// 与上不同  直接比较class  函数模板无法识别  自定义的 class 类型  所以 error
// ***********提示：： (1)  可用运算符重载 解决  
//                     (2)  具体化 Person 的版本解决  
	Person p1("Tom",18);
	Person p2("jake",16);//
	bool ret = myCompare(p1,p2);
	if(ret){
		cout << "p1 == p2" << endl;
	}else{
		cout << "p1 != p2" << endl;
	}
}


void text0(void)
{
	int a = 10;
	int b = 20;
	double c = 19.88;
	// cout << myCompare<int ,double >(a, c) << endl;   error 
	bool ret = myCompare( a, b);
	if(ret){
		cout << "a == b" << endl;
	}else{
		cout << "a != b" << endl;
	}
}
int main(void )
{
	text0();
	text1();
	text2(); //  text2() 中函数模板的 参数有问题  编译器无法识别
//	函数模板的参数类型
	return 0;
}
