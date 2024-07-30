#include <iostream>
using namespace std;
class A{
	private:
		int num;
	public:
		 A(void);
		~A(void){
			cout<<"~A"<<endl;
		}
		void geta(int a);
		void geta(int a,int b){
			(b >= a)?num = b:num= a;
		}
		void A_only_fun(void) const ;
		int re_num(void)const;
		virtual void printf(void) const;
};
class B: public A{
	public:
		B(void);
		~B(void){
			cout<<"~B"<<endl;
		}
		void getb(int num);
		int re_num(void)const;
		virtual void printf(void) const;
};
class C: public A{
	public:
		C(void){
			cout<<"C creamte"<<endl;
		}
		~C(void){
			cout<<"~c      "<<endl;
		}
};
class D : public B,public C {
	public:
		D(void){
			cout<<"D creamte"<<endl;
		}
		~D(void){
			cout<<"~D      "<<endl;
		}

};




