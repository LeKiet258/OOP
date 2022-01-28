#pragma once
#include"IEmployee.h"

class ManagerEmployee : public IEmployee
{
private:
	int _factor;
	const int _baseSalary = 3000;
public:
	ManagerEmployee(){ }
	ManagerEmployee(int f) : _factor(f){}

	int salary() { return _factor * _baseSalary; }
	shared_ptr<IEmployee> nextEmployee() ;
	string toString();
	string type() { return "Manager Employee"; }
	shared_ptr<IEmployee> parse(string);
};

