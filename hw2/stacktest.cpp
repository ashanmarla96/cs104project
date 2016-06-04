#include "lib/stackint.h"
#include <iostream>

using namespace std;

int main() {
	StackInt* s = new StackInt();

	if(s->empty()){
		cout << "Success" << endl;
	}

	s->push(3);
	s->push(5);
	s->push(7);
	if(s->top() == 7){
		cout << "Success" << endl;
	}
	s->pop();
	if(s->top() == 3){
		cout << "Success" << endl;
	}





}