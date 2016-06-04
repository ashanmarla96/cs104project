#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "lib/stackint.h"
using namespace std;

void readFile(char* filein, char* fileout, StackInt*& s){
	ifstream infile(filein);
	if(infile.fail()){
		cerr << "Error opening file" << endl;
		return;
	}
	ofstream outfile(fileout);
	if(outfile.fail()){
		cerr << "Error creating file" << endl;
		return;
	}
	
	string txtline;
	int num;
	getline(infile, txtline);
	stringstream ss(txtline);
	while(ss >> num){ //reading in number from file
		if(num == 0 || num == -1){
			s->push(num); //push to stack
		}
		else if(num > 0){
			for(int i=0; i<num; i++){ //iterating through the given pos num
				if(s->empty()){
					break;
				}
				else if(s->top() == 0){
					outfile << "black" << " ";
					s->pop();

				}
				else if(s->top() == -1){
					outfile << "white" << " ";
					s->pop();
				}
				
			}
			outfile << endl;
		}
	}
}

int main(int argc, char* argv []){
	if(argc < 3){
   		cerr << "Usage $(BIN_DIR)/laundry input_file output_file" << endl;
  	}

  	StackInt* s = new StackInt();
  	readFile(argv[1], argv[2], s);
}