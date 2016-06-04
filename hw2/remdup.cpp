#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

struct Item{
	int val;
	Item* next;
};

void readLists(char* filename, Item*& headA, Item*& headB){
	ifstream infile(filename);
	if(infile.fail()){
		cerr << "Error opening input file" << endl;
		return;
	}

	
	
	string txtline;
	int num;
	getline(infile, txtline);
	stringstream ss(txtline);
	cout<<txtline<<endl;
	Item* temp;
	while(ss >> num){
		Item* newNode = new Item;
		newNode->val = num;
		newNode->next = NULL;
		if(headA == NULL){
			headA = newNode;
			temp = headA;
		}
		else{
			temp->next = newNode;
			temp = temp->next;
			//temp = newNode;
		}
		
	}
	
	/*Item* temp2 = headA;
	while(temp2 != NULL){
		cout << temp2->val << endl;
		temp2 = temp2->next;
	}*/
}



void concatenatehelper(Item* headA, Item* headB, Item* headC){
	if(headA == NULL){
		Item* newNode = new Item;
		headC->next = newNode;
		newNode = headB;
		concatenatehelper(headA, headB->next, headC);
	}
	if(headB == NULL){
		return;
	}
	else{
		headC->next = headA;
		concatenatehelper(headA->next, headB, headC);
	}
}

Item* concatenate(Item* headA, Item* headB){
	Item* headC = new Item;
	concatenatehelper(headA, headB, headC);
	return headC;
}

void removehelper(Item*& head){
	if(head->next == NULL){
		return;
	}
	else{
		if(head->val == head->next->val){
			head->next = head->next->next;
			removehelper(head);
		}
		else{
			removehelper(head->next);
		}
	}
}

void removeDuplicates(Item*& head){
	removehelper(head);
}





int main(int argc, char* argv[]){
	if(argc < 2){
   		cerr << "Usage ./remdup input_file output_file" << endl;
  	}

  	Item* head1 = NULL;
  	Item* head2 = NULL;
  	Item* head3;

  	readLists(argv[1], head1, head2);

  	removeDuplicates(head1);
  	//head3 = concatenate(head1, head2);
  	Item* temp2 = head1;
	while(temp2 != NULL){
		cout << temp2->val << endl;
		temp2 = temp2->next;
	}
}