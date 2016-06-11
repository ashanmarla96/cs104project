#include "../lib/setstr.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include <stdexcept>
using namespace std;

SetStr::SetStr() : index(0)
{}

SetStr::SetStr(const SetStr& other)
{
	for(int i=0; i < other.size(); i++){
		this->list_.push_back(other.list_.get(i));
	}
}

SetStr& SetStr::operator=(const SetStr& other)
{
	if(this == &other){
		return *this;
	}

	if(!this->list_.empty()){
		this->list_.clear();
	}

	for(int i=0; i < other.size(); i++){
		this->list_.push_back(other.list_.get(i));
	}

	return *this;
}

SetStr::~SetStr()
{
	list_.clear();
}

int SetStr::size() const
{
	return list_.size();
}

bool SetStr::empty() const
{
	return list_.empty();
}

void SetStr::insert(const string& val)
{
	if(list_.size() == 0){
		list_.push_back(val);
	}
	else{
		for(int i=0; i < list_.size(); i++){
			if(list_.get(i) == val){
				return;
			}
		}
		list_.push_back(val);
	}
}

void SetStr::remove(const string& val)
{
	if(list_.size() == 0){
		return;
	}
	else{
		for(int i=0; i < list_.size(); i++){
			if(list_.get(i) == val){
				list_.remove(i);
			}
		}
		return;	
	}

	
}

bool SetStr::exists(const string& val) const
{
	if(list_.size() == 0){
		return false;
	}
	else{
		for(int i=0; i < list_.size(); i++){
			if(list_.get(i) == val){
				return true;
			}
		}
		return false;
	}
}



string const* SetStr::first()
{
	if(list_.empty()){
		return NULL;
	}

	return &(list_.get(0));
	index = 0;
	index += 1;
}

string const* SetStr::next()
{
	if(index >= list_.size()){
		return NULL;
	}
	else{
		string* temp = &(list_.get(index));
		index += 1;
		return temp;
		//return &(list_.get(index));
	}
	//index += 1;
	
}


SetStr SetStr::setUnion(const SetStr& other) const
{
	SetStr newSet(*this);
	string temp;

	if(other.size() == 0){
		return newSet;
	}

	for(int i; i < other.size(); i++){
		temp = other.list_.get(i);
		if(!newSet.exists(temp)){
			newSet.insert(temp);
		}
	}
	return newSet;
}

SetStr SetStr::setIntersection(const SetStr& other) const
{
	SetStr newSet;
	string temp;

	if(other.size() == 0){
		return newSet;
	}
	
	for(int i; i < other.size(); i++){
		temp = other.list_.get(i);
		if(this->exists(temp)){
			newSet.insert(temp);
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

SetStr SetStr::operator|(const SetStr& other) const
{
	return setIntersection(other);
}

SetStr SetStr::operator&(const SetStr& other) const
{
	return setUnion(other);
}
