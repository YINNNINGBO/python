#include <iostream>
#include <cstring>
using namespace std;
class People {
	private:
		string m_name;
		int m_age;
	public:
		People(const string& a,const int& b):m_name(a),m_age(b){
			cout << "people(..)" << endl;
		}
		virtual ~People(void){
			cout << "~People()" << endl;
		}
		const string getn(void) const 
		{
			return m_name;
		}
		const int geta(void) const
		{
			return m_age;
		}
		virtual void show(void) const 
		{
			cout << "名子:" << m_name
				<< " 年龄:" << m_age << endl;
		}
};
class Teacher: public People
{
	private:
		string doing;
		string discipline;
	public:
		Teacher(const string& a,const int& b,const string& c,const string& d):People(a,b),doing(c),discipline(d)
	{
		cout << "Teacher(....)" << endl;
	}
		virtual ~Teacher(void)
		{
			cout << "~Teacher()" << endl;
		}
		string getdo(void) const {return doing;}
		string getdi(void) const {return discipline;}
		void show(void) const 
		{
			cout << "教师名字:" << getn()
				<< " 年龄:"  << geta()
				<< " 正在:" << doing
				<< " 所教科目为:" << discipline << endl;
		}

};
class Student: public People
{
	private:
		string doing;// 玩 or 学习
		string discipline; // 学科
		string whattime;   // 上课时间 还是休息时间 
	public:
		Student(const string& a,const int& b,const string& c,const string& d,const string& e):People(a,b),doing(c),discipline(d),whattime(e)
	{
		cout << "Student(.....)" << endl; 
	}
		virtual ~Student()
		{
			cout << "~Student()" << endl;
		}
		string getw(void) const {return whattime; }
		void show(void) const 
		{// c++ 中  可以用 ==  比较字符串
			if(whattime == "上课时间"){
				cout << "学生姓名:" << getn() << " 年龄:" << geta() << "在" << discipline
					<< whattime << doing << endl;
			}else{//下课时间 玩 不输出  课
				cout << "学生:" << getn() << " 年龄:" << geta() << "在" 
					<< whattime << doing << endl;

			}

		}
};
class Doctor:public Teacher,public Student{
    public:
        Doctor(const string& a,const int& b,const string& c ,const string& d,const string& e):Teacher(a,b,c,d),Student(a,b,c,d,e) {
            cout << "Doctor(.....)" << endl;
        }
        ~Doctor(void){
            cout << "~Doctor()" << endl;
        }
        void show(void) const {
            cout << "Doctor: " << Teacher:: getn()
                 << "年龄 " << Teacher::geta()
                 <<"学习的同时也在教学" << endl;
        }

};

int main(void)
{
	People* p1 = new People("张三",18);
	p1->show();
	Teacher* t1 = new Teacher("李春霞",27,"上课","英语");
	t1->show();
	Student* s1 = new Student("王小明",14,"玩","英语","上课时间");
	s1->show();
	Doctor* d1  = new Doctor("李时珍",56,"望闻问切","中药学","任何时间");
	d1->show();

	return 0;
}
