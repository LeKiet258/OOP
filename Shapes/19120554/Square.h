#pragma once
#include"IShape.h"
#include"Point.h"

class Square : public IShape
{
private:
	Point _topLeft;
	Point _rightBottom;
public:
	Square() {}
	Square(Point a, Point b);

	static bool isSquare(Point, Point);

	virtual string type() { return "Square"; }
	virtual string toString();
	static IShape_ptr parse(string);

	double edge();
	double area(){ return edge() * edge(); }
	double perimeter() { return edge() * 4; }

	virtual ~Square() {};

};

