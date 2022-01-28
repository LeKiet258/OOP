#pragma once
#include<iostream>
#include<algorithm>
#include<numeric>
#include"Random.h"

using namespace std;
typedef long long ll;

class Fraction {
	friend wostream& operator<<(wostream&, const Fraction&);
private:
	Random _rng;
	ll _num;
	ll _den;
public:
	Fraction(ll = 0, ll = 1);

	ll num() { return _num; }
	ll den() { return _den; }
	void setNum(ll num) { _num = num; }
	void setDen(ll);

	Fraction operator+(const Fraction&);
	Fraction& operator+=(const Fraction&);
};