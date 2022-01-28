#pragma once
#include<iostream>
#include<string>
#include<vector>

using namespace std;

class MobileNetwork {
private:
	wstring _name;
	vector<wstring> _prefixes;
public:
	MobileNetwork();
	MobileNetwork(wstring, vector<wstring> );

	void setName(wstring nameVal) { _name = nameVal; };
	wstring name() { return _name; };
	void setPrefixes(vector<wstring> pref) { _prefixes = pref; }
	vector<wstring> prefixes() { return _prefixes; }
};