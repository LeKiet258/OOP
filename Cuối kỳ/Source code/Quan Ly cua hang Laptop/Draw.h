#pragma once
#include"Header.h"
#include"Point.h"

class Draw {
protected:
	vector<Point> _frameTitle;
	vector<Point> _frameInstruction;
	vector<Point> _frameEdit;
	int _indent;
	wstring _bullet;
public:
	Draw() {
		_indent = 2;
		_bullet = L">>";

		int x = (consoleWidth - 12) / 2 + 1;
		int y = 1;
		_frameTitle = { Point(x, y), Point(x + 11, y + 2) }; 
		
		x = (consoleWidth - 36) / 2 + 1;
		_frameInstruction = { Point(x, y + 3), Point(x + 35, y + 9) };

		x = (consoleWidth - 40) / 2 + 1;
		_frameEdit = { Point(x, y + 12), Point(x + 39, y + 14) };
	}

	void drawFrameTitle(wstring title);
	void drawFrameEdit(wstring);
	void drawFrameEdit(wstring editLine, Point src, Point dst);

	void clearFrameEdit(wstring);
	void clearFrameTitle();
};