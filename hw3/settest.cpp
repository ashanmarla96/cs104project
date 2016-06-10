#include "lib/setstr.h"
#include <iostream>
#include "gtest/gtest.h"

int main()
{
	SetStr *my_set = new SetStr();
	TEST_F(SetTest, EmptyNominal){
		EXPECT_EQ(0, my_set->size());
	}

	my_set->insert("ant");
	my_set->insert("bat");
	my_set->insert("cat");

	TEST_F(SetTest, AddNominal){
		EXPECT_EQ(3, my_set->size());
		my_set->insert("cat");
		EXPECT_EQ(3, my_set->size());
	}
	delete my_set;
}
