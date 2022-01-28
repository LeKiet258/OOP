#include "DailyEmployee.h"
#include"Tokenizer.h"
#include<vector>
#include<sstream>

shared_ptr<IEmployee> DailyEmployee::nextEmployee() {
	shared_ptr<IEmployee> res = make_shared<DailyEmployee>(Random::nextInt(100));
	return res;
}

string DailyEmployee::toString() {
	stringstream ss;
	ss << _dailyPayment << " " << _totalDays;
	return ss.str();
}

shared_ptr<IEmployee> DailyEmployee::parse(string info) {
	vector<string> tokens = Tokenizer::split(info, " ");
	int dailyPayment = stoi(tokens[0]);
	shared_ptr<IEmployee> res = make_shared<DailyEmployee>(dailyPayment);

	return res;
}