#include "lib/setstr.h"
#include <iostream>
#include "gtest/gtest.h"

int main()
{
	SetStr *my_set = new SetStr();
	SetStr *set2 = new SetStr();
	SetStr testset;
	
	if(my_set->empty()){cout << "success" << endl;}

	my_set->insert("ant");
	my_set->insert("bat");
	my_set->insert("cat");
	my_set->insert("bat");
	if(my_set->size() == 3){cout << "success" << endl;}
	//my_set->remove("cat");
	//if(my_set->size() == 2){cout << "success" << endl;}
	if(my_set->exists("an")){cout << "s2" << endl;}

	set2->insert("ant");
	set2->insert("bat");
	set2->insert("rat");

	testset = *my_set | *set2;
	for(int i=0; i<testset.size(); i++){
		cout << *testset.next() << endl;
	}



	/*TEST_F(SetTest, EmptyNominal){
		EXPECT_EQ(0, my_set->size());
	}

	my_set->insert("ant");
	my_set->insert("bat");
	my_set->insert("cat");

	TEST_F(SetTest, AddNominal){
		EXPECT_EQ(3, my_set->size());
		my_set->insert("cat");
		EXPECT_EQ(3, my_set->size());
	}*/
	delete my_set;
	delete set2;
}
