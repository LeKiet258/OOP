#pragma once
#include<iostream>
#include<ctime>

using namespace std;

class Random {
private:
	static bool _seeded;
public:
	int nextInt();
	int nextInt(int);
	int nextInt(int, int);
};