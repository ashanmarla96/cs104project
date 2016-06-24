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
	getline(infile, txtLine);
	// cout << "Extra line" << txtLine << endl;
	while( usr_cnt < num_users && getline(infile, txtLine)){

		// cout << "Line " << txtLine << endl;
		stringstream ss(txtLine);
		ss >> myuser;

			// 		cout << "Parsing" << endl;
			// cout << myuser  << endl;

		//cout<<"Created User: "<<myuser<<endl;
		map<string, User*>::iterator it = allUsrs.find(myuser);
		if(it != allUsrs.end()){ 
			// delete myuserptr;
			myuserptr = it->second;
		}
		else
		{
			myuserptr = new User(myuser);
			allUsrs.insert(std::make_pair(myuser, myuserptr));
		}

		while(ss >> myfollowing){
			map<string, User*>::iterator it = allUsrs.find(myfollowing);
			if(it != allUsrs.end()){ 
				myfollowingptr = it->second;
			}
			else{
				myfollowingptr = new User(myfollowing);
				allUsrs[myfollowing] = myfollowingptr;

			}
			// cout << "Parsing" << endl;
			// cout << myuser << " follow " << myfollowing << endl;
			myuserptr->addFollowing(myfollowingptr);
			myfollowingptr->addFollower(myuserptr);
			//cout << "Parsing" << endl;
			//cout << myuser << " follow " << myfollowing << endl;

			// myuserptr->addFollower(myfollowingptr);
			// myfollowingptr->addFollowing(myfollowingptr);
		}
		
		// allUsrs[myuser] = myuserptr;

		// cout << endl;

		usr_cnt += 1;
	}

	//cout << endl;

	string txtLine2;
	while(getline(infile, txtLine2)){
		// cout << "Line" << txtLine2 << endl;
		//cout << txtLine2;
		stringstream ss3(txtLine2);
		//cout << ss3.str() << endl;
		string temp_str;

		int index = 0;


		string twt_;
		string usr_;

		DateTime* dt;
		map<string, User*>::iterator usertweet;

		string datetimewow;

		
		while(ss3 >> temp_str){
			index += 1;

			if(index==1){
				dt= new DateTime();
				datetimewow = temp_str;
				ss3>>temp_str;
				datetimewow+=" "+temp_str;
				
				stringstream ss (datetimewow);

				ss>>(*dt);
			}	

			else if(index == 2){
				usr_ = temp_str;
				usertweet = allUsrs.find(usr_);
				//cout << theuser << endl;
			}
			
			else if(index > 2){
				twt_ = twt_ + temp_str + " ";

			}
			
		}
		//cout << twt_ << endl;
		Tweet* tweet_placeholder = new Tweet((usertweet->second), *dt, twt_);


		set<string> tagss;
		tagss = tweet_placeholder->hashTags();
		for(set<string>::iterator tagssIt = tagss.begin(); tagssIt != tagss.end(); ++tagssIt)
		{
			map<string, set<Tweet*> >::iterator it = tagmap.find(*tagssIt);
			if(it != tagmap.end()){
				(it->second).insert(tweet_placeholder);
			}
			else{
				set<Tweet*> tempSet;
				tempSet.insert(tweet_placeholder);
				tagmap.insert(make_pair(*tagssIt , tempSet));
			}
		}

		
		//dt = new DateTime(hr, min, sec, year, mon, day);
		(usertweet->second)->addTweet(tweet_placeholder); 
		cout << *tweet_placeholder << endl;


	}
	return false;

}

void TwitEng::addTweet(std::string& username, DateTime& time, std::string& text)
{
	User* userptr;
	map<string, User*>::iterator it = allUsrs.find(username);
	if(it != allUsrs.end()){ 
		userptr = it->second;
	}
	else{
		userptr = new User(username);

	}
	Tweet* newTweet = new Tweet(userptr, time, text);
	tweets_.push_back(newTweet);
	userptr->addTweet(newTweet);
}

set<Tweet*> setUnion(const set<Tweet*>& me, const set<Tweet*>& other) 
{
	set<Tweet*> newSet = me;
	//Tweet* temp;

	if(other.size() == 0){
		return newSet;
	}

	set<Tweet*>::iterator setit;
	for(setit = other.begin(); setit != other.end(); ++setit){
		newSet.insert(*setit);
	}
	return newSet;
}

set<Tweet*> setIntersection(const set<Tweet*>& me, const set<Tweet*>& other) 
{
	set<Tweet*> newSet;
	//Tweet* temp;

	if(other.size() == 0){
		return newSet;
	}
	
	set<Tweet*>::iterator setit;
	for(setit = other.begin(); setit != other.end(); ++setit){
		// temp = other.find(*setit);
		if(me.find(*setit) != me.end()) {
			newSet.insert(*setit);
		}
	}

	if(newSet.empty()){
		cout << "no intersection" << endl;
		return newSet;
	}
	else{
		return newSet;
	}
}

std::vector<Tweet*> TwitEng::search(std::vector<std::string>& terms, int strategy)
{
	
	set<Tweet*> result;
	map<string, set<Tweet*> >::iterator mapIt = (tagmap.find(terms[0]));
	if( mapIt != tagmap.end()) 
	{
		result = (mapIt->second);
	}


	for(unsigned int i = 0; i < terms.size(); ++i){
		set<Tweet*> tempSet;
		mapIt = (tagmap.find(terms[i]));
		if( mapIt != tagmap.end()) 
		{
			tempSet = mapIt->second;
		}
		if(strategy == 0){
			result = setIntersection(result, tempSet);
		}
		else if(strategy == 1){
			result = setUnion(result, tempSet);
		}
	}

	vector<Tweet*> disResult;
	set<Tweet*>::iterator setit;
	for(setit = result.begin(); setit != result.end(); ++setit){
		disResult.push_back(*result.find(*setit));
	}

	return disResult;

}

void TwitEng::dumpFeeds()
{



	for(map<string, User*>::iterator it = allUsrs.begin(); it != allUsrs.end(); ++it){


		ofstream ofile(it->first.c_str());//name.feed
		// cout<< endl<<endl<<endl;
		ofile << it->first << endl;
		vector<Tweet*> tempTweetsVec = (it->second)->getFeed();

		// cout<<it->first<<endl;
		// cout << tempTweetsVec.size() << endl;
		for(unsigned int i=0; i<tempTweetsVec.size(); i++){
			ofile<<(*(tempTweetsVec[i]))<<endl;
			// cout<<(*(tempTweetsVec[i]))<<endl;
		}

	}


}
