#pragma once
#include"Header.h"

class Line : public IShape {
private:
	Point _start;
	Point _end;
public:
	Line(){}
	Line(Point start, Point end) : _start(start), _end(end) {}
	IShape_ptr create(Point, Point);

	double length() { return Point::calcDistance(_start, _end); }
	static IShape_ptr parse(string buffer);

	virtual string toString();
	virtual string type() { return "Line"; }

	virtual double perimeter() { return 0.0; }
	virtual double area() { return 0.0; }

	Point srcPoint() { return _start; }
	Point dstPoint() { return _end; }

	virtual ~Line(){}
};
