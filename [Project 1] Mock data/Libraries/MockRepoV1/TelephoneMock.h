#pragma once
#include<Random.h>
#include<Telephone.h>
#include<MobileNetwork.h>

class TelephoneMock {
private:
	Random _rng;
	vector<MobileNetwork> _supportedNetworks;
public:
	TelephoneMock();

	Telephone next();
};