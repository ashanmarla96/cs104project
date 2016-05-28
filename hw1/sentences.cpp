#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void readWords(char* filename, vector<vector<string> >& words);
// client interface

void generateSentences(vector<vector<string> >& words, ofstream& ofile);
// recursive helper function

void genHelper(vector<vector<string> >& words,
	       ofstream& ofile,
	       int currentOption,
	       string sentence,
	       int& numSentences);

void readWords(char* filename,vector<vector<string> >& words){
	ifstream infile(filename);
	if(infile.fail()){
		cerr << "Error opening file" << endl;
		return;
	}
	
	vector<string> part;

	//parse in words from file
	string txtLine;
	while(getline(infile, txtLine)){
		stringstream ss(txtLine);
		string word;
		while(ss >> word){
			part.push_back(word);
		}
		words.push_back(part);
		part.clear();
	}

	//contigencies for empty adj's/adv's and missing verbs/nouns
	if(words[0].empty()){
		words[0].push_back("");
	}

	if ((words.size() > 2) && (words.size() < 4)){
		part.push_back("");
		words.push_back(part);
		part.clear();
	}

	if (words[1].empty() || words[2].empty()){
		cerr << "missing noun or verb" << endl;
		return;
	}

}

void generateSentences(vector<vector<string> >& words, ofstream& ofile){
	int numSentences = 0;
	genHelper(words, ofile, 0, "The", numSentences);
	ofile << numSentences << " sentences." << endl;
}

void genHelper(vector<vector<string> >& words, ofstream& ofile, int currentOption, string sentence, int& numSentences)
{
  string temp;
  //base case
  if((unsigned) currentOption == words.size()){
  	ofile << sentence << "." << endl;
  	numSentences += 1;
  	return;
  }

  else{
  	//iterate through each part of speech
  	for(unsigned int j=0; j < words[currentOption].size(); j++){
  		//skip over un-needed  words
  		if(words[currentOption][0].empty()){
  			temp = sentence;
  		}
  		else{
  			temp = sentence + " " + words[currentOption][j];
  			if(((currentOption==0)||(currentOption==3)) && (j == (words[currentOption].size())-(unsigned)1)){
				genHelper(words, ofile, currentOption+1, sentence, numSentences);
			}
  		}
		genHelper(words, ofile, currentOption+1, temp, numSentences); 
  	}	
  }

}

int main(int argc, char* argv[]){
  if(argc < 3){
    cerr << "Usage ./sentences input_file output_file" << endl;
  }
  vector<vector<string> > words;

  // Parse the file
  readWords(argv[1], words);

  // Check the status of parsing
  if(words.size() < 4){
    cerr << "Input file requires 4 lines of words" << endl;
    return 1;
  }

  // Open the output file
  ofstream ofile(argv[2]);
 
  // generate all the sentence options writing them to ofile
  generateSentences(words, ofile);

  ofile.close();

  return 0;
}
