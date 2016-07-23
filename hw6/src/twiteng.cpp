#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <ctime>
#include <stack>
#include <cstring>
#include "../lib/twiteng.h"
// #include "../lib/tarjan.h"
using namespace std;

TwitEng::TwitEng()
{}

TwitEng::~TwitEng()
{	
	vector<Tweet*>::iterator it;
	for(it = tweets_.begin(); it != tweets_.end(); ++it){
		Tweet* temp = *it;
		// tweets_.erase(it);
		delete temp;
	}

	map<string, User*>::iterator it2;
	for(it2 = allUsrs.begin(); it2 != allUsrs.end(); ++it2){
		User* temp = it2->second;
		// allUsrs.erase(it2);
		delete temp;
	}


}

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
		map<string, User*>::iterator it = allUsrs.find(myuser);
		if(it != allUsrs.end()){ 
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
			myuserptr->addFollowing(myfollowingptr);
			myfollowingptr->addFollower(myuserptr);
			//delete myuserptr;
		}

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

		DateTime dt;
		map<string, User*>::iterator usertweet;
		
		//for mentions
		string firstmen;
		vector<string> mentions_;
		bool mentrigger = false;
		bool mentrigger2 = false;


		string datetimewow;

		
		while(ss3 >> temp_str){
			index += 1;

			if(index==1){
				//dt= new DateTime();
				datetimewow = temp_str;
				ss3>>temp_str;
				datetimewow+=" "+temp_str;
				
				stringstream ss (datetimewow);

				ss>>(dt);
			}	

			else if(index == 2){
				usr_ = temp_str;
				usertweet = allUsrs.find(usr_);
				//cout << theuser << endl;
			}
			
			else if(index > 2){
				twt_ = twt_ + temp_str + " ";

				if(temp_str[0] == '@'){
					if(index == 3){
						mentrigger = true;
						//cout << "reach this mention"
						firstmen = temp_str;
						firstmen.erase(0,1);
					}
					else if(index > 3){
						mentrigger2 = true;
						//cout << "reached this mention"
						string secondmen;
						secondmen = temp_str;
						secondmen.erase(0,1);
						mentions_.push_back(secondmen);
					}
				}

			}
			
		}
		//cout << twt_ << endl;
		Tweet* tweet_placeholder = new Tweet((usertweet->second), dt, twt_);



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

		if(mentrigger == true || mentrigger2 == true){
			if(mentrigger){
				map<string, User*>::iterator it = allUsrs.find(firstmen);
				it->second->addMentionedTweet(tweet_placeholder);
				
				usertweet->second->addMentionTweet(tweet_placeholder);
			}

			else if(mentrigger2){
				for(unsigned int i = 0; i < mentions_.size(); ++i){
					map<string, User*>::iterator guessit = allUsrs.find(mentions_[i]);
					if(guessit != allUsrs.end()){
						guessit->second->addMentionedTweet(tweet_placeholder);
					}
				}

				usertweet->second->addTweet(tweet_placeholder);
			}
		}
		else{
			usertweet->second->addTweet(tweet_placeholder);
		}
		
		tweets_.push_back(tweet_placeholder);
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
		allUsrs.insert(make_pair(username, userptr));
		it = allUsrs.find(username);
	}
	Tweet* newTweet = new Tweet(userptr, time, text);
	tweets_.push_back(newTweet);
	//userptr->addTweet(newTweet);

	stringstream ss(text);
	bool mentrigger_ = false;
	bool mentrigger2_ = false;
	string firstmen_;
	string secondmen_;
	vector<string> _mentions;

	string temper; 
	int posn=0;
	while(ss >> temper){
		if(temper[0] == '@'){
			if(posn == 0){
				mentrigger_ = true;
				firstmen_ = temper;
				firstmen_.erase(0,1);
			}
			else if(posn >= 1){
				mentrigger2_ = true;
				secondmen_ = temper;
				secondmen_.erase(0,1);
				_mentions.push_back(secondmen_);
			}
		}

		posn += 1;
	}

	
	if(mentrigger_ == true || mentrigger2_ == true){
		if(mentrigger_){
			map<string, User*>::iterator menit = allUsrs.find(firstmen_);
			menit->second->addMentionedTweet(newTweet);
			
			it->second->addMentionTweet(newTweet);
			
		}

		else if(mentrigger2_){
			for(unsigned int i = 0; i < _mentions.size(); ++i){
				map<string, User*>::iterator munit = allUsrs.find(_mentions[i]);
				if(munit != allUsrs.end()){
					(munit->second)->addMentionedTweet(newTweet);
				}
			}

			it->second->addTweet(newTweet);

		}
	}
	else{
		it->second->addTweet(newTweet);
	}

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
		//cout << "no intersection" << endl;
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

