#include <iostream>
#include <cstdlib>
#include <string>
#include <string>
#include <sstream>
#include <locale>
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

Tweet::~Tweet()
{}
	// delete user_}

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
	set<string> tags_;
	string temp = text_;
    
    string tagline; 
    locale loc;
    stringstream ss(temp);

    while(ss >> tagline){
      if(tagline[0]=='#'){
        tagline.erase(0, 1);
        //for (string::size_type i=0; i<tagline.length(); ++i){
    		//tagline = tolower(tagline,loc);
        //}
        //cout << tagline << endl;
        tags_.insert(tagline);
      }
      else{
      	continue;
      }
    }


    return tags_;
}



bool Tweet::operator<(const Tweet& other) const
{
	if(time_ < other.time_) {return true;}
	else {return false;}
}

std::ostream& operator<<(std::ostream& os, const Tweet& t)
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




