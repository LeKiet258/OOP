#pragma once
#include"Header.h"

class Rectangle : public IShape
{
private:
	Point _topLeft;
	Point _rightBottom;
public:
	Rectangle(){}
	Rectangle(Point, Point);
	IShape_ptr create(Point, Point);

	virtual string toString();
	virtual string type() { return "Rectangle"; }
	static IShape_ptr parse(string);

	double width();
	double height();
	double area() { return width() * height(); }
	double perimeter() { return 2 * (width() + height()); }

	Point srcPoint() { return _topLeft; }
	Point dstPoint() { return _rightBottom; }

	virtual ~Rectangle() {};
};

