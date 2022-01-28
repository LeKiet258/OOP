#pragma once
//#include"Header.h"
#include"Point.h"

class IShape
{
protected:
	int _color;
public:
	virtual string toString() = 0;
	virtual string type() = 0;
	virtual shared_ptr<IShape> create(Point, Point) = 0;

	//lưu tọa độ 2 điểm topLeft & rightBottom
	virtual Point srcPoint() = 0;
	virtual Point dstPoint() = 0;

	void setRGB(int color) { _color = color; }
	int color() { return _color; }

	virtual ~IShape() {};

};

typedef shared_ptr<IShape> IShape_ptr;
