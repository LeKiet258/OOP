#pragma once
#include"ClasslessFunctions.h"

class Rectangle {
private:
	Point _topLeft;
	Point _rightBottom;

	vector<wstring> _corners = { L"╔", L"╗", L"╝", L"╚" }; //clockwise
	wstring _row = L"═";
	wstring _wall = L"║";
public:
	Rectangle(Point tl = { 0,0 }, Point rb = { 0,0 }) :_topLeft(tl), _rightBottom(rb) {}

	Point topLeft() { return _topLeft; }
	Point rightBottom() { return _rightBottom; }

	void draw() {
		_setmode(_fileno(stdout), _O_WTEXT); //needed for output

		//draw upper row
		gotoXY(_topLeft.x(), _topLeft.y());
		wcout << _corners[0];

		for (int i = _topLeft.x() + 1; i < _rightBottom.x(); ++i) {
			gotoXY(i, _topLeft.y());
			wcout << _row;
		}
		gotoXY(_rightBottom.x(), _topLeft.y());
		wcout << _corners[1];

		//draw walls
		////left wall
		for (int i = _topLeft.y() + 1; i < _rightBottom.y(); ++i) {
			gotoXY(_topLeft.x(), i);
			wcout << _wall;
		}
		gotoXY(_topLeft.x(), _rightBottom.y());
		wcout << _corners[3];

		////right wall
		for (int i = _topLeft.y() + 1; i < _rightBottom.y(); ++i) {
			gotoXY(_rightBottom.x(), i);
			wcout << _wall;
		}
		gotoXY(_rightBottom.x(), _rightBottom.y());
		wcout << _corners[2];

		//draw lower row
		for (int i = _topLeft.x() + 1; i < _rightBottom.x(); ++i) {
			gotoXY(i, _rightBottom.y());
			wcout << _row;
		}
	}

	void draw(vector<wstring> corners, wstring row, wstring wall) {
		//draw upper row
		gotoXY(_topLeft.x(), _topLeft.y());
		wcout << corners[0];

		for (int i = _topLeft.x() + 1; i < _rightBottom.x(); ++i) {
			gotoXY(i, _topLeft.y());
			wcout << row;
		}
		gotoXY(_rightBottom.x(), _topLeft.y());
		wcout << corners[1];

		//draw walls
		////left wall
		for (int i = _topLeft.y() + 1; i < _rightBottom.y(); ++i) {
			gotoXY(_topLeft.x(), i);
			wcout << wall;
		}
		gotoXY(_topLeft.x(), _rightBottom.y());
		wcout << corners[3];

		////right wall
		for (int i = _topLeft.y() + 1; i < _rightBottom.y(); ++i) {
			gotoXY(_rightBottom.x(), i);
			wcout << wall;
		}
		gotoXY(_rightBottom.x(), _rightBottom.y());
		wcout << corners[2];

		//draw lower row
		for (int i = _topLeft.x() + 1; i < _rightBottom.x(); ++i) {
			gotoXY(i, _rightBottom.y());
			wcout << row;
		}
	}
};