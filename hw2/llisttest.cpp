#include "lib/llistint.h"
#include <iostream>

using namespace std;

int main() {
  LListInt * list = new LListInt();

  // Check if the list is initially empty.
  if (list->empty()) {
    cout << "SUCCESS: List is empty initially." << endl;
  } else {
    cout << "FAIL: List is not empty initially when it should be." << endl;
  }

  // Insert an item at the head.
  list->insert(0, 3);

  // Check if the list is still empty.
  if (!list->empty()) {
    cout << "SUCCESS: List is not empty after one insertion." << endl;
  } else {
    cout << "FAIL: List is empty after one insertion." << endl;
  }

  if (list->size() == 1) {
    cout << "SUCCESS: List has size 1 after one insertion." << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after one insertion.";
    cout << endl;
  }

  // Check if the value is correct.
  if (list->get(0) == 3) {
    cout << "SUCCESS: 3 is at the 0th index of the list." << endl;
  } else {
    cout << "FAIL: 3 is not at the 0th index of the list, " << list->get(0);
    cout << " is instead." << endl;
  }

  list->insert(0,4);
  if(list->get(0) == 4){
    cout << "SUCCESS, " << list->size() << endl;
  }
  else{
    cout << "FAIL, " << list->get(0) << endl;
  }

  list->insert(2,8);
  list->insert(3,7);
  list->set(2, 9);
  
  list->remove(4);
  list->remove(3);
  list->remove(2);
  list->remove(0);
  //list->remove(0);


    if(list->size() != 0){
      for(int i=0; i<list->size(); i++){
        cout << list->get(i) << endl;
      }
    }
    else{cout << "empty list" << endl;};
  



  // Clean up memory.
  delete list;
}