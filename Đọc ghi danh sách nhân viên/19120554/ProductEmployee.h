#pragma once
#include"IEmployee.h"
#include<string>

class ProductEmployee : public IEmployee
{
private:
	int _totalProduct;
	int _unitPrice;
public:
	ProductEmployee(){}
	ProductEmployee(int count, int price):_totalProduct(count), _unitPrice(price){}

	string toString();
	string type() { return "Product Employee"; }
	int salary() { return _totalProduct * _unitPrice; }
	shared_ptr<IEmployee> nextEmployee();
	shared_ptr<IEmployee> parse(string);
};

