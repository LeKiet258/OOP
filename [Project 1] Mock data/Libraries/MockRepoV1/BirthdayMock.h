#pragma once
#include<Random.h>
#include<DateTime.h>

class BirthdayMock {
private:
	Random _rng;
	int _maxAge;
	int _currentYear;
public:
	BirthdayMock();

	DateTime next();
};