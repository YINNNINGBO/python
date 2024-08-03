#include <iostream>
#include <cstring>
#include <limits>
/*
私有成员为一个长度为8个整型数的数组
公有成员：
输出函数， 输出数组中的内容
输入函数， 输入数组中的所有元素
求和函数， 求得数组中所有元素的和
排序函数， 将数组中的元素进行升序排序
*/
using namespace std;
class A{
    private:
    int *arr = new  int[8];
	int length;
    public:
    A(void){
        memset(arr,0,sizeof(int)*8); 
		cout << "输入数组 可用字母结束" << endl;
		length = 0;
		for(int i = 0 ; i < 8 ;i++){
			int tmp =0;
			cin >> tmp;
			if (cin.fail()) {
				// 清除错误状态并丢弃无效的输入
				cin.clear();  // 清除输入流的错误状态
				cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 丢弃输入流中的剩余字符
				break;  // 输入失败时退出循环
			}
		// 存储有效的整数值到数组
			arr[length] = tmp;
			length++;
		//	tmparr++;  // 移动指针到下一个位置
			/*
			if(typeid(tmp).name() == typeid(char).name())
			{
			return ;
			}else{
			(*tmparr) = tmp;
			tmparr++;
			}	*/

			cout << '|' << endl;
		}
	}
    ~A(void){
        delete arr;
        cout << "~A" << endl;
    }
	int* getarr(void) const{
		return arr;
	}
	const int get_length(void) const {
		return length;
	} 
    void input(const int& a ){
		if(length == 8){
			cout << "数组已经满了" <<endl;
		}else{
			cout << "input: " << endl;
			arr[length] = a;
			length++;
		}
    }
    void output(int * arr) const{
	const	int size = length;
		for(int i =0 ; i< size;i++){
			cout  << arr[i]<<"--";
		}
      cout << endl; 
    }
	int add_arr(void){
		int i = 0;
		for ( int n = 0; n<length ; n++){
			i += arr[n];
		}
		return i;
	}
	int* sort_arr(int *arr) {
		// 冒泡排序
		const int size = length;
		int tmp = 0;
		int* tmpar = new int[size];
		tmpar = arr;
		for(int i= 0; i < size-1; i++){
			for( int j = i; j <size-1 ;j++){
				if(arr[i] > tmpar[j+1] ){
					tmp = tmpar[j+1];
					tmpar[j+1] = tmpar[i] ;
					tmpar[i] = tmp;
				}
			}
		}
		return tmpar;
	}
};
int main()
{
	A* a = new A;
	a->input(11);
	a->output(a->getarr());
	cout << "length is " << a->get_length() << endl;
	cout <<"arr add is :"<< a->add_arr() << endl;
	cout << "顺序排列数组为" << endl;
	a->output(a->sort_arr(a->getarr()));
	return 0;
}
