#include"DrawStats.h"
#include"Rectangle.h"

void DrawStats::resetVariables() {
	_menuChoice = 0;
	_page = 1;
}

void DrawStats::drawFrameMenu() {
	class Rectangle rec(_frameMenu[0], _frameMenu[1]);
	rec.draw();
	vector<wstring> menu = { L"Danh sách các mặt hàng sắp hết",
							L"Danh sách mặt hàng bán chạy trong tháng trước",
							L"Doanh thu, lợi nhuận theo theo tháng cụ thể" };
	for (int i = 0; i < menu.size(); ++i) {
		gotoXY(_frameMenu[0].x() + 2*_indent + 1, _frameMenu[0].y() + i + 1);
		std::wcout << menu[i];
	}
}

void DrawStats::drawFrameInstruction(int code) {
	vector<wstring> instructions;
	if (code == 0)
		instructions = { L"[Enter]: Chọn mục", L"[Esc]: Trở lại menu" };
	else if (code == 1)
		instructions = { L"[Enter]: Chọn xem chi tiết laptop", L"[Esc]: Trở lại", L"[A/D]: qua trang trái/phải" };
	else if (code == 2)
		instructions = { L"[Enter]: Chọn tháng", L"[Esc]: Trở lại", L"[A/D]: qua trang trái/phải" };
	else if (code == 3)
		instructions = { L"[Esc]: Trở lại" };

	int yEnd = _frameInstruction[0].y() + instructions.size() + 1;
	int xStart = (consoleWidth - (4 + longestStringLength(instructions))) / 2 + 1;
	int xEnd = xStart + longestStringLength(instructions) + 3;

	_frameInstruction[0].setX(xStart);
	_frameInstruction[1].setX(xEnd);
	_frameInstruction[1].setY(yEnd);
	class Rectangle rec(_frameInstruction[0], _frameInstruction[1]);
	rec.draw();

	for (int i = 0; i < instructions.size(); ++i) {
		gotoXY(_frameInstruction[0].x() + 2, _frameInstruction[0].y() + i + 1);
		std::wcout << instructions[i];
	}
}

void DrawStats::drawFrameLaptopNameTitle() {
	class Rectangle rec(_frameLaptopNameTitle[0], _frameLaptopNameTitle[1]);
	rec.draw();
	wstring title = L"Mặt hàng";
	int x = _frameLaptopNameTitle[0].x() + (_frameLaptopNameTitle[1].x() - _frameLaptopNameTitle[0].x() - title.length()) / 2;
	gotoXY(x, _frameLaptopNameTitle[0].y() + 1);
	std::wcout << title;
}

void DrawStats::drawFrameNumberTitle(wstring title) {
	class Rectangle rec(_frameNumberSoldTitle[0], _frameNumberSoldTitle[1]);
	rec.draw();
	gotoXY(_frameNumberSoldTitle[0].x() + 1, _frameNumberSoldTitle[0].y() + 1);
	std::wcout << title;
}

void DrawStats::drawFrameLaptopNames() {
	class Rectangle rec(_frameLaptopNames[0], _frameLaptopNames[1]);
	rec.draw();
}

void DrawStats::drawFrameNumber() {
	class Rectangle rec(_frameNumberSold[0], _frameNumberSold[1]);
	rec.draw();
}

void DrawStats::drawFrameLaptopSpecs() {
	class Rectangle rec(_frameLaptopSpecs[0], _frameLaptopSpecs[1]);
	rec.draw();
}

void DrawStats::drawFramePage() {
	gotoXY(_framePage[0].x(), _framePage[0].y());
	std::wcout << L"Trang ";
	if (_page < 10) std::wcout << L"0";
	std::wcout << _page;
}

void DrawStats::drawFrameMonths() {
	int x = _frameInstruction[0].x() + (_frameInstruction[1].x() - _frameInstruction[0].x() - 15) / 2;
	_frameMonths = { Point(x, _frameInstruction[1].y() + 2), Point(x + 16, _frameInstruction[1].y() + 15) };
	class Rectangle rec(_frameMonths[0], _frameMonths[1]);
	rec.draw();
	for (int i = 1; i <= 12; ++i) {
		gotoXY(_frameMonths[0].x() + _indent + 3, _frameMonths[0].y() + i);
		std::wcout << L"Tháng " << i;
	}
}

void DrawStats::drawFrameSales() {
	_frameSales[0].setY(_frameInstruction[1].y() + 2);
	_frameSales[1].setY(_frameSales[0].y() + 3);
	class Rectangle rec(_frameSales[0], _frameSales[1]);
	rec.draw();
}

