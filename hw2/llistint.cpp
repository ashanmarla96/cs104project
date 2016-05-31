#include "llistint.h"
#include <cstdlib>
#include <stdexcept>
using namespace std;

LListInt::LListInt()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

LListInt::~LListInt()
{
  clear();
}

bool LListInt::empty() const
{
  return size_ == 0;
}

int LListInt::size() const
{
  return size_;
}

/**
 * Complete the following function
 */
void LListInt::insert(int loc, const int& val)
{
  if(loc < 0 || loc > size_){
    throw invalid_argument("bad location");
  }

  Item *temp = getNodeAt(loc);
  Item* newNode = new Item;
  newNode->val = val;
  newNode->next = NULL; newNode->prev = NULL;

  if(head_ == NULL){
    head_ = newNode;
  }

  if(loc == size_){
    newNode->prev = tail_;
    tail_->next = newNode;
    tail_ = newNode;
  }

  else if(loc == 0 && head_ != NULL){
    newNode->next = head_;
    head_->prev = newNode;
    head_ = newNode;
  }

  else{
    newNode->prev = temp->prev;
    temp->prev->next = newNode;

    newNode->next = temp;
    temp->prev = newNode;
  }
  

}

/**
 * Complete the following function
 */
void LListInt::remove(int loc)
{
  if(loc < 0 || loc >= size_){
    throw invalid_argument("bad location");
  }

  if(head_ == NULL){
    throw invalid_argument("empty list");
  }

  Item* temp = getNodeAt(loc);
  
  if(loc == size_-1){
    temp->prev->next = NULL;
    tail_ = temp->prev;
    temp->prev = NULL;
    delete temp;
  }

  else if(loc == 0 && head_ != NULL){
    temp->next->prev = NULL;
    head_ = temp->next;
    temp->next = NULL;
    delete temp;
  }

  else{
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;

    temp->prev = NULL;
    temp->next = NULL;
    delete temp;
  }

}

void LListInt::set(int loc, const int& val)
{
  if(loc < 0 || loc >= size_){
    throw invalid_argument("bad location");
  }
  Item *temp = getNodeAt(loc);
  temp->val = val;
}

int& LListInt::get(int loc)
{
  if(loc < 0 || loc >= size_){
    throw invalid_argument("bad location");
  }
  Item *temp = getNodeAt(loc);
  return temp->val;
}

int const & LListInt::get(int loc) const
{
  if(loc < 0 || loc >= size_){
    throw invalid_argument("bad location");
  }
  Item *temp = getNodeAt(loc);
  return temp->val;
}

void LListInt::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}


LListInt::Item* LListInt::getNodeAt(int loc) const
{
  Item *temp = head_;
  if(loc >= 0 && loc < size_){
    while(temp != NULL && loc > 0){
      temp = temp->next;
      loc--;
    }
    return temp;
  }
  else {
    //throw std::invalid_argument("bad location");
    return NULL;
  }
}
