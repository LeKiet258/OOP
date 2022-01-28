#include<iostream>
#include<fstream>

#include"IEmployee.h"
#include"Random.h"
#include"EmployeeFactory.h"
#include"Tokenizer.h"

int main() {
	int n = Random::nextInt(5, 20);
	vector<shared_ptr<IEmployee>> employees;
	ofstream fout("output.txt");

	for (int i = 0; i < n; ++i) {
		int type = Random::nextInt(EmployeeFactory::instance()->totalEmployee());
		shared_ptr<IEmployee> employee = EmployeeFactory::instance()->create(type);

		employees.push_back(employee);
	}

	fout << n << endl;
	for (int i = 0; i < n; ++i) {
		fout << employees[i]->type() << ": " << employees[i]->toString() << endl;
	}

	fout.close();

	//reset variables
	n = 0;
	employees.clear();

	ifstream fin("output.txt");
	string s;

	getline(fin, s);
	n = stoi(s);

	for (int i = 0; i < n; ++i) {
		getline(fin, s);
		vector<string> tokens = Tokenizer::split(s, ": ");
		string type = tokens[0];
		shared_ptr<IEmployee> employee = EmployeeFactory::instance()->parse(type, tokens[1]);

		employees.push_back(employee);
	}

	for (int i = 0; i < n; ++i)
		cout << employees[i]->type() << ": " << employees[i]->salary() << endl;

	return 0;
}