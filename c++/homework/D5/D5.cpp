#include <iostream>
#include <cstring>
using namespace std;
/*
	编程实现一个Date类，私有成员包括年月日，实现对
	应的带参构造函数、无参构造函数、类型转换构造函数
	（Date data=20230325）
*/
class Date{
	private:
		int *year ;
		int *month ;
		int *day ;
	public:
		Date(void);
		// 	Date(int y = 0 ,int m = 0 , int d = 0); 是默认构造函数 
		// 	与Date(void) 冲突  有二意性 错误
		Date(int y ,int m , int d);
		Date(int* y,int* m , int *d );
		~Date(void);
		const Date& operator =(const long int& other ){
			if (this->year == nullptr || this->month == nullptr || this->day == nullptr) {
				year = new int;
				month = new int;
				day = new int;
			}

			// 从 long int 中提取年、月、日
			*year = other / 10000;  // 提取前4位作为年份
			*month = (other % 10000) / 100;  // 提取中间2位作为月份
			*day = other % 100;  // 提取最后2位作为日期

			return *this; // 返回当前对象的引用
		} 
		void show(void) const {
			cout <<get_y()<<" 年,"<<get_m()<<"月,"<<get_d()<< "日"<<endl;
		}
		const int get_y(void) const;
		const int get_m(void) const;
		const int get_d(void) const;
};
//  int 类型成员 主动申请空间 赋值
Date::Date() : year(new int(0)), month(new int(0)), day(new int(0)) {
	std::cout << "Date(void) called" << std::endl;
	cin >> *year >> *month >> *day;
}
// 构造函数 定义  不需要指明 默认初始化值
Date::Date(int y, int m, int d) : year(new int(y)), month(new int(m)), day(new int(d)){
	cout << " Date(int y ,int m , int d)" << endl;
}
/*
 * Date::Date(int y, int m, int d) {
    // Dynamically allocate memory for each member variable
    year = new int;
    month = new int;
    day = new int;

    // Initialize the allocated memory with the provided values
    *year = y;
    *month = m;
    *day = d;

    std::cout << "Date(int y, int m, int d) called" << std::endl;
}
*/
Date::Date(int* y,int* m , int *d ){
	cout << "Date(int* y,int* m , int *d )" ;
    year = y;
	month = m;
	day =  d;
	cout << "input over " <<endl; 
}
Date::~Date(void){
	cout << " ~Date(void)" << endl;
	delete year;
	delete month;
	delete day;
}
const int Date::get_y(void) const{
	return *year;
}
const int Date::get_m(void) const{
	return *month;
}
const int Date::get_d(void) const{
	return *day;
}

int main(void)
{
	int y = 1949;
	int m = 10;
	int d = 1;
	int* y1 = &y;
	int* m1 = &m;
	int* d1 = &d;

	Date * date0 = new Date;
	Date * date1 = new Date(y1, m1, d1);
	Date * date2 = new Date(y, m, d);
	date0->show();
	date1->show();
	date2->show();
	cout << "= 20230325" << endl;
//	Date date;
//	date= 20230325;
	(*date2) = 20230325;
	date2->show();
	return 0;
}
