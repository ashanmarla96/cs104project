#include <map>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <cctype>
#include "lib/setstr.h"
using namespace std;

int main(int argc, char* argv [])
{
	/*if(argc < 4){
		cout << "Usage bin/sentences input_file command prompt out_file" << endl;
	}*/

	ifstream infile(argv[1]);
	if(infile.fail()){
		cout << "Error opening file" << endl;
		return 1;
	}
	
	ifstream cmdfile(argv[2]);
	if(cmdfile.fail()){
		cout << "Error openin fie" << endl;
		return 1;
	}
	
	SetStr stud_set;
	map<string, SetStr> my_map;

	string textLine;
	while(getline(infile, textLine)){
		stringstream ss(textLine);
		
		string student;
		string major;
		while(getline(ss, student, ',')){

			if(isspace(student[student.size()-1])){
  				student.erase(student.size()-1,1);
			} 
  					
			cout << student << endl;
			stud_set.insert(student);
			cout << stud_set.size() << endl;
			while(getline(ss, major)){
				stringstream ssmaj(major);
				string major_;
				while(ssmaj >> major_){
					for(unsigned int i=0; i<major_.size(); i++){
     					if(major_[i] == ' ') major_.erase(i,1);
     					major_[i] = toupper(major_[i]);
					}
					//cout << student << endl;
					//cout << "!" + major_ << endl;
				}

				
			}
		}
	}


	


}