void TwitEng::feedStart()
{
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
		  result = search(query, 0);

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

		  result = search(query, 1);

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

		  
		  DateTime* dt = new DateTime(timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,timeinfo->tm_year + 1900, timeinfo->tm_mon,  timeinfo->tm_mday);
		  addTweet(name_, *dt, text);
		}

		else if(sstrategy == "QUIT"){
		  dumpFeeds();
		  break;
		}
  	}
}

void TwitEng::dumpFeeds()
{
	for(map<string, User*>::iterator it = allUsrs.begin(); it != allUsrs.end(); ++it){

		string filename = it->first + ".feed";
		string menfilename = it->first + ".mentions";

		ofstream ofile(filename.c_str());
		ofstream menfile(menfilename.c_str());
		// cout<< endl<<endl<<endl;
		ofile << it->first << endl;
		vector<Tweet*> tempTweetsVec = (it->second)->getFeed();
		for(unsigned int i=0; i < tempTweetsVec.size(); ++i){
			ofile << (*(tempTweetsVec[i])) << endl;
		}

		menfile << it->first << endl;
		vector<Tweet*> mentweets = (it->second)->getMenFeed();
		for(unsigned int i=0; i<mentweets.size(); ++i){
			menfile << (*(mentweets[i])) << endl;
		}
	}
}

map<string, User*> TwitEng::getUsers()
{
	return allUsrs;
}

void TwitEng::tarjan()
{
	vector<vector<int> > doubhold;

	vector<User*> userVec;
	for(map<string, User*>::iterator it = allUsrs.begin(); it != allUsrs.end(); ++it)
	{
		userVec.push_back(it->second);
		it->second->t_index = userVec.size() -1;
	}

	for(unsigned int i = 0; i < userVec.size(); i++)
	{
		User* u = userVec[i];
		set<User*> followingSet = u->following();
		vector<int> temp;
		for(set<User*>::iterator it = followingSet.begin(); it != followingSet.end(); ++it)
		{
			temp.push_back((*it)->t_index);
		}
		doubhold.push_back(temp);

	}

	/*for(unsigned int i = 0; i < doubhold.size(); i++)
	{
		cout << "Index i =" << i << ":";
		for(unsigned int j = 0; j < doubhold[i].size(); j++)
		{
			cout << doubhold[i][j]<< " ";
		}
		cout<< endl;
	}*/
	vector<int> tempIndex;
	for(unsigned int i=0; i<userVec.size(); i++){
		tempIndex.push_back(-1);
	}
	vector<int> tempLow;
	for(unsigned int i=0; i<userVec.size(); i++){
		tempLow.push_back(-1);
	}
	stack<int> S;

	int disc = 0;
	vector<int> in_stack;
	for(unsigned int i=0; i<userVec.size(); i++){
		in_stack.push_back(0);
	}

	string filename = "Connections";
    ofstream ofile(filename.c_str());
    int count = 1;

	for(unsigned int i=0; i<userVec.size(); i++){
		if(tempIndex[i] == -1)
		{
			tarjanHelper(i, doubhold, tempIndex, tempLow, S, disc, in_stack, userVec, ofile, count);
		} 
	}




}


// A->B
// B->A
// C

void TwitEng::tarjanHelper(int u,vector< vector<int> > g,vector<int>& index, vector<int>& low_index, 
	stack<int>& S, int& disc, vector<int>& in_stack, vector<User*>& userVec, ostream& ofile, int& count)
{
    
	//cout << "Enter recur" << endl;

    index[u] = low_index[u] = ++disc;
    

    //disc = 0;
	in_stack[u] = 1;
	S.push(u);
	for(unsigned int i = 0;i < g[u].size();i++){
		int v = g[u][i]; 
		if(index[v] == -1){
			tarjanHelper(v,g,index,low_index, S, disc, in_stack, userVec, ofile, count);
			low_index[u] = min(low_index[v],low_index[u]);
		}
	                          		           
		else if(in_stack[v] == 1){
			low_index[u] = min(low_index[u],index[v]);
		}          
		        
	}
	//cout << "Index = " << index[u] << " Low = " << low_index[u] << endl; 
	
	if(index[u] == low_index[u])              
	{                 
		//cout << "equal" << endl; 
		//int tup = 1;
		ofile << "Component"  << " " << count << endl;
		cout << "Component" << " " << count << endl;                     
		while(S.empty() == false )
		{
			int i_ = S.top();
			cout<<S.top()<<" ";
			
			ofile << userVec[i_]->name() << endl;
			cout << userVec[i_]->name() << endl; 
			in_stack[S.top()] = 0;	
			S.pop();
			

			if(i_ == u){
				 
				break;
			}
		}
		ofile << endl;
		count += 1;

	}
	//ofile.close();
}