/******************************************************************************

假定居民的基本数据包括身份证号、姓名、性别和出
生日期,而居民中的成年人又多 两项数据:最高学历和职
业,成年人中的党员又多一项数据:党员类别。现要求建
立三个类,让成年人类继承居民类,而党员类继承成年人
类,并要求在每个类中都提供有数 据输入和输出的功
能。

*******************************************************************************/
#include <iostream>
#include <cstring>
using namespace std;

class Human{
    private:
        long int ID;
        string name;
        string gender;
        int born_date[3];
    public:
        Human(void):ID(0),name("none"),gender("none "),born_date{0,0,0} {
            cout << "Human(void)" << endl; 
        }
        Human( const long  int& a,const string&  b,const string& c,int* d):ID(a),name(b),gender(c),born_date{d[0],d[1],d[2]}{
            cout << "含参Huma(...)" << endl;
        }
        virtual ~Human(void){
            cout << "~Human" << endl;
        }
        virtual void show(void) const{
              cout << "身份ID:" << ID << " 名字:" << name << " 性别:" <<gender << " 出生年月日:";
              cout << born_date[0] << '-'
                   << born_date[1] << '-'
                   << born_date[2] <<  endl;
        }
        int getID(void) const {return ID;}
        const string getname(void) const {return name;}
        const string getgender(void) const {return gender;}
        const int* getdate(void) const {return born_date;}
};
class Adult_human:public Human{
    private:
        string degree;//学位
        string posts;// 职位
    public:
    Adult_human(void):Human(),degree("none"),posts( "none"){
        cout << "Adult_human()" << endl;
    }
    Adult_human(const long  int& a,const string&  b,const string& c,int* d,const string& e,const string& f):Human(a,b,c,d),degree(e),posts(f){
        cout << "含参Adult_human(...)" << endl;
    }
    virtual ~Adult_human(void){
        cout << "~Adult_human()" << endl;
    }
    void show(void) const{
              cout << "成年人ID:" << getID() << " 名字:" << getname() << " 性别:" <<getgender() << " 出生年月日:";
              cout << getdate()[0] << '-'
                   << getdate()[1] << '-'
                   << getdate()[2] <<  endl;
              cout << " 学位:" << degree << " 职位:" << posts << endl;
        }
        const string getdegree(void) const { return degree; }
        const string getposts(void) const {return posts; }
};
class Party_member:public Adult_human{
    private:
        string cpc_type;//党员类别
    public:
        Party_member():Adult_human(){
            cpc_type = "none";
        }
        Party_member(const long  int& a,const string&  b,const string& c,int* d,const string& e,const string& f,const string& g):Adult_human(a,b,c,d,e,f),cpc_type(g){
            cout << "含参Party_name(....)" << endl;
        }
        ~Party_member(void){
            cout << "~Party_menber()" << endl;
        }
        void show(void) const{
              cout << "党员ID:" << getID() << " 名字" << getname() << " 性别:" << getgender() << " 出生年月日: ";
              cout << getdate()[0] << '-'
                   << getdate()[1] << '-'
                   << getdate()[2] <<  endl;
              cout << " 学位:" << getdegree() << " 职位:" << getposts() << " 党员类别:"<< cpc_type<< endl;
        }
        const string getcpc(void) const {return cpc_type;}
        
};
int main()
{
    int date1[3] = {2012,10,06};
    int date2[3] = {2008,10,01};
    int date3[3] = {2023,03,25};
    Human *person[3];
     person[1] = new Human(1234567,"张三","男",date1);
    person[1]->show();
     person[2] = new Adult_human(23456543,"王五","男",date2,"学士","经理");
    person[2]->show(); 
     person[3] = new Party_member(4765456,"刘爱国","男",date3,"硕士","村委书记","村级干部");
    person[3]-> show();
    return 0;
}