#pragma once
#include<Random.h>
#include<Utils.h>
#include"FullNameMock.h"

class EmailMock {
private:
	Random _rng;
	vector<wstring> _domains;
	FullNameMock _nameStore;
public:
	EmailMock();

	wstring next();
	wstring next(FullName);
};