#include "Ellipse.h"
#include<sstream>

Ellipse::Ellipse(Point a, Point b) : _topLeft(a), _rightBottom(b)
{
}

string Ellipse::toString() {
	stringstream ss;
	ss << _topLeft.toString() << " " << _rightBottom.toString();
	return ss.str();
}

IShape_ptr Ellipse::parse(string buffer) {
	vector<string> tokens = Tokenizer::split(buffer, " ");
	Point a = Point::parse(tokens[0]);
	Point b = Point::parse(tokens[1]);
	IShape_ptr res = make_shared<Ellipse>(a, b);
	res->setRGB(stoi(tokens[2]));

	return res;
}

IShape_ptr Ellipse::create(Point a, Point b) {
	IShape_ptr res = make_shared<Ellipse>(a, b);
	return res;
}

