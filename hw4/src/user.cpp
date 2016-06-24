#include <string>
#include <set>
#include <list>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include "../lib/user.h"
#include "../lib/tweet.h"
#include "../lib/datetime.h"
using namespace std;

User::User(std::string name) : name_(name)
{}

User::User(const User*& other)
{
	this->name_ = other->name_;
}

User::~User()
{
	set<User*>::iterator it;
	for(it = followers_.begin(); it != followers_.end(); it++){
		User* temp = *it;
		followers_.erase(it);
		delete temp;
	}

	set<User*>::iterator it2;
	for(it2 = following_.begin(); it2 != following_.end(); it2++){
		User* temp = *it2;
		following_.erase(it2);
		delete temp;
	}


	list<Tweet*>::iterator it3;
	for(it3= tweets_.begin(); it3 != tweets_.end(); it3++){
		Tweet* temp = *it3;
		tweets_.erase(it3);
		delete temp;
	}

}

string User::name() const
{
	return name_;
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


  //int temp_count =  following().size(); 
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
            totTweets.push_back(*it2);
        }
    }
  }

  if (!totTweets.empty()){

    	sort(totTweets.begin(), totTweets.end(), TweetComp());
     
  }

  cout << "Get feed" << endl;
  for(unsigned int i = 0; i < totTweets.size(); i++)
  {
  	cout << *(totTweets[i]) << endl;
  }
  return totTweets; 
}

