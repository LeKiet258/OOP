#pragma once
#include<Address.h>
#include<Random.h>
#include<map>
#include<vector>

using namespace std;

typedef map<wstring, vector<wstring>> map_ws_vecWs;

class HcmAddressMock {
private:
	Random _rng;
	map_ws_vecWs _streets; //<district, streets_of_each_district> -> filter streets based on districts 
	map_ws_vecWs _wards;
	vector<wstring> _districts;
	vector<wstring> _cities;
public:
	HcmAddressMock();

	Address next();
};