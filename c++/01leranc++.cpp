#include <iostream>
using namespace std;
class stock{

	private:
		int  m1;
	public:
		stock(void){
			int m1 = 111;
			cout<<"stock(void)"<< " "<<m1<<endl;
		}
		stock(int n){
			m1 = n;
			cout<< "stock(int n)"<<m1<<endl;
		}
		~stock(void ){
			cout << "~stock "<< endl;
		}
};
int main(void)
{
	stock mm;
	stock m2(3);
	return 0;

}
