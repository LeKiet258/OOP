#include"Draw.h"
#include"Rectangle.h"

void Draw::drawFrameTitle(wstring title) {
	int xStart = (consoleWidth - (4 + title.length())) / 2 + 1;
	int xEnd = xStart + title.length() + 3;
	_frameTitle[0].setX(xStart);
	_frameTitle[1].setX(xEnd);
	class Rectangle rec(_frameTitle[0], _frameTitle[1]);
	rec.draw();
	gotoXY(_frameTitle[0].x() + 2, _frameTitle[0].y() + 1);
	std::wcout << title;
}

void Draw::drawFrameEdit(wstring editLine) {
	int x = (consoleWidth - (editLine.length() + _frameEdit[1].x() - _frameEdit[0].x())) / 2 + 1;
	gotoXY(x, _frameEdit[0].y() + 1);
	std::wcout << editLine;
	x = wherex();
	int y = wherey();
	class Rectangle rec(Point(x + 1, y - 1), Point(x + 40, y + 1));
	rec.draw({ L"┌", L"┐", L"┘", L"└" }, L"─", L"│");
	gotoXY(x + 2, y); //input from this point
}

void Draw::drawFrameEdit(wstring editLine, Point src, Point dst) {
	gotoXY(src.x(), src.y() + 1);
	std::wcout << editLine;
	int x = wherex();
	int y = wherey();
	class Rectangle rec(Point(x + 1, y - 1), dst);
	rec.draw({ L"┌", L"┐", L"┘", L"└" }, L"─", L"│");
	gotoXY(x + 2, y); //input from this point
}

void Draw::clearFrameEdit(wstring editLine) {
	int x = (consoleWidth - (editLine.length() + _frameEdit[1].x() - _frameEdit[0].x())) / 2 + 1;
	clearRegion(Point(x, _frameEdit[0].y()), Point(_frameEdit[1].x() + 30, _frameEdit[1].y()));
}

void Draw::clearFrameTitle(){
	clearRegion(_frameTitle[0], _frameTitle[1]);
}