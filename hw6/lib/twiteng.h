#ifndef TWITENG_H
#define TWITENG_H
#include <map>
#include <string>
#include <set>
#include <vector>
#include <stack>
#include <fstream>
#include <string>
#include "user.h"
#include "tweet.h"
#include "datetime.h"


class TwitEng
{
 public:
  TwitEng();
  ~TwitEng();
  /**
   * Parses the Twitter database and populates internal structures
   * @param filename of the database file
   * @return true if there is an error, false if successful
   */
  bool parse(char* filename);

  /**
   * Allocates a tweet from its parts and adds it to internal structures
   * @param username of the user who made the tweet
   * @param timestamp of the tweet
   * @param text is the actual text of the tweet as a single string
   */
  void addTweet(std::string& username, DateTime& time, std::string& text);

  /**
   * Searches for tweets with the given words and strategy
   * @param words is the hashtag terms in any case without the '#'
   * @param strategy 0=AND, 1=OR
   * @return the tweets that match the search
   */
  std::vector<Tweet*> search(std::vector<std::string>& terms, int strategy);

  /**
   * Dump feeds of each user to their own file
   */
   void feedStart();

  void dumpFeeds();

  /* You may add other member functions */
  std::map<std::string, User*> getUsers();

  void tarjan();


  void tarjanHelper(int u,std::vector< std::vector<int> > g,std::vector<int>& index, std::vector<int>& low_index, 
  std::stack<int>& S, int& disc, std::vector<int>& in_stack, std::vector<User*>& userVec, 
  std::ostream& ofile, int& count);
 private:
  /* Add any other data members or helper functions here  */
  //std::string hashtag_;
  //User* meuser;
  std::map<std::string, std::set<Tweet*> > tagmap;
  //std::map<std::string, std::set<Tweet*> > mentionmap;
  std::vector<Tweet*> tweets_;

  std::map<std::string, User*> allUsrs;

  // std::vector<User*> allUsers;


};


#endif
