#include "lib/alistint.h"
#include <iostream>

using namespace std;

int main() {
  AListInt * list = new AListInt(5);

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

  list->insert(1,8);
  list->insert(1,7);
  list->set(1, 9);
  //list->remove(1);
  list->insert(1,4);
  list->insert(-1,6);
  list->insert(3, 323);
  cout << endl;
    for(int i=0; i<list->size(); i++){
      cout << list->get(i) << endl;
  }
  

  // Clean up memory.
  delete list;
}
