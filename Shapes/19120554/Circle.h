#pragma once
#include"Point.h"
#include"IShape.h"

const int PI = 3.14;

class Circle : public IShape
{
private:
	Point _topLeft;
	Point _rightBottom;
public:
	Circle(){}
	Circle(Point, Point);

	virtual string type() { return "Circle"; }
	virtual string toString();
	static IShape_ptr parse(string);
	double radius();
	double area(){ return PI * radius() * radius(); }
	double perimeter(){ return 2 * PI * radius(); }

	virtual ~Circle() {};
};

