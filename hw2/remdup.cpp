#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

struct Item{
	int val;
	Item* next;
};

void print(Item*& head){
	//ofstream outfile(ofile);
	//vector<int> nums;
	if(head->next == NULL){
		return;
	}  
	else{
		cout << head->val << endl;
		//nums.push_back(head->val);
   		print(head->next);
  	}
}

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
	//cout<<txtline<<endl;
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
		}
	}

	string txtline2;
	getline(infile, txtline2);
	stringstream ss2(txtline2);
	while(ss2 >> num){
		Item* newNode = new Item;
		newNode->val = num;
		newNode->next = NULL;

		if(headB == NULL){
			headB = newNode;
			temp = headB;
		}
		else{
			temp->next = newNode;
			temp = temp->next;
		}
	}

}



void concatenatehelper(Item* headA, Item* headB, Item* headC){
	//cout << "TEST0" << endl;
	Item* newNode = new Item;
	if(headB == NULL){
		headC->next = NULL;
		return;
	}
	else if(headA == NULL){
		//Item* newNode = new Item;
		newNode->val = headB->val;
		headC->val = newNode->val;
		concatenatehelper(headA, headB->next, headC->next);
	}
	else{
		//Item* newNode = new Item;
		newNode->val = headA->val;
		headC->val = newNode->val;
		concatenatehelper(headA->next, headB, headC->next);
	}
}

Item* concatenate(Item* headA, Item* headB){
	Item* headC = new Item;
	//headC->val = 0; headC->next = NULL;
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
	if(argc < 3){
   		cerr << "Usage $(BIN_DIR)/remdup input_file output_file" << endl;
  	}

  	Item* head1 = NULL;
  	Item* head2 = NULL;
  	Item* head3 = NULL;

  	readLists(argv[1], head1, head2);

  	//vector<int> numlist;
  	removeDuplicates(head1);
  	head3 = concatenate(head1, head2);
  	print(head3);

  	//ofstream outfile(argv[2]);

  	Item* temp = head3;
  	while(temp->next != NULL){
  		cout << temp->val << " ";
  		temp = temp->next;
  	}
  	cout << endl;

  	

}