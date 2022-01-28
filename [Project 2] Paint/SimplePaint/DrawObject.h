#pragma once
#include"IShape.h"
#include<vector>

class DrawObject
{
private:
	int _object;
	vector<IShape_ptr> _shapes; 
	vector<IShape_ptr> _undoShapes;
public:
	DrawObject(){
		//_undoShapes = 0;
	}
	//getters/setters
	void setObject(int a) { _object = a; }
	int object() { return _object; }
	void setShapes(vector<IShape_ptr> shapes) { _shapes = shapes; }
	vector<IShape_ptr> shapes() { return _shapes; }
	vector<IShape_ptr> undoShapes() { return _undoShapes; }
	void setUndoShapes(vector<IShape_ptr> obj) { _undoShapes = obj; }

	void addShape(shared_ptr<IShape> shape){ _shapes.push_back(shape); }
	void clear() { _shapes.clear(); }
	void addUndoShape(IShape_ptr obj) { _undoShapes.push_back(obj); }
};

