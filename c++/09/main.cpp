#include "09.h"
int main(void)
{
	cout<<"覆盖是使用 virtual"
		<<" 隐藏是不使用virtual"
		<<endl;
	cout<<"创建4个类"<<endl;
	A* a1 = new A;
	B* b1 = new B;
	C* c1 = new C;
	D* d1 = new D; 
	cout<<"创建类的指针数组"
		<<"将4个类放入数组"<<endl;
	A* cur[128] = {0};
	cur[0] = a1;
	cur[1] =static_cast<B*>(b1);
	cur[2] =static_cast<C*>(c1);
	cur[3] =static_cast<B*>(d1);
	cout<<"___对a1赋值geta(int a) 并打印"<<endl;
	a1->geta(2);
	a1->printf();
	cout<<"调用geta重载,再打印"<<endl;
	a1->geta(3,1);
	a1->printf();
	cout<<"___对b1赋值,在打印"<<endl;
	b1->getb(4);
	// B::printf() 有两次 答应   本身的 + A的            
	b1->B::printf();
	cout<<"___对c1赋值,在打印"<<endl;
	c1->geta(8);
	cur[2]->printf();
	cout<<"___对d1赋值,在打印"<<endl;
	d1->getb(12);
	cur[3]->A::printf();
	return 0;
}
