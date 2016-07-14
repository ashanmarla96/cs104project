#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include "rbbst.h"
using namespace std;

void parse(char* filename, vector<vector<int> >& clause, int& numVar, map<int, int> vartemp)
{
	ifstream infile(filename);
	if(infile.fail()){
		cerr << "Error opening file" << endl;
		return;
	}


	int numClause;
	vector<int> part;
	string line;

	while(getline(infile, line)){
		stringstream ss(line);
		string fword;
		ss >> fword;
		if(fword == "c"){
			continue;
		}
		else if(fword == "p"){
			ss >> fword;
			ss >> numVar;
			ss >> numClause;
			break;
		}
	}

	while(getline(infile, line)){
		stringstream ss2(line);
		int var;
		while(ss2 >> var){
			if(var == 0){
				continue;
			}
			part.push_back(var);
		}
		clause.push_back(part);
		part.clear();
	}

	/*for(unsigned int i=0; i<clause.size(); i++){
		for(unsigned int j =0; j<clause[i].size(); j++){
			cout << clause[i][j] << " ";
		}
		cout << clause[i].size();
		cout << endl;
	}*/
	//map<int, int>::iterator it = 

	
}

bool isValid(vector<vector<int> >& clause, int& numVar);

bool solveHelper();

void solve();

void print();

int main(int argc, char* argv[])
{
	if(argc < 3){
		cerr << "Provide an input and output file" << endl;
		return 1;
	}

	RedBlackTree<int, int> vars;
	vector<vector<int> > clauses;
	map<int, int> vartemp;
	int numVar;

	parse(argv[1], clauses, numVar, vartemp);
	//solve();

	return 1;
}



