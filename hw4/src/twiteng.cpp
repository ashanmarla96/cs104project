#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include "../lib/twiteng.h"
using namespace std;

TwitEng::TwitEng()
{}

TwitEng::~TwitEng()
{}

bool TwitEng::parse(char* filename)
{
	ifstream infile(filename);
	if(infile.fail()){
		cerr << "Error opening file" << endl;
		return true;
	}
	int num_users;
	int usr_cnt = 0;

	infile >> num_users;

	string myuser;
	string myfollowing;
	User* myuserptr;
	User* myfollowingptr;


	//parse in words from file
	string txtLine;
	while(getline(infile, txtLine) && usr_cnt <= num_users){
		stringstream ss(txtLine);
		ss >> myuser;
		myuserptr = new User(myuser);
		//cout<<"Created User: "<<myuser<<endl;
		map<string, User*>::iterator it = allUsrs.find(myuser);
		if(it != allUsrs.end()){ 
			myuserptr = it->second;
		}
		else{
			while(ss >> myfollowing){
				allUsrs.insert(std::make_pair(myuser, myuserptr));
				//cout << allUsrs.size() << endl;

				//cout << myfollowing << " ";
				myfollowingptr = new User(myfollowing);

				myuserptr->addFollower(myfollowingptr);
				//cout << myuserptr->followers().size() << endl;
			
			}
			
		}

		cout << endl;

		usr_cnt += 1;
	}

	//cout << endl;

	string txtLine2;
	while(getline(infile, txtLine2)){
		//cout << txtLine2;
		stringstream ss3(txtLine2);
		//cout << ss3.str() << endl;
		string temp_str;

		int index = 0;

		int sec, min, hr, day, mon, year;

		string date_placeholder;
		string time_placeholder;

		string twt_;
		string usr_;

		DateTime* dt;
		map<string, User*>::iterator usertweet;


		while(ss3 >> temp_str){
			index += 1;
			if(index == 1){

				date_placeholder = temp_str.substr(0,4);
				year = atoi(date_placeholder.c_str());
				date_placeholder = temp_str.substr(5, 7);
				mon  = atoi(date_placeholder.c_str());
				date_placeholder = temp_str.substr(8, 9);
				day  = atoi(date_placeholder.c_str());
				//date_placeholdertimectr++;
				//cout << year << " " << day << endl;
			}
			else if(index == 2){
				time_placeholder = temp_str.substr(0,2);
				hr    = atoi(time_placeholder.c_str());
				time_placeholder = temp_str.substr(3, 5);
				min   = atoi(time_placeholder.c_str());
				time_placeholder = temp_str.substr(6, 7);
				sec   = atoi(time_placeholder.c_str());
				//cout << hr << " " << min << endl;
			}
			else if(index == 3){
				usr_ = temp_str;
				usertweet = allUsrs.find(usr_);
				//cout << theuser << endl;
			}
			
			else if(index > 3){
				twt_ = twt_ + temp_str + " ";

			}
			
		}
		//cout << twt_ << endl;
		Tweet* tweet_placeholder = new Tweet((usertweet->second), *dt, twt_);
		dt = new DateTime(hr, min, sec, year, mon, day);

		

		(usertweet->second)->addTweet(tweet_placeholder); 


	}
	return false;

}

void TwitEng::addTweet(std::string& username, DateTime& time, std::string& text)
{
	Tweet* newTweet = new Tweet(new User(username), time, text);
	tweets_.push_back(newTweet);
	delete newTweet;
}

std::vector<Tweet*> TwitEng::search(std::vector<std::string>& terms, int strategy)
{
	if(strategy == 0){

	}
	else if(strategy == 1){

	}
	else{

	}

}

void TwitEng::dumpFeeds()
{
	for(map<string, User*>::iterator it = allUsrs.begin(); it != allUsrs.end(); ++it){

		cout<< endl<<endl<<endl;

		tweets_ = (it->second)->getFeed();

		cout<<it->first<<endl;

		for(unsigned int i=0; i<tweets_.size(); i++){
			cout<<(*(tweets_[i]))<<endl;
		}

	}


}