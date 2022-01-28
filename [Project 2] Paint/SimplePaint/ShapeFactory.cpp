#include "ShapeFactory.h"
#include"Point.h"
#include"Rectangle.h"
#include"Line.h"
#include"Ellipse.h"

ShapeFactory::ShapeFactory() {
	_prototypes.push_back(make_shared<Line>());
	_prototypes.push_back(make_shared<Rectangle>());
	_prototypes.push_back(make_shared<Ellipse>());
}

ShapeFactory* ShapeFactory::instance() {
	if (_instance == NULL)
		_instance = new ShapeFactory();
	return _instance;
}

IShape_ptr ShapeFactory::create(int type, int fromX, int fromY, int toX , int toY ) {
	Point topLeft(fromX, fromY);
	Point rightBot(toX, toY);
	IShape_ptr obj = _prototypes[type]->create(topLeft, rightBot);

	return obj;
}

IShape_ptr ShapeFactory::parse(string type, string value) {
	IShape_ptr shape = 0;
	//value: x.from,x.to_y.from,y.to_color

	if (type == "Rectangle")
		shape = Rectangle::parse(value);
	else if (type == "Line")
		shape = Line::parse(value);
	else if (type == "Ellipse")
		shape = Ellipse::parse(value);

	return shape;
}

vector<IShape_ptr> ShapeFactory::readFile(ifstream& fin) {
	int n;
	string s;
	vector<IShape_ptr> shapes;

	getline(fin, s);
	n = stoi(s);

	for (int i = 0; i < n; ++i) {
		getline(fin, s);
		vector<string> tokens = Tokenizer::split(s, ": ");
		IShape_ptr shape = parse(tokens[0], tokens[1]);
		shapes.push_back(shape);
	}

	return shapes;
}
