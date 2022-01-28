#pragma once

class Point {
private:
	int _x, _y;
public:
	Point(int x = 0, int y = 0):_x(x),_y(y){}

	int x() { return _x; }
	int y() { return _y; }
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }
};