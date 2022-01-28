#include "ManagerEmployee.h"
#include"Random.h"
#include"Tokenizer.h"
#include<vector>
#include<sstream>

shared_ptr<IEmployee> ManagerEmployee::nextEmployee() {
	shared_ptr<IEmployee> res = make_shared<ManagerEmployee>(Random::nextInt(1, 4));
	return res;
}

string ManagerEmployee::toString() {
	stringstream ss;
	ss << _factor << " " << _baseSalary;
	return ss.str();
}

shared_ptr<IEmployee> ManagerEmployee::parse(string s) {
	vector<string> tokens = Tokenizer::split(s, " ");
	int factor = stoi(tokens[0]);
	shared_ptr<IEmployee> res = make_shared<ManagerEmployee>(factor);

	return res;
}