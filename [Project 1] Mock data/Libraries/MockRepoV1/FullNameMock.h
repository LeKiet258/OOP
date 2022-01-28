#pragma once
#include<Random.h>
#include<FullName.h>
#include<vector>

class FullNameMock {
private:
	Random _rng;
	vector<wstring> _lastNames;
	vector<wstring> _femaleMiddleNames;
	vector<wstring> _maleMiddleNames;
	vector<wstring> _femaleFirstNames;
	vector<wstring> _maleFirstNames;
public:
	FullNameMock();

	FullName next(bool = true);
};