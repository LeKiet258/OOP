#pragma once
#include"Header.h"
#include"Point.h"

void clrscr();
void nocursortype();
void cursortype();
void gotoXY(int column, int line);
void clearRegion(Point topLeft, Point rightBottom);
int wherex();
int wherey();
void inputString(int, wstring&);
int longestStringLength(vector<wstring>);
wstring formattedPrice(unsigned long long);

template <class T>
void printVec(vector<T> v) {
	_setmode(_fileno(stdout), _O_WTEXT); //needed for output

	for (int i = 0; i < v.size(); ++i) {
		wcout << v[i] << endl;
	}
}


