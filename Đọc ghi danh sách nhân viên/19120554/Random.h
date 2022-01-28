#pragma once
#include<iostream>
#include<ctime>

using namespace std;

class Random {
private:
	inline static bool _seeded = false;
	inline static Random* _instance = NULL;

	Random(){}
	int nextIntInternal();
	int nextIntInternal(int);
	int nextIntInternal(int, int);
public:
	static Random* instance();

	void setSeed(bool s) { _seeded = s; }
	static int nextInt();
	static int nextInt(int ceiling);
	static int nextInt(int a, int b);
};