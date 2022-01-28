#include "ProductEmployee.h"
#include"Random.h"
#include"Tokenizer.h"
#include<sstream>
#include<vector>

string ProductEmployee::toString() {
	stringstream ss;
	ss << _totalProduct << " " << _unitPrice;
	return ss.str();
}

shared_ptr<IEmployee>  ProductEmployee::nextEmployee() {
	shared_ptr<IEmployee> res = make_shared<ProductEmployee>(
		Random::nextInt(50, 90), Random::nextInt(30, 50));
	return res;
}

shared_ptr<IEmployee> ProductEmployee::parse(string info) {
	vector<string> tokens = Tokenizer::split(info, " ");
	int totalProduct = stoi(tokens[0]);
	int unitPrice = stoi(tokens[1]);
	shared_ptr<IEmployee> res = make_shared<ProductEmployee>(totalProduct, unitPrice);

	return res;
}