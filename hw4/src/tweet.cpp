#include <iostream>
#include <cstdlib>
#include <string>
#include <string>
#include <vector>
#include <set>
#include "../lib/tweet.h"
#include "../lib/user.h"
#include "../lib/datetime.h"
using namespace std;

Tweet::Tweet()
{
	user_ = NULL;
	text_ = " ";
	time_.year = 0;
	time_.month = 0;
	time_.day = 0;
	time_.hour = 0;
	time_.min = 0;
	time_.sec = 0;
}

Tweet::Tweet(User* user, DateTime& time, std::string& text) : text_(text)
{
	user_ = user;
	time_.year = time.year;
	time_.month = time.month;
	time_.day = time.day;
	time_.hour = time.hour;
	time_.min = time.min;
	time_.sec = time.sec;
}

DateTime const & Tweet::time() const
{
	return time_;
}

string const & Tweet::text() const
{
	return text_;
}

set<string> Tweet::hashTags() const
{
	return tags_;
}

bool Tweet::operator<(const Tweet& other) const
{
	if(time_ < other.time_) {return true;}
	else {return false;}
}

friend std::ostream& Tweet::operator<<(std::ostream& os, const Tweet& t)
{
	os << t.time_ << " ";
	os << (t.user_)->name() << " ";
	os << t.text_;

	return os;
}

User* Tweet::user() const
{
	return user_;
}




