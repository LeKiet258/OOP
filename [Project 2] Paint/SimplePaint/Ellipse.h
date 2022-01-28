#pragma once
#include"Header.h"

const double PI = 3.14;

class Ellipse : public IShape
{
private:
	Point _topLeft;
	Point _rightBottom;
public:
	Ellipse(){}
	Ellipse(Point, Point);
	IShape_ptr create(Point, Point);

	virtual string type() { return "Ellipse"; }
	virtual string toString();
	static IShape_ptr parse(string);
	Point srcPoint() { return _topLeft; }
	Point dstPoint() { return _rightBottom; }

	virtual ~Ellipse() {};
};

