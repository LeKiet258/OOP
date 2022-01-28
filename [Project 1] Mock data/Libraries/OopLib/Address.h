#pragma once
#include<iostream>
#include<string>
#include<sstream>

using namespace std;

class Address {
	friend wostream& operator<<(wostream&, Address&);
private:
	wstring _number;
	wstring _street;
	wstring _ward; 
	wstring _district; 
	wstring _city;
public:
	Address(wstring = L"?", wstring = L"?", wstring = L"?", wstring = L"?", wstring = L"?");

	void setNumber(wstring number) { _number = number; }
	void setStreet(wstring streetName) { _street = streetName; }
	void setWard(wstring ward) { _ward = ward; }
	void setDistrict(wstring district) { _district = district; }
	void setCity(wstring city) { _city = city; }

	wstring street() { return _street; }
	wstring ward() { return _ward; }
	wstring district() { return _district; }
	wstring city() { return _city; }
	wstring number() { return _number; }

	wstring toString();
	static Address parse(wstring line);
};