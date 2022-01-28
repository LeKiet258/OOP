#pragma once
#include<iostream>
#include<string>
#include<sstream>

using namespace std;

class FullName {
	friend wostream& operator<<(wostream&, FullName&);
private:
	wstring _firstName;
	wstring _middleName;
	wstring _lastName;
public:
	FullName(wstring, wstring, wstring);

	void setFirstName(wstring f) { _firstName = f; };
	wstring firstName() { return _firstName; };
	void setMiddleName(wstring m) { _middleName = m; };
	wstring middleName() { return _middleName; };
	void setLastName(wstring l) { _lastName = l; };
	wstring lastName() { return _lastName; };
	wstring fullName() { return _lastName + L" " + _middleName + L" " + _firstName; };
	wstring toString();
};