void DrawStats::drawAllFrames() {
	drawFrameSales();
}

int DrawStats::menuProcessing() {
	char keyboard = ' ';

	drawFrameTitle(L"THỐNG KÊ BÁO CÁO");
	drawFrameInstruction(0);
	drawFrameMenu();

	while (keyboard != ESC && keyboard != ENTER) {
		gotoXY(_frameMenu[0].x() + _indent, _frameMenu[0].y() + _menuChoice + 1);
		std::wcout << _bullet;

		if (_kbhit) {
			keyboard = _getch();

			if ((keyboard == 'w' || keyboard == 'W') && _menuChoice > 0) {
				//remove current bullet
				gotoXY(_frameMenu[0].x() + _indent, _frameMenu[0].y() + _menuChoice + 1);
				std::wcout << L"  ";

				_menuChoice--;
			}
			else if ((keyboard == 's' || keyboard == 'S') && _menuChoice < 2) {
				//remove current bullet
				gotoXY(_frameMenu[0].x() + _indent, _frameMenu[0].y() + _menuChoice + 1);
				std::wcout << L"  ";

				_menuChoice++;
			}
		}
	}
	if (keyboard == ENTER)
		return _menuChoice;
	else
		return ESC;
}

void DrawStats::viewLaptopsAndNumber(vector<pair<Laptop, int>> v) {
	int n = v.size();
	int end = _page <= n / 10 ? 10 * _page - 1 : n - 1;
	int start = _page * 10 - 10;

	for (int i = start; i <= end; ++i) {
		gotoXY(_frameLaptopNames[0].x() + 2 * _indent + 1, _frameLaptopNames[0].y() + (i % 10) + 1);
		std::wcout << v[i].first.name();
		gotoXY(_frameNumberSold[0].x() + 6, _frameNumberSold[0].y() + (i % 10) + 1);
		std::wcout << (v[i].second < 10 ? L"0" : L"") << v[i].second;
	}
}

int DrawStats::runoutLaptopProcessing() {
	vector<Laptop> laptops = stats->under10();
	char keyboard = ' ';
	bool redraw = 1;

	if (!laptops.empty()) {
		vector<pair<Laptop, int>> v;
		int totalPages = ceil(laptops.size() * 1.0 / 10);
		int choice = 0;
		int choiceDisplay = 0;
		bool reviewContents = 0;

		for (int i = 0; i < laptops.size(); ++i)
			v.push_back(make_pair(laptops[i], laptops[i].amount()));

		while (keyboard != ESC) {
			choiceDisplay = choice % 10;
			gotoXY(_frameLaptopNames[0].x() + _indent, _frameLaptopNames[0].y() + choiceDisplay + 1);
			std::wcout << _bullet;

			if (redraw) {
				drawFrameTitle(L"MẶT HÀNG SẮP HẾT");
				drawFrameLaptopNameTitle();
				drawFrameLaptopNames();
				drawFrameNumberTitle(L"Số lượng còn");
				drawFrameNumber();
				drawFrameInstruction(1);
				drawFramePage();
				viewLaptopsAndNumber(v);

				redraw = 0;
			}

			if (reviewContents) {
				//clear laptopNames frame
				clearRegion(Point(_frameLaptopNames[0].x() + 1, _frameLaptopNames[0].y() + 1),
					Point(_frameLaptopNames[1].x() - 1, _frameLaptopNames[1].y() - 1));
				//clear numberSold frame
				clearRegion(Point(_frameNumberSold[0].x() + 1, _frameNumberSold[0].y() + 1),
					Point(_frameNumberSold[1].x() - 1, _frameNumberSold[1].y() - 1));

				viewLaptopsAndNumber(v);
				reviewContents = 0;
			}

			//draw arrows
			if (_page > 1) drawArrowLeft();
			else clearArrowLeft();
			if (_page < totalPages) drawArrowRight();
			else clearArrowRight();

			if (_kbhit()) {
				keyboard = _getch();

				if ((keyboard == 'w' || keyboard == 'W') && choiceDisplay > 0) {
					//remove current bullet
					gotoXY(_frameLaptopNames[0].x() + _indent, _frameLaptopNames[0].y() + choiceDisplay + 1);
					std::wcout << L"  ";

					choice--;
				}
				else if ((keyboard == 's' || keyboard == 'S') && choice < v.size() - 1 && choiceDisplay < 9) {
					//remove current bullet
					gotoXY(_frameLaptopNames[0].x() + _indent, _frameLaptopNames[0].y() + choiceDisplay + 1);
					std::wcout << L"  ";

					choice++;
				}
				else if ((keyboard == 'd' || keyboard == 'D') && _page < totalPages) {
					//remove current bullet
					gotoXY(_frameLaptopNames[0].x() + _indent, _frameLaptopNames[0].y() + choiceDisplay + 1);
					std::wcout << L"  ";

					_page++;
					choice = 10 * _page - 10;
					reviewContents = 1;

					drawFramePage();
				}
				else if ((keyboard == 'a' || keyboard == 'A') && _page > 1) {
					//remove current bullet
					gotoXY(_frameLaptopNames[0].x() + _indent, _frameLaptopNames[0].y() + choiceDisplay + 1);
					std::wcout << L"  ";

					_page--;
					choice = (choice - 10) / 10 * 10;
					reviewContents = 1;

					drawFramePage();
				}
				else if (keyboard == ENTER) {
					clrscr();
					vector<vector<wstring>> specs = laptops[choice].toString();
					int yEnd = _frameLaptopSpecs[0].y() + specs.size() + 1;
					_frameLaptopSpecs[1].setY(yEnd);

					drawFrameTitle(L"THÔNG SỐ LAPTOP");
					drawFrameInstruction(3);
					drawFrameLaptopSpecs();
					for (int i = 0; i < specs.size(); ++i) {
						gotoXY(_frameLaptopSpecs[0].x() + 2 * _indent + 1, _frameLaptopSpecs[0].y() + i + 1);
						std::wcout << specs[i][0] << L": " << specs[i][1];
					}

					while (keyboard != ESC)
						keyboard = _getch();
					keyboard = ' ';
					clrscr();
					redraw = 1;
				}
			}
		}
		_page = 1; //reset
	}
	else {
		gotoXY(_frameLaptopNames[0].x() + _indent, _frameLaptopNames[0].y() + 1);
		std::wcout << L"Không có mặt hàng nào sắp hết";

		while (keyboard != ESC)
			keyboard = _getch();
	}

	return keyboard;
}

