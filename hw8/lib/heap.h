#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <functional>
#include <algorithm>
#include <stdexcept>
using namespace std;

template <typename T, typename PComp, typename KComp >
class Heap
{
 public:
   /// Constructs an m-ary heap for any m >= 2
  Heap(int m, PComp c = PComp(), KComp k = KComp());

  /// Destructor as needed
  ~Heap();

  /// Adds an item
  void push(const T& item);

  /// returns the element at the top of the heap 
  ///  max (if max-heap) or min (if min-heap)
  T const & top() const;

  /// Removes the top element
  void pop();

  /// returns true if the heap is empty
  bool empty() const;

  /// updates the key to a "better" priority
  void updated_key(const T& item, const T& new_val);
 private:
  /// Add whatever helper functions and data members you need below
  void swapUp(int posn);
  void swapDown(int posn);
  
  vector<T> _store;
  int _m;
  PComp _c;
  KComp _k;
};

template <typename T, typename PComp, typename KComp>
  Heap<T,PComp,KComp>::Heap(int m, PComp c, KComp k) : 
    _store(),
    _m(m),
    _c(c),
    _k(k)
{}

template <typename T, typename PComp, typename KComp>
Heap<T,PComp,KComp>::~Heap()
{}

/// child at p @ m*p + 1 to m*p + m
/// parent at (c-1)/m
template <typename T, typename PComp, typename KComp>
void Heap<T,PComp,KComp>::push(const T& item)
{
  _store.push_back(item);
  swapUp(_store.size() -1);
}

template <typename T, typename PComp, typename KComp>
void Heap<T,PComp,KComp>::updated_key(const T& item, const T& new_val)
{
  for(int i =0; i<_store.size(); ++i){
    if(_k(_store[i], item)){
      _store[i] = new_val;
    }
  }
  for (int i = 0; i < _store.size(); ++i){
    swapUp(i);
  }
}

template <typename T, typename PComp, typename KComp>
T const & Heap<T,PComp,KComp>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    throw std::logic_error("can't top an empty heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return _store[0];
}

/// Removes the top element
template <typename T, typename PComp, typename KComp>
void Heap<T,PComp,KComp>::pop()
{
  if(empty()){
    throw std::logic_error("can't pop an empty heap");
  }

  // complete the code here
  _store[0] = _store[size()-1];
  _store.pop_back();
  swapDown(0);
}
/// returns true if the heap is empty
template <typename T, typename PComp, typename KComp>
bool Heap<T,PComp,KComp>::empty() const
{
  return _store.empty();
}

template<typename T, typename PComp, typename KComp>
void Heap<T,PComp,KComp>::swapUp(int posn) 
{
  int parentNode;
  parentNode = (posn-1)/_m;

  while(posn>0 && _c(_store[posn], _store[parentNode])){
    swap(_store[posn], _store[parentNode]);
    posn = parentNode;
    parentNode = (posn-1)/_m;
  }
}

template<typename T, typename PComp, typename KComp>
void Heap<T,PComp,KComp>::swapDown(int posn)
{
  while ((_m*posn)+1 < _store.size()){
    
    int tempkid = (_m*posn)+1;
    for (int i = 1; i < _m; ++i){
      if ((_m*posn)+i >= _store.size()){
        break;
      }
      else if(_c(_store[(_m*posn)+i], _store[tempkid])){
        tempkid = (_m*posn)+i;
      }
    }

    if(_c(_store[tempkid], _store[posn])){
      swap(_store[tempkid], _store[posn]);
      posn = tempkid;
    }
    else{
      return;
    }
  }
}


#endif

