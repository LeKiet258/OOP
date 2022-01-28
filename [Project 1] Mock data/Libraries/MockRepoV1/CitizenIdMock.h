#pragma once
#include<DateTime.h>
#include<Random.h>
#include<fstream>
#include<sstream>

class CitizenIdMock {
private:
	Random _rng;
	vector<wstring> _cityCodes;
	int _maxAge;
	int _currentYear;
public:
	CitizenIdMock();

	wstring next();
	int getCentury();
};