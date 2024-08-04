#include <iostream>
#include <cstring>
using namespace std;

class People{
    private:
        string m_name;
        int m_age;
    public:
       People(const string& a,const int& b ):m_name(a),m_age(b) {
           cout << "People(..)" << endl; 
       }
       virtual ~People(void) {
           cout << "~People()" << endl; 
       }
      virtual const string getn(void) const {return m_name;}
      virtual const int geta(void) const {return m_age;}
       virtual void show(void) const{
           cout << "名字" << m_name
                << "年齡 " << m_age << endl;
       }
};
class Teacher:public People{
    private:
        string doing;//状态 
        string discipline;// 学科
    public:
        Teacher(const string& a,const int& b,const string& c ,const string& d):People(a,b),doing(c),discipline(d){
            cout << "Teacher(....)" << endl;
        }
        ~Teacher(void){ 
            cout << "~Teacher()" << endl;
        }
        void show(void) const {
            cout << "教師名字" << getn() 
                 << "年龄" << geta()
                 << "正在" << doing
                 << "教学科目 "     << discipline << endl;
        }
        const string getdo(void) const { return doing; }
        const string getdi(void) const {return discipline; }
};
class Student:public People{
    private:
       	 string doing;//状态  玩 or 学习
         string discipline;// 学科
         string whattime;  // 上课时间 还是 下课时间
    public:
        Student(const string& a,const int& b,const string& c ,const string& d,const string& e):People(a,b),doing(c),discipline(d),whattime(e) {
            cout << "Student(....)" << endl;
        }
        ~Student(void){
            cout << "~Student()" << endl;
        }
        void show(void) const{
               cout << "学生" << getn() 
                 << "年龄" << geta()
                 << "在"<< whattime << "时间段"
                 << "正在 " << doing
                 << "所学科目 "     << discipline << endl;
        }
        const string getw(void) const {return whattime;}
        
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
int main()
{
   // std::cout.imbue(std::locale("zh_CN.UTF-8"));
	People* p1 = new People("张三",18);
	p1-> show();
	Teacher* t1 = new Teacher("李春霞",27,"上课","英语");
	t1->show();
	Student* s1 = new Student("王小明",14,"玩","英语","上课时间");
	s1->show();
	Doctor* d1  = new Doctor("李时珍",56,"望闻问切","中药学","任何时间");
	d1->show();


      
    return 0;
} 
