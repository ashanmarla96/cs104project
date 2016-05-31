#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

struct Item{
	int val;
	Item* next;
};

void append(Item*& head, int value){
	Item* newNode = new Item;
	newNode->val = value;
	newNode->next = NULL;

	if(head == NULL){
		head = newNode;
	}
	else{
		Item* temp = head;
		while(temp->next){
			temp = temp->next;
		}
		temp->next = newNode;
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
	vector<int> nums;
	while(infile >> num){
		nums.push_back(num);
		if(infile.get('/n')){
			break;
		}
	}
	

	for (int i = 0; i < nums.size(); ++i)
	{
		cout << nums[i] << endl;
	}


}

int main(int argc, char* argv[]){
	if(argc < 2){
   		cerr << "Usage ./remdup input_file output_file" << endl;
  	}

  	Item* head1 = NULL;
  	Item* head2 = NULL;

  	readLists(argv[1], head1, head2);
}