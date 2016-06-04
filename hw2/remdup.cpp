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

void print(Item*& head, char* filename){
	int val;
	ofstream outfile(filename);
	//vector<int> nums;


	while(head != NULL){
		val = head->val;
		outfile << val << " ";
		//cout << head->val << " ";
		head = head->next;
	}
  	//cout << endl;
  	outfile << endl;
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
		//delete newNode;
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

void copy(Item* head, Item* copyto){
	if(head == NULL){
		return;
	}
	else{
		Item* newNode = new Item;
		newNode->val = head->val; newNode->next = NULL;
		copyto->next = newNode;
		copy(head->next, newNode);
	}

}


void concatenatehelper(Item* headA, Item* headB, Item* headC){
	//cout << "TEST0" << endl;
	//Item* newNode = new Item;
	if(headB == NULL){
		return;
	}
	else if(headA != NULL){
		Item* newNode = new Item;
		newNode->val = headA->val; newNode->next = NULL;
		headC->next = newNode;
		concatenatehelper(headA->next, headB, newNode);
	}
	else /*if(headB != NULL)*/{
		Item* newNode = new Item;
		newNode->val = headB->val; newNode->next = NULL;
		headC->next = newNode;
		concatenatehelper(headA, headB->next, newNode);
	}
	
}

Item* concatenate(Item* headA, Item* headB){
	Item* headC = new Item;
	

	if(headA == NULL || headB == NULL){
		if(headA == NULL){
			headC->val = headB->val; headC->next = NULL;
			copy(headB->next, headC);
			return headC;
		}
		else if(headB == NULL){
			headC->val = headA->val; headC->next = NULL;
			copy(headA->next, headC);
			return headC;
		}
		else if(headA == NULL && headB == NULL){
			headC->val = 0; headC->next = NULL;
			return headC;
		}

	}
	
	headC->val = headA->val; headC->next = NULL;
	concatenatehelper(headA->next, headB, headC);
	return headC;
}

void removehelper(Item*& head){
	Item* temp;
	temp = head;
	if(head == NULL){
		return;
	}

	if(temp->next->next == NULL){
		if(temp->val == temp->next->val){
			temp->next = NULL;
			return;
		}
		return;
	}

	if(temp->val == temp->next->val){
		temp->next = temp->next->next;
		removehelper(temp);
	}
	
	removehelper(temp->next);
	
	
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
  	
  	
  	removeDuplicates(head1);
  	head3 = concatenate(head1, head2);
  	print(head3, argv[2]);

  	

  	/*Item* temp = head3;
  	cout << head3->val << endl;
  	while(temp != NULL){
  		cout << temp->val << " ";
  		temp = temp->next;
  	}
  	cout << endl;*/

  	

}