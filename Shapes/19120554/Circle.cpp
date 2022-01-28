#include "Circle.h"
#include"Square.h"
#include<sstream>

Circle::Circle(Point a, Point b) : _topLeft(a), _rightBottom(b)
{
	if (!Square::isSquare(a, b))
		throw exception("The 2 points provided can't form a square so they can't form a circle");
}

string Circle::toString() {
	stringstream ss;
	ss << _topLeft.toString() << " " << _rightBottom.toString();
	return ss.str();
}

IShape_ptr Circle::parse(string buffer) {
	vector<string> tokens = Tokenizer::split(buffer, " ");
	Point a = Point::parse(tokens[0]);
	Point b = Point::parse(tokens[1]);
	IShape_ptr res = make_shared<Circle>(a, b);

	return res;
}

double Circle::radius() {
	Point topRight(_rightBottom.x(), _topLeft.y());
	return Point::calcDistance(_rightBottom, topRight) / 2;
}

