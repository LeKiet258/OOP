#pragma once
#include<memory>
#include<string>
using namespace std;

class IEmployee
{
public:
	virtual int salary() = 0;
	virtual shared_ptr<IEmployee> nextEmployee() = 0;

	//return info of each class (except class name)
	virtual string toString() = 0;

	virtual string type() = 0;
	virtual shared_ptr<IEmployee> parse(string) = 0;
};

