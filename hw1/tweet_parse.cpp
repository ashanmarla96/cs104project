#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <cstring>
#include <vector>
#include <sstream>
using namespace std;

/*HAVENT ACCOUNTED FOR DUPLICATES
	OR MULTIPLE ELEMENTS YET!!!!
	*/

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
		//below code for users
		stringstream ss(textLine);
		string temp;
		getline(ss, temp, '@');
		getline(ss, temp, ' ');
		if(!ss.fail()){
			stringstream ss2(temp);
			string user;
			while(ss2 >> user){
				users.push_back(user);
			}
		}
		//below code for hashtags
		getline(ss, temp, '#');
		getline(ss, temp, ' ');
		if(!ss.fail()){
			stringstream ss3(temp);
			string hastag;
			while(ss3 >> hastag){
				hashtags.push_back(hastag);
			}
		}
		
		if(!textLine.empty()){
			numLines += 1;
		}
	}

	cout << numLines << endl;
	for (int i = 0; i < users.size(); ++i)
	{
		cout << users[i] << endl;
	}
	for (int i = 0; i < hashtags.size(); ++i)
	{
		cout << hashtags[i] << endl;
	}

}