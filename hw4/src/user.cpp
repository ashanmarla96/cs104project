#include <string>
#include <set>
#include <list>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "../lib/user.h"
#include "../lib/tweet.h"
#include "../lib/datetime.h"
using namespace std;

User::User(std::string name) : name_(name)
{}

User::~User()
{
	followers_.clear();
	delete followers_;
	tweets_.clear();
	delete tweets_;
	following_.clear();
	delete following_;
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

list<Tweet*> tweets() const
{
	return tweets_;
}

void User::addFollower(User* u)
{
	followers_.push_back(u);
}

void User::addFollowing(User* u)
{
	following_.push_back(u);
}

void User::addTweet(Tweet* t)
{
	tweets_.push_back(u);
}

User*& operator=(const User*& other)
{
	if(this == &other) {return *this;}
	if(this != NULL) {/*call the destructor*/}
	
	this->name_ = other.name_;
	
	return *this
}

/*vector<Tweet*> User::getFeed()
{

}
*/