#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "../lib/llistint.h"
#include "../lib/stackint.h"
using namespace std;

StackInt::StackInt()
{}

StackInt::~StackInt()
{
	list_.clear();
}

bool StackInt::empty() const
{
	return list_.empty();
}

void StackInt::push(const int& val)
{
	return list_.insert(list_.size(), val);
}

int const & StackInt::top() const
{
	return list_.get(list_.size() - 1);
}

void StackInt::pop()
{
	return list_.remove(list_.size() - 1);
}

