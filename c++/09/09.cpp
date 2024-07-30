#include "09.h"
//......B......
B::B(void){
	cout<<"B creamte"<<endl;
}
void B::getb(int num){
	int x = num; 
	A::geta(x);
}
int B::re_num(void)const{
	cout<<"B::re_num与A::re_num形成覆盖";
	return A::re_num();
}
void B::printf(void)const{
	cout<< "B.."<<re_num()<<".."<<endl;
}
//.....A.......
int A::re_num(void)const{
	cout<<"A::re_num与B::re_num形成覆盖";
	return num;
}
//构造函数  没有返回值 没有void
 A::A(void){
	cout<<"A creamte"<<endl;
}
void A::geta(int a){
	num = a;
}
void A::printf(void)const{
	cout<< "A.."<<re_num()<<".."<<endl;
}
//关于函数声明与定义的结尾 const  只写一个即可
void A::A_only_fun() const{
	cout<<"A_only_fun  A 的 public fun"<<endl;
}

