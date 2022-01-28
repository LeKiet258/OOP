#pragma once
#include"IEmployee.h"
#include"Random.h"

class DailyEmployee:public IEmployee
{
private:
	int _dailyPayment;
public:
	const int _totalDays = 28;

	DailyEmployee(int payment = 0) : _dailyPayment(payment){ }

	int salary() { return _dailyPayment * _totalDays; }
	shared_ptr<IEmployee> nextEmployee();
	string toString();
	string type() { return "Daily Employee"; }
	shared_ptr<IEmployee> parse(string);
};

