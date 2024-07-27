#include <iostream>
using namespace std;
class stu{
	private:
		string name;
		int age;
	public:
		stu(){
			cout<<"默认构造"<<endl;
		}
		stu(string n,int a):name(n),age(a){
			// 上方是含有参数的构造函数的  参数列表初始化使用
			 
			cout<<"汉参数构造"<<endl;
		}
		~stu(void){
			cout<<"析构"<<endl;
		}
		void showper() const {
			cout<<name<<":"<<age<<endl;
		}
};
int main(void)
{
	stu* as = new stu("校长",68);
	as->showper( );
	return 0;
}
