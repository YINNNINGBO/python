#include <iostream>
using namespace std;
// 懒惰式单例进程实现
class A{
	private:
		int i;
		static int count; // 计数
		static A* getA;  // 数据
		A(int n= 100){  //构造
			i =  n;
			cout << i<<endl;
		}
		A(const A& that ){//拷贝
			this->i = that.i;
		}
	public:
		static A& GET(void){//调用private  static 构造
			if(getA  == NULL){
				getA = new A(123);// 这里 操作A中的构造函数
				count++;
			}
			return * getA;
		} 
		~A(){  //  析沟函数
			cout<< "~A"<< endl;
		}

};
A*  A::getA  = NULL; // 初始化 getA = NULL
int A::count = 0;    //出是化  count  是 0
int main(void)
{
	A& m1 = A::GET();
	A& m2 = A::GET();
	A& m3 = A::GET();
	cout<< &m1<<endl;
	cout<< &m2<<endl;
	cout<< &m3<< endl;
	//
	return 0;
}
