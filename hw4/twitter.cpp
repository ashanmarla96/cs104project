#include <iostream>
#include <sstream>
#include <string>
// #include <stdlib>
#include <ctime>
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

  
  //int strategy;
  
 // string term;
  cout << "Enter command:" << endl;
  string sstrategy;
  while(cin >> sstrategy){

    if(sstrategy == "AND"){
      string term_;
      vector<string> query;
      vector<Tweet*> result;


      string line;
      getline(cin, line);

      stringstream ss(line);
      while(ss >> term_){
        query.push_back(term_);
      }


      cout << "End" << endl;
      result = twit.search(query, 0);

      if(!result.empty()){
        cout << result.size() << " Matches:" << endl;
        for(unsigned int i =0; i< result.size(); i++){
          cout << *result[i] << endl;
        }
      }
      else{
        cout << "No Matches." << endl;
      }
    }
    
    else if(sstrategy == "OR"){
      string term;
      vector<string> query;
      vector<Tweet*> result;

      string line;
      getline(cin, line);

      stringstream ss(line);
      while(ss >> term){
        query.push_back(term);
      }

      result = twit.search(query, 1);

      if(!result.empty()){
        cout << result.size() << " Matches:" << endl;
        for(unsigned int i =0; i< result.size(); i++){
          cout << *result[i] << endl;
        }
      }
      else{
        cout << "No Matches." << endl;
      }
    }
    
    else if(sstrategy == "TWEET"){
      string name_;
      string text = "";
      time_t rawtime;
      struct tm * timeinfo;
      time (&rawtime);
      timeinfo = localtime(&rawtime);

      cin >> name_; 

      string line;
      getline(cin, line);


      std::size_t found = line.find_first_not_of(" \t");
      line = line.substr(found, line.size());
      text = line;
      cout << text << endl;
      // stringstream ss(line);
      // while(ss >> text){
      //   string temp = text;
      //   text.append(temp);
      // }

      //cout << line << endl;
      
      DateTime* dt = new DateTime(timeinfo->tm_hour, timeinfo->tm_min + 1, timeinfo->tm_sec - 1,timeinfo->tm_year + 1900, timeinfo->tm_mon + 1,  timeinfo->tm_mday + 1);
      twit.addTweet(name_, *dt, text);
    }

    else if(sstrategy == "QUIT"){
      twit.dumpFeeds();
      break;
    }
  }

    return 0;
}

  

