#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <cstring>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

int main(int argc, char* argv []){
	if(argc < 2){
		cerr << "Include an input file" << endl;
		return 1;
	}

	ifstream infile(argv[1]);
	if(infile.fail()){
		cerr << "Error opening file" << endl;
		return 1;
	}
	int numLines = 0;
	vector<string> users;
	vector<string> hashtags;

	string textLine;
	while(getline(infile, textLine)){
		
		stringstream ss(textLine);
		string temp, skip;

		while(getline(getline(ss, skip, '@'), temp, ' ')){
			if(!ss.fail()){
				stringstream ss2(temp);
				string user;
				while(ss2 >> user){
					users.push_back(user);
					ss2.clear();
				}

			}
		}

		stringstream ss3(textLine);
		string temp2, skip2;

		while(getline(getline(ss3, skip2, '#'), temp2, ' ')){
			if(!ss3.fail()){
				stringstream ss4(temp2);
				string hastag;
				while(ss4 >> hastag){
					hashtags.push_back(hastag);
					ss4.clear();
				}

			}
		}
		
		if(!textLine.empty()){
			numLines += 1;
		}
	}


	//below code is to remove duplicates from users and hashtags
	sort(users.begin(), users.end());
	users.erase(unique(users.begin(), users.end()), users.end());
	
	sort(hashtags.begin(), hashtags.end());
	hashtags.erase(unique(hashtags.begin(), hashtags.end()), hashtags.end());
	
	//below is outputed twitter data
	cout << "1. Number of tweets=" << numLines << endl;
	
	cout << "2. Unique users" << endl;
	for (unsigned int i = 0; i < users.size(); ++i){
		cout << users[i] << endl;
	}
	
	cout << "3. Unique hashtags" << endl;
	for (unsigned int i = 0; i < hashtags.size(); ++i){
		cout << hashtags[i] << endl;
	}

}