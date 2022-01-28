#include "Rectangle.h"
#include<sstream>

Rectangle::Rectangle(Point a, Point b) : _topLeft(a), _rightBottom(b)
{
	
}

string Rectangle::toString() {
	stringstream ss;
	ss << _topLeft.toString() << " " << _rightBottom.toString();
	return ss.str();
}

IShape_ptr Rectangle::parse(string buffer) {
	vector<string> tokens = Tokenizer::split(buffer, " ");
	Point a = Point::parse(tokens[0]);
	Point b = Point::parse(tokens[1]);
	IShape_ptr res = make_shared<Rectangle>(a, b);

	return res;
}

double Rectangle::width() {
	Point topRight(_rightBottom.x(), _topLeft.y());
	return Point::calcDistance(_topLeft, topRight);
}

double Rectangle::height() {
	Point topRight(_rightBottom.x(), _topLeft.y());
	return Point::calcDistance(_rightBottom, topRight);
}