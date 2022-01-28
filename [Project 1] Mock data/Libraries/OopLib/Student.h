#pragma once
#include"FullName.h"
#include"Telephone.h"
#include"Address.h"
#include"DateTime.h"

class Student {
	friend wostream& operator<<(wostream&, Student&);
private:
	wstring _studentId;
	FullName _fullName;
	wstring _citizenId;
	Telephone _telephone;
	wstring _email;
	Address _address;
	DateTime _birthday;
public:
	Student();
	Student(wstring, FullName, wstring, Telephone, wstring, Address, DateTime);

	wstring studentId() { return _studentId; }
	void setStudentId(wstring id) { _studentId = id; }
	FullName fullName() { return _fullName; }
	void setFullName(FullName fullName) { _fullName = fullName; }
	Telephone phone() { return _telephone; }
	void setPhone(Telephone phone) { _telephone = phone; }
	wstring email() { return _email; }
	void setEmail(wstring email) { _email = email; }
	Address address() { return _address; }
	void setAddress(Address addr) { _address = addr; }
	DateTime birthday() { return _birthday; }
	void setBirthday(DateTime bday) { _birthday = bday; }

	bool checkBirthMonth(int m) { return _birthday.month() == m; };
	bool checkMobileNetwork(wstring ispName) { return _telephone.network().name() == ispName; };
	bool checkDistrict(wstring dist) { return _address.district() == dist; };
	bool isUsingGmail() { return _email.find(L"gmail") != string::npos; }

	static int saveStudentsToFile(vector<Student> studentVec, string fname);
	static Student parse(vector<wstring> lines);
};