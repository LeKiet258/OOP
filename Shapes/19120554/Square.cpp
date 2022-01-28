#include "Square.h"
#include<sstream>

Square::Square(Point a, Point b) :_topLeft(a), _rightBottom(b) {
	if (!isSquare(a, b))
		throw exception("The 2 points provided can't form a square");
}

bool Square::isSquare(Point topLeft, Point rightBottom) {
	Point topRight(rightBottom.x(), topLeft.y());
	return Point::calcDistance(topLeft, topRight) == Point::calcDistance(topRight, rightBottom);
}

string Square::toString() {
	stringstream ss;
	ss << _topLeft.toString() << " " << _rightBottom.toString();
	return ss.str();
}

IShape_ptr Square::parse(string buffer) {
	vector<string> tokens = Tokenizer::split(buffer, " ");
	Point a = Point::parse(tokens[0]);
	Point b = Point::parse(tokens[1]);
	IShape_ptr res = make_shared<Square>(a, b);

	return res;
}

double Square::edge() {
	Point topRight(_rightBottom.x(), _topLeft.y());
	return Point::calcDistance(_rightBottom, topRight);
}

