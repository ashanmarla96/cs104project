#include "lib/setstr.h"
#include <iostream>
#include "gtest/gtest.h"

class SetTest : public testing::Test
{
protected:	
	/*if(my_set->empty()){cout << "success" << endl;}

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
	}*/


	SetTest( ) { 
       // initialization code here
   } 
 
   void SetUp( ) { 
       // code here will execute just before the test ensues 
   		my_set.insert("ant");
		my_set.insert("bat");
		my_set.insert("cat");

		set2.insert("ant");
		set2.insert("rat");
   }
 
   void TearDown( ) { 
       // code here will be called just after the test completes
       // ok to through exceptions from here if need be
   }
 
   ~SetTest( )  { 
       // cleanup any pending stuff, but no exceptions allowed
   		/*delete my_set;
		delete set2;*/
   }
   SetStr my_set;
	SetStr set2;
	SetStr testset;
	
};
	
TEST_F(SetTest, AddNominal){
	EXPECT_EQ(3, my_set.size());
	my_set.insert("dat");
	EXPECT_EQ(4, my_set.size());
}

TEST_F(SetTest, AddOffNominal){
	EXPECT_EQ(3, my_set.size());
	my_set.insert("cat");
	EXPECT_EQ(3, my_set.size());
}

TEST_F(SetTest, RemoveNominal){
	EXPECT_EQ(3, my_set.size());
	my_set.remove("cat");
	EXPECT_EQ(2, my_set.size());
}

TEST_F(SetTest, RemoveOffNominal){
	EXPECT_EQ(3, my_set.size());
	my_set.remove("rat");
	EXPECT_EQ(3, my_set.size());
}

TEST_F(SetTest, ExistsNominal){
	EXPECT_TRUE(my_set.exists("cat"));
}

TEST_F(SetTest, ExistsOffNominal){
	EXPECT_FALSE(my_set.exists("fat"));
}

TEST_F(SetTest, UnionNominal){
	testset = set2 & my_set;
	EXPECT_EQ(4, testset.size());
}


TEST_F(SetTest, IntersectNominal){
	testset = set2 | my_set;
	EXPECT_EQ(1, testset.size());
}




	

