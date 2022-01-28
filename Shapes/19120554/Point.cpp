#include "Point.h"
#include<sstream>

double Point::calcDistance(const Point& a, const Point& b) {
	int dx = a._x - b._x;
	int dy = a._y - b._y;
	double res = sqrt(dx * dx + dy * dy);
	return res;
}

Point Point::parse(string buffer) {
	vector<string> tokens = Tokenizer::split(buffer, ",");
	int x = stoi(tokens[0]);
	int y = stoi(tokens[1]);
	Point res(x, y);

	return res;
}

string Point::toString() {
	stringstream ss;
	ss << _x << "," << _y;
	return ss.str();
}

ostream& operator<<(ostream& out, const Point& p) {
	out << p._x << " " << p._y;
	return out;
}