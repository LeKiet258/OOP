#include "EmployeeFactory.h"
#include"ProductEmployee.h"
#include"DailyEmployee.h"
#include"ManagerEmployee.h"

EmployeeFactory::EmployeeFactory() {
	_prototypes.push_back(make_shared<DailyEmployee>());
	_prototypes.push_back(make_shared<ProductEmployee>());
	_prototypes.push_back(make_shared<ManagerEmployee>());
}

shared_ptr<IEmployee> EmployeeFactory::create(int type) {
	shared_ptr<IEmployee> res = _prototypes[type]->nextEmployee();
	return res;
}

shared_ptr<IEmployee> EmployeeFactory::parse(string type, string info) {
	shared_ptr<IEmployee> employee = NULL;

	for (int i = 0; i < _prototypes.size(); ++i) {
		if (_prototypes[i]->type() == type) {
			employee = _prototypes[i]->parse(info);
			break;
		}
	}

	return employee;
}
