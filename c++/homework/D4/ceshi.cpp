#include <iostream>
#include <cstring>
using namespace std;
int main(void )
{
	int  num[8]= {6,4,8,2,10,77,12,1};
	int *arr = num;
	int tmp = 0;
	for(int i= 0; i < 8; i++){
		for( int j = i; j <8 ;j++){
			if(arr[i] > arr[j+1] ){
				tmp = arr[j+1];
				arr[j+1] = arr[i] ;
				arr[i] = tmp;
			}
		}
	}
for(int i =0  ; i < 8; i++)
{
	cout << arr[i]<< "  ";
}
	return 0;
}
