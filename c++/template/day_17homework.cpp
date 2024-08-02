#include <iostream>
#include <cstring>
using namespace std;
//用运算符重载和 类模板实现 类的大小比较（类成员）
//****** 类模板*********
template <class T>
class Num_str{
	private:
		T str_num;
	public:
		Num_str(const T& c):str_num(c) {}
		T gets(void) const;
		void p_s(void) const;
};
template <class T>
T Num_str<T>::gets() const{
	return str_num;
}
template <class T>
void Num_str<T>::p_s(void) const{
	cout << "T type is  " << typeid(T).name() <<" str_num is :" << str_num << endl;
}
template <class T1, class T2>
int  Compare(T1 &a, T2 &b){
	if(a.gets() > b.gets()){
		cout << a.gets() << ">" << b.gets() << endl;
		return 1;
	}else if(a.gets() == b.gets()){
		cout << a.gets() << "=" << b.gets() << endl;
		return 0;
	}else{
		cout << a.gets() << "<" << b.gets() << endl;
		return -1;
	}
}
void text0(){
	Num_str m1(31);
	Num_str m2(25);
	Compare(m1,m2);
}
void text1(){
	Num_str m1('a');
	Num_str m2(66);
	Compare(m1,m2);
}
// ********算术俯重载
class  stock{
	private:
		char str;
	public:
		stock(char  a):str(a) {}
		char Mygetchar(void) const;
		friend void operator- ( const stock a,const stock b) 
		// 友元函数重载-操作符 !
		 { 
			 if(a.Mygetchar() > b.Mygetchar()){
			 cout << a.Mygetchar() << ">" << b.Mygetchar() << endl;
			 }else if(a.Mygetchar() == b.Mygetchar() ){
			 cout << a.Mygetchar() << " == " << b.Mygetchar() << endl;
			 }else{
			 cout << a.Mygetchar() << "<" << b.Mygetchar() << endl;
			 }
		}
};
char stock::Mygetchar() const{
	return str;
}
void text2(void){
	stock m1('a');
	stock m2('b');
	stock m3(110);
	stock m4(88);
	m1-m2;
	m3-m4;
}
int main()
{
	text0();
	text1();
	text2();
	return 0;
}
