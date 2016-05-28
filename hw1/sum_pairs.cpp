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

	infile >> count;
	int* numList = new int[count];

	for(int i=0; i<count; i++){
		infile >> num;
		numList[i] = num;
	}

	infile.close();
	int newcap = ceil((double)count/2);
	int* sumList = new int[newcap];

	int start = 0;
	int end = count-1;
	
	for (int i = 0; i < newcap; ++i){
		sumList[i] = numList[start] + numList[end];
		start += 1;
		end -= 1;
		//cout << sumList[i] << endl;
	}

		

	if (outfile.fail()){
		cerr << "Error opening output file";
	}
	else{
		if(count == 0){
			outfile << 0;
		}
		else{
			//iterate through sum list and output to file
			for(int i=0; i < newcap; i++){
				outfile << sumList[i] << endl;;
			}
		}
	}

	//de-allocating memory 
	delete [] numList;
	delete [] sumList;

}

