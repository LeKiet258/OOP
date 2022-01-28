#pragma once
#include"MobileNetwork.h"

class Telephone {
	friend wostream& operator<<(wostream&, Telephone&);
private:
	MobileNetwork _network;
	wstring _prefix;
	wstring _numbers;
public:
	Telephone(MobileNetwork, wstring, wstring);

	MobileNetwork network() { return _network; };
	wstring numbers() { return _numbers; };
};