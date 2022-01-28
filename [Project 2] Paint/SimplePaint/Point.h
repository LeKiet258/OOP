#pragma once
#include<iostream>
#include<vector>
#include<string>
#include"Tokenizer.h"

using namespace std;

class Point {
	friend ostream& operator<<(ostream&, const Point&);
private:
	int _x, _y;
public:
	Point(int x = 0, int y = 0) : _x(x), _y(y) { }
	
	int x() { return _x; }
	void setX(int x) { _x = x; }
	int y() { return _y; }
	void setY(int y) { _y = y; }
	static double calcDistance(const Point& a, const Point& b);
	static Point parse(string buffer);
	string toString();

};