int DrawStats::bestsellerProcessing() {
	char keyboard = ' ';
	int choice = 0;
	int choiceDisplay = 0;
	wcout << L"Đang tải...";
	vector<pair<Laptop, int>> bestseller = stats->bestsellersPrevMonth();
	bool review = 1;
	bool reviewContents = 1;
	int totalPages = ceil(bestseller.size() * 1.0 / 10);
	gotoXY(0, 0);
	wcout << L"           ";

	if (!bestseller.empty()) {
		while (keyboard != ESC) {
			choiceDisplay = choice % 10;
			gotoXY(_frameLaptopNames[0].x() + _indent, _frameLaptopNames[0].y() + choiceDisplay + 1);
			std::wcout << _bullet;

			if (review) {
				drawFrameTitle(L"DANH SÁCH MẶT HÀNG BÁN CHẠY THÁNG TRƯỚC");
				drawFrameInstruction(1);
				drawFrameLaptopNameTitle();
				drawFrameNumberTitle(L"Số lượng bán");
				drawFrameLaptopNames();
				drawFrameNumber();
				drawFramePage();
				review = 0;
			}
			if (reviewContents) {
				//clear laptopNames frame
				clearRegion(Point(_frameLaptopNames[0].x() + 1, _frameLaptopNames[0].y() + 1),
					Point(_frameLaptopNames[1].x() - 1, _frameLaptopNames[1].y() - 1));
				//clear numberSold frame
				clearRegion(Point(_frameNumberSold[0].x() + 1, _frameNumberSold[0].y() + 1),
					Point(_frameNumberSold[1].x() - 1, _frameNumberSold[1].y() - 1));

				viewLaptopsAndNumber(bestseller);
				reviewContents = 0;
			}

			//draw arrows
			if (_page > 1) drawArrowLeft();
			else clearArrowLeft();
			if (_page < totalPages) drawArrowRight();
			else clearArrowRight();

			if (_kbhit()) {
				keyboard = _getch();

				if ((keyboard == 'w' || keyboard == 'W') && choice > 0) {
					//remove current bullet
					gotoXY(_frameLaptopNames[0].x() + _indent, _frameLaptopNames[0].y() + choiceDisplay + 1);
					std::wcout << L"  ";

					choice--;
				}
				else if ((keyboard == 's' || keyboard == 'S') && choice < bestseller.size() - 1) {
					//remove current bullet
					gotoXY(_frameLaptopNames[0].x() + _indent, _frameLaptopNames[0].y() + choiceDisplay + 1);
					std::wcout << L"  ";

					choice++;
				}
				else if ((keyboard == 'a' || keyboard == 'A') && _page > 1) {
					//remove current bullet
					gotoXY(_frameLaptopNames[0].x() + _indent, _frameLaptopNames[0].y() + choiceDisplay + 1);
					std::wcout << L"  ";

					_page--;
					choice = (choice - 10) / 10 * 10;
					reviewContents = 1;

					drawFramePage();
				}
				else if ((keyboard == 'd' || keyboard == 'D') && _page < totalPages) {
					//remove current bullet
					gotoXY(_frameLaptopNames[0].x() + _indent, _frameLaptopNames[0].y() + choiceDisplay + 1);
					std::wcout << L"  ";

					_page++;
					choice = 10 * _page - 10;
					reviewContents = 1;

					drawFramePage();
				}
				else if (keyboard == ENTER) {
					clrscr();
					drawFrameTitle(L"THÔNG SỐ LAPTOP");
					drawFrameInstruction(3);
					
					Laptop laptop = bestseller[choice].first;
					vector<vector<wstring>> specs = laptop.toString();
					int n = laptop.totalProperties();
					int yEnd = _frameLaptopSpecs[0].y() + n + 1;
					_frameLaptopSpecs[1].setY(yEnd);
					drawFrameLaptopSpecs();
					_frameLaptopSpecs[1].setY(_frameInstruction[1].y() + 15); //reset

					for (int i = 0; i < n; ++i) {
						gotoXY(_frameLaptopSpecs[0].x() + _indent, _frameLaptopSpecs[0].y() + i + 1);
						std::wcout << specs[i][0] << L": " << specs[i][1];
					}

					while (keyboard != ESC)
						if (_kbhit())
							keyboard = _getch();
					keyboard = ' ';

					clrscr();
					review = reviewContents = 1;
				}
			}
		}
		_page = 1; //reset
	}
	else {
		gotoXY(_frameLaptopNames[0].x() + _indent, _frameLaptopNames[0].y() + 1);
		std::wcout << L"Tất cả các mặt hàng được bán với số lượng là 1";

		while (keyboard != ESC)
			if (_kbhit())
				keyboard = _getch();
	}
	return keyboard;
}

