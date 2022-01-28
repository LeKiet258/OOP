#pragma once
#include"Point.h"
#include"IShape.h"

class Rectangle : public IShape
{
private:
	Point _topLeft;
	Point _rightBottom;
public:
	Rectangle(){}
	Rectangle(Point, Point);

	virtual string toString();
	virtual string type() { return "Rectangle"; }
	static IShape_ptr parse(string);

	double width();
	double height();
	double area() { return width() * height(); }
	double perimeter() { return 2 * (width() + height()); }

	virtual ~Rectangle() {};
};

