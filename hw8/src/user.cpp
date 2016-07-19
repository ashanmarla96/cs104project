#include <string>
#include <set>
#include <list>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include "../lib/user.h"
#include "../lib/mergesort.h"
#include "../lib/tweet.h"
#include "../lib/datetime.h"
using namespace std;

User::User(std::string name) : name_(name)
{}

User::User(string name, int pass) : name_(name), pass_(pass)

User::User(const User*& other)
{
	this->name_ = other->name_;
}

User::~User()
{
}

string User::name() const
{
	return name_;
}

int User::password() const
{
  return pass_;
}

set<User*> User::followers() const
{
	return followers_;
}

set<User*> User::following() const
{
	return following_;
}

list<Tweet*> User::tweets() const
{
	return tweets_;
}

void User::addFollower(User* u)
{
	followers_.insert(u);
}

void User::addFollowing(User* u)
{
	// cout << "Inside User" << name_ << " following " << u->name_ << endl; 
	following_.insert(u);
}

void User::addTweet(Tweet* t)
{
	tweets_.push_back(t);
}

void User::addMentionedTweet(Tweet* t)
{
  mentioned.push_back(t);
}

void User::addMentionTweet(Tweet* t){
  mention.push_back(t);
}


User* User::operator=(const User*& other)
{
	if(this == other) {return this;}
	if(this != NULL) {delete other;}
	
	this->name_ = other->name_;
	
	return this;
}



vector<Tweet*> User::getFeed()
{
  vector<Tweet*> totTweets;
  set<User*>::iterator it;

  if(!tweets_.empty()){

     for(list<Tweet*>::iterator it3 = tweets_.begin(); it3 != tweets_.end(); ++it3){
     	totTweets.push_back(*it3);
   		} 
  }

  if(!following().empty()){
   for( it = following_.begin(); it != following_.end(); ++it){
   		//cout << this->name_ <<" following " << (*it)->name_ << endl;
   					list<Tweet*> temp;
        temp = (*it)->tweets();
        for (list<Tweet*>::iterator it2 = temp.begin(); it2 != temp.end(); ++it2){
            //cout << **it2 << endl;
            totTweets.push_back(*it2);
        }
    }
  }

  if (!totTweets.empty()){
      mergeSort(totTweets, TweetComp());
      vector<Tweet*>::iterator itt;
      itt = unique(totTweets.begin(), totTweets.end());
      totTweets.resize(distance(totTweets.begin(), itt));

    	
     
  }
  return totTweets; 
}




vector<Tweet*> User::getMenFeed(){
  
  vector<Tweet*> mentweets;
  list<Tweet*>::iterator twitit;

  for(twitit = mentioned.begin(); twitit != mentioned.end(); ++twitit) {
      mentweets.push_back(*twitit);
  }

  mergeSort(mentweets, TweetComp());
  return mentweets;
}

