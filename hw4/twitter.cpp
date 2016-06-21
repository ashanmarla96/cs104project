#include <iostream>
#include <sstream>
#include <string>
#include "lib/user.h"
#include "lib/tweet.h"
#include "lib/twiteng.h"
#include "lib/datetime.h"

using namespace std;

void displayTweets(vector<Tweet*>& hits);

int main(int argc, char* argv[])
{
  if(argc < 2){
    cerr << "Please provide the twitter data file" << endl;
    return 1;
  }
  TwitEng twit;

  if ( twit.parse(argv[1]) ){
    cerr << "Unable to parse " << argv[1] << endl;
    return 1;
  }


  cout << "=====================================" << endl;
  cout << "Menu: " << endl;
  cout << "  AND term term ...                  " << endl;
  cout << "  OR term term ...                   " << endl;
  cout << "  TWEET username tweet_text" << endl;
  cout << "  QUIT (and write feed files)        " << endl;
  cout << "=====================================" << endl;

  string sstrategy;
  int strategy;
  vector<string> query;
  string term;
  cout << "Enter command:" << endl;
  cin >> sstrategy;
  /*if(sstrategy == "AND")
    strategy = 0;
  if(sstrategy == "OR")
    strategy = 1;
  while (cin >> term)
    query.push_back(term);*/


  //twit.search(query, strategy);

  return 0;
}