void DrawStats::drawArrowLeft() {
	gotoXY(_framePage[0].x() - 2, _framePage[0].y());
	std::wcout << L"◄";
}

void DrawStats::drawArrowRight() {
	gotoXY(_framePage[1].x() + 1, _framePage[1].y());
	std::wcout << L"►";
}

void DrawStats::clearArrowLeft() {
	gotoXY(_framePage[0].x() - 2, _framePage[0].y());
	std::wcout << L" ";
}

void DrawStats::clearArrowRight() {
	gotoXY(_framePage[1].x() + 1, _framePage[1].y());
	std::wcout << L" ";
}

int DrawStats::saleProcessing() {
	char keyboard = ' ';
	int month = 1;
	bool redrawFrameMonth = 1;

	while (keyboard != ESC) {
		if (redrawFrameMonth) {
			drawFrameTitle(L"DOANH THU");
			drawFrameInstruction(2);
			drawFrameMonths();
			redrawFrameMonth = 0;
		}

		//print bullet
		gotoXY(_frameMonths[0].x() + _indent, _frameMonths[0].y() + month);
		std::wcout << _bullet;

		if (_kbhit()) {
			keyboard = _getch();

			if ((keyboard == 'w' || keyboard == 'W') && month > 1) {
				//remove current bullet
				gotoXY(_frameMonths[0].x() + _indent, _frameMonths[0].y() + month);
				std::wcout << L"  ";

				month--;
			}
			else if ((keyboard == 's' || keyboard == 'S') && month < 12) {
				//remove current bullet
				gotoXY(_frameMonths[0].x() + _indent, _frameMonths[0].y() + month);
				std::wcout << L"  ";

				month++;
			}
			else if (keyboard == ENTER) {
				unsigned long long revenue = stats->revenue(month);
				unsigned long long profit = stats->profit(month);
				clrscr();
				drawFrameTitle(L"DOANH SỐ THÁNG " + to_wstring(month));
				drawFrameInstruction(3);
				drawFrameSales();

				gotoXY(_frameSales[0].x() + _indent, _frameSales[0].y() + 1);
				std::wcout << L"Doanh số: " << formattedPrice(revenue) << L" VND";
				gotoXY(_frameSales[0].x() + _indent, _frameSales[0].y() + 2);
				std::wcout << L"Lợi nhuận: " << formattedPrice(profit) << L" VND";

				while (keyboard != ESC)
					keyboard = _getch();
				keyboard = ' ';

				clrscr();
				redrawFrameMonth = 1;
			}
		}
	}
	return keyboard;
}