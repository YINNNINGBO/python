#include <iostream>
using namespace std;
class stock{

	private:
		int  m1;
	public:
		stock(void){
		//	int m1;
			cout<<"stock(void)"<<endl;
		}
		stock(int n){
			m1 = n;
			cout<< "stock(int n)"<<m1<<endl;
		}
};
int main(void)
{
	stock mm;
	return 0;

}
