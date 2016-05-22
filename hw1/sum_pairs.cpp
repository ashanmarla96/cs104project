#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]){
	if(argc < 3){
		cerr << "Include an input and output file" << endl;
		return 1;
	}

	ifstream infile(argv[1]);
	if(infile.fail()){
		cerr << "Error opening file" << endl;
		return 1;
	}
	ofstream outfile(argv[2]);
	int count = 0;
	int num = 0;
	
	if(infile.fail()){
		cerr << "Error opening file" << endl;
		return 1;
	}

	infile >> count;
	int* numList = new int[count];

	for(int i=0; i<count; i++){
		infile >> num;
		numList[i] = num;
	}

	infile.close();
	int newcap = ceil(count/2);
	int* sumList = new int[newcap];

	/*for(int i=0; i<count; i++){
		for (int j = count-1; j >= 0; j--)
		{
			sumList[i] = numList[i] + numList[j];
			if(i+1 == j || i == j){
				break;
			}
		}
	}*/

	int start = 0;
	int end = count-1;

	while(start<count && end >= 0){
		sumList[start] = numList[start] + numList[end];
		start += 1;
		end -= 1;
		if(start+1 == end || start == end){
			break;
		}
	}

	if (outfile.fail()){
		cerr << "Error opening output file";
	}
	else{
		if(count == 0){
			outfile << 0;
		}
		else{
			for(int i=0; i < newcap; i++){
				outfile << sumList[i];
			}
		}
	}

	delete [] numList;
	delete [] sumList;

}

