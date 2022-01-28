#pragma once
#include"Header.h"

class FullName {
private:
	wstring _ho;
	wstring _tenDem;
	wstring _ten;
public:
	FullName(wstring ho = L"", wstring tenDem = L"", wstring ten = L"") : _ho(ho), _tenDem(tenDem), _ten(ten) {}


	wstring toString() {
		wstringstream wss;
		wss << _ho << L" " << _tenDem << L" " << _ten;
		return wss.str();
	}
};