#include <iostream>
#include <sstream>
#include <string>

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

  return 0;
}
