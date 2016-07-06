#include "lib/mergesort.h"
#include <iostream>
#include <vector>
using namespace std;

struct intComp
{
  bool operator()(int t1, int t2)
  {
    return (t1 < t2);
  }
};

/*int main(){
	vector<int> myvec;
	for(int i = 10; i > 0; i--){
		//cout << i;
		myvec.push_back(i);
		
	}
	for (unsigned int i = 0; i < myvec.size(); ++i)
	{
		cout << myvec[i] << endl;
	}

	cout << endl << endl << endl;
	mergeSort(myvec, intComp());
	for (unsigned int i = 0; i < myvec.size(); ++i)
	{
		cout << myvec[i] << endl;
	}
}*/

