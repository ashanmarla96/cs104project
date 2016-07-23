#ifndef MERGESORT_H
#define MERGESORT_H
#include <vector>
using namespace std;

template<class T, class Comparator>
void merge(vector<T>& me, vector<T>& container, int start, int middle, int end, Comparator compare)
{
  int begin = start;
  int tempmid = middle+1;
  for (int j = start; j <= end; ++j){
    if (begin <= middle){
      if(tempmid > end || compare(me[begin], me[tempmid])){
        container[j] = me[begin];
        ++begin;
      }
    }
    else{
      container[j] = me[tempmid];
      ++tempmid;
    }
  }

  for (int j = start; j <= end; ++j){
    me[j] = container[j];
  }
    
}

template<class T, class Comparator>
void mergeSortHelper(vector<T>& me, vector<T>& container, int start, int end, Comparator compare)
{
  if (start < end){
    int middle = (start+end)/2;
    mergeSortHelper(me, container, start, middle, compare);
    mergeSortHelper(me, container, middle+1, end, compare);
    merge(me, container, start, middle, end, compare);
  }
}

template <class T, class Comparator>
void mergeSort(vector<T>& me, Comparator compare)
{
  vector<T> container;
  container = me;
  mergeSortHelper(me, container, 0, (me.size()-1), compare);
}
#endif