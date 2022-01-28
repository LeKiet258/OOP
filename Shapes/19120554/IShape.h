#pragma once
#include<string>
#include<memory>

using namespace std;

class IShape
{
public:
	virtual string toString() = 0;
	virtual string type() = 0;

	virtual double area() = 0;
	virtual double perimeter() = 0;

	virtual ~IShape() {};

};

typedef shared_ptr<IShape> IShape_ptr;
