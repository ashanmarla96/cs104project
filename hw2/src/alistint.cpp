#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "../lib/alistint.h"
using namespace std;

AListInt::AListInt() : size_(0), cap_(10)
{
	data_ = new int[cap_];
}

AListInt::AListInt(int cap) : size_(0), cap_(cap)
{
	data_ = new int[cap_];
}

AListInt::~AListInt()
{
	delete data_;
}

int AListInt::size() const
{
	return size_;
}

bool AListInt::empty() const
{
	return size_ == 0;
}

void AListInt::insert(int pos, const int& val)
{
	if(pos < 0 || pos > size_){
    cerr << "Out of bounds of list" << endl;
    return;
  }

  if(pos == size_){
  	resize();
  	data_[pos] = val;
    size_ += 1;
  }
	else{
		resize();
		int temp = size_;
		while(temp > pos){
			data_[temp] = data_[temp-1];
			temp--;
		}
		data_[pos] = val;
    size_ += 1;
	}
}

void AListInt::remove(int pos)
{
	if(pos < 0 || pos >= size_){
    cerr << "Out of bounds of list" << endl;
    return;
  }

	if(pos == (size_ - 1)){
		data_[pos] = 0;
    size_ -= 1;
	}
  else{
  	int temp = pos;
    while((size_ - 1) > temp){
  		data_[temp] = data_[temp+1];
  		temp++;
  	}
    size_ -= 1;
  }
}

void AListInt::set(int position, const int& val)
{
	if(position < 0 || position >= size_){
    cerr << "Out of bounds of list" << endl;
    return;
  }
  data_[position] = val;
}

int& AListInt::get(int position)
{
	if(position < 0 || position >= size_){
    cerr << "Out of bounds of list" << endl;
  }
  return data_[position];
}

int const & AListInt::get(int position) const
{
	if(position < 0 || position >= size_){
    cerr << "Out of bounds of list" << endl;
  }
  return data_[position];
}

//Private declarations are here
void AListInt::resize()
{
	if(size_ == cap_){
		int newcap;
    newcap = cap_ * 2;
    int* newdata = new int[newcap];
    for(int i=0; i<size_; i++){
      newdata[i] = data_[i];
    }
    delete data_;
    data_ = newdata;
	}
	else{
		return;
	}
}

