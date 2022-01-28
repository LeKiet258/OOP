#include "Line.h"
#include<sstream>

IShape_ptr Line::parse(string buffer) {
	vector<string> tokens = Tokenizer::split(buffer, " ");
	Point a = Point::parse(tokens[0]);
	Point b = Point::parse(tokens[1]);
	IShape_ptr res = make_shared<Line>(a, b);
	res->setRGB(stoi(tokens[2]));

	return res;
}

string Line::toString() {
	stringstream ss;
	ss << _start.toString() << " " << _end.toString();
	return ss.str();
}

IShape_ptr Line::create(Point a, Point b) {
	IShape_ptr res = make_shared<Line>(a, b);
	return res;
}
