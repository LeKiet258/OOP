#pragma once
#include"Point.h"
#include"IShape.h"

class Line : public IShape {
private:
	Point _start;
	Point _end;
public:
	Line(Point start, Point end) : _start(start), _end(end) {}

	double length() { return Point::calcDistance(_start, _end); }
	static IShape_ptr parse(string buffer);

	virtual string toString();
	virtual string type() { return "Line"; }

	virtual double perimeter() { return 0.0; }
	virtual double area() { return 0.0; }

	virtual ~Line(){}
};
