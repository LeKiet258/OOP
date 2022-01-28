#pragma once
#include<iostream>
#include<ctime>

using namespace std;

class Random {
private:
	static bool _seeded;
public:
	void setSeed(bool s) { _seeded = s; }
	int nextInt();
	int nextInt(int);
	int nextInt(int, int);
	
	//Random() { wcout << seed() << endl; }
	//wstring seed() { return (_seeded ? L"yes" : L"no"); }
};