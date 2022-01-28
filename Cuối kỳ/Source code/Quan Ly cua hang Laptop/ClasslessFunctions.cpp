#include"ClasslessFunctions.h"

void clrscr()
{
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home = { 0,0 };
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}

void nocursortype()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void cursortype() {
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = TRUE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void gotoXY(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int wherex() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.X;
}

int wherey() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.Y;
}

void clearRegion(Point topLeft, Point rightBottom) {
	for (int i = topLeft.y(); i <= rightBottom.y(); ++i) {
		for (int j = topLeft.x(); j <= rightBottom.x(); ++j) {
			gotoXY(j, i);
			wcout << L" ";
		}
	}
}

void inputString(int wordsLimit, wstring& s) {
	wchar_t c;
	int wordCount = 0;
	int x = 0, y = 0;

	while (1) {
		c = _getch();
		x = wherex();
		y = wherey();

		if (wordCount < wordsLimit) {
			if (c != ENTER && c != ESC && c != BACKSPACE) {
				s.push_back(c);
				wcout << c;
				wordCount++;
			}
		}
		if (c == BACKSPACE && s.length() > 0) {
			--wordCount;
			s.pop_back();
			gotoXY(x - 1, y);
			wcout << L" ";
			gotoXY(x - 1, y);
		}
		if (c == ENTER)
			break;
	}
}

int longestStringLength(vector<wstring> v) {
	int max = 0;

	for (wstring line : v)
		if (max < line.length())
			max = line.length();
	return max;
}

wstring formattedPrice(unsigned long long price) {
	if (price == 0)
		return L"";
	wstring s = to_wstring(price);
	wstring res;
	int idx = s.length() - 1;

	while (idx >= 0) {
		res.insert(res.begin(), s[idx]);

		if((s.length() - idx) % 3 == 0 && idx != 0)
			res.insert(res.begin(), L'.');
		idx--;
	}
	return res;
}
