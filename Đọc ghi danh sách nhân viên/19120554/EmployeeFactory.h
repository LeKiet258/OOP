#pragma once
#include"IEmployee.h"
#include<vector>

class EmployeeFactory
{
private:
	inline static EmployeeFactory* _instance = NULL;
	vector<shared_ptr<IEmployee>> _prototypes;

	EmployeeFactory();
public:
	static EmployeeFactory* instance() {
		if (_instance == NULL)
			_instance = new EmployeeFactory();
		return _instance;
	}

	int totalEmployee() { return _prototypes.size(); }

	shared_ptr<IEmployee> create(int type);
	shared_ptr<IEmployee> parse(string type, string info);
};

