#pragma once
#include "IShape.h"

class ShapeFactory
{
public:
	enum Shape { circle, rectangle, line };
	inline static int totalShapes = 3;

	static IShape_ptr create(int type);
	static IShape_ptr parse(string type, string value);
};

