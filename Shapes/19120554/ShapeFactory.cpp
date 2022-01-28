#include "ShapeFactory.h"
#include"Point.h"
#include"Random.h"
#include"Circle.h"
#include"Rectangle.h"
#include"Line.h"
#include"Square.h"

IShape_ptr ShapeFactory::create(int type) {
	Random rng;
	IShape_ptr obj = 0;
	Point p1(rng.nextInt(100), rng.nextInt(100));
	Point p2(rng.nextInt(100), rng.nextInt(100));

	switch (type)
	{
	case circle:
		while (!Square::isSquare(p1, p2)) {
			p1 = Point(rng.nextInt(100), rng.nextInt(100));
			p2 = Point(rng.nextInt(100), rng.nextInt(100));
		}
		obj = make_shared<Circle>(p1, p2);

		break;
	case rectangle:
		obj = make_shared<Rectangle>(p1, p2);
		break;
	case line:
		obj = make_shared<Line>(p1, p2);
		break;
	}

	return obj;
}

IShape_ptr ShapeFactory::parse(string type, string value) {
	IShape_ptr shape = 0;

	if (type == "Rectangle")
		shape = Rectangle::parse(value);
	else if (type == "Line")
		shape = Line::parse(value);
	else if (type == "Circle")
		shape = Circle::parse(value);

	return shape;
}