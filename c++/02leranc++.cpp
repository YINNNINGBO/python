#include <iostream>
#include <cstring>
using namespace std;
class Spring{
	private:
		char* str;
	public:
		Spring(const char* str){
		this ->str = new char[strlen(str)+1];
		strcpy(this->str,str);
		}
		Spring(const Spring &that){  //拷贝构造  将传入的that——> this
			str = new char[strlen(that.str)+1];
			strcpy(str,that.str);
		}
		Spring &operator=(const Spring &that){  
			if(this != &that){              //  若 传入的 that != this
				delete [] str;              //清空this
				this->str = new char[strlen(that.str)+1];   //that -> this
				strcpy(this->str,that.str);
			}
		return *this;// 
		}
		~Spring(void){
			delete str;
		}
		void printf(void){
			cout<<str<<endl;
		}
		char* strfun(void){
			cout<<"int str fun"<<"\t"<< str<< endl;
			return  str;
		}
};
int main(void)
{
	Spring s1("Hello world"); //创建s1  并传值
							  //Spring  s1 = "Hello world " 与上式相同
	s1.printf();            
	cout<<"s1.printf"<<endl;  
	Spring s2 = s1;          // 拷贝构造函数
	s2.printf();
	cout<<"s2.printf"<<endl;
	Spring s3("fuck haha");  //
	s1 = s3;                // 拷贝赋值  //
	s1.printf();            // Hello world 
	cout<<s3.strfun()<<endl;
	return 0;
}
