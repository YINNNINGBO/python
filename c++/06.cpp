#include <iostream>
using namespace std;
class homan {
	private:
	protected:
		int m_pri;
		string name;
		int age;
	public:
		homan(const string& n,int a):name(n),age(a){
			m_pri = 1234;
		}
		~homan(){
		//	delete this;  不可以这样使用

			cout<<"~homan over"<<endl;
		}
	void who(){
		cout<<"姓名"<<name<<"年龄："<<age<<"身份号"<<m_pri<<endl;
	}
};
class student :public homan{
	private:
		int stu_num;
	public:
		student(const string& n,int a,int num):homan(n,a){
			stu_num  = num;
		}
		~student(){
		//	delete this;
			cout<<"~student over"<<endl;
		}
		void who(){
			cout<<"学生"<<name<<"年龄"<<age<<"学号"<<stu_num<<endl;
		
		}
		void sleep(int time = 0)const{
			if(time == 0){
			}else{
				cout<<"睡觉已有："<<time<<"小时"<<endl;
			}
		}
		void leran(int time = 0)const;
		
};//
  //使用在类外定义的方式
void student::leran(int time )const
{
	if(time == 0){
	}else{
		cout<<"学习已有："<<time<<"小时"<<endl;
	}
}
int main(void )	
{//使用new  申请内存的方式创建 
	homan * m1 = new homan("章三",18);
	m1->who();
	student * s1 = new student("小明",15,100013);
	s1->who();
	s1->sleep(2);
	s1->leran();
	cout<<'\n'<<"测试向下 向上造型"<<endl;
	//向下造型   子 = 基类
	//不建议使用
	student *s2  =static_cast<student*> (m1);
	s2->who();
	//向上造型 基类 = 子
	homan *m2  =static_cast<homan*> (s1);
	m2->who();
//这个homan   指挥调用~homan
	delete m1;
//这个student是homan 的继承 
//调用~sdudent 和 homan
	delete s1;

	return 0;
}

