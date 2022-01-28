#pragma once
#include "IShape.h"
#include"Tokenizer.h"
#include<string>
#include<fstream>

using namespace std;

class ShapeFactory
{
private:
	enum Shape { line, rectangle, ellipse };
	inline static ShapeFactory* _instance = NULL;
	vector<IShape_ptr> _prototypes;

	ShapeFactory();
public:
	static ShapeFactory* instance();

	int totalShapes() { return _prototypes.size(); }
	IShape_ptr create(int type, int fromX, int fromY, int toX = 0, int toY = 0);
	IShape_ptr parse(string type, string value);
	vector<IShape_ptr> readFile(ifstream& fin);
};

