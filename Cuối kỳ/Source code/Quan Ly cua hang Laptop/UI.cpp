#include"UI.h"

void UI::drawFrameMenu() {
	class Rectangle frameMenu(_frameMenu[0], _frameMenu[1]);
	frameMenu.draw();
}

void UI::drawFrameBigTitle() {
	for (int i = 0; i < _bigTitle.size();++i) {
		gotoXY(_frameBigTitle[0].x(), _frameBigTitle[0].y() + i + 1);
		wcout << _bigTitle[i];
	}
}

int UI::menu() {
	char keyboard = ' ';
	vector<wstring> options = { L"DANH MỤC", L"ĐƠN HÀNG", L"THỐNG KÊ BÁO CÁO", L"EXIT" };
	wstring bullet = L">>";
	
	clrscr();
	drawFrameBigTitle();
	drawFrameMenu();

	for (int i = 0; i < options.size(); ++i) {
		gotoXY(_frameMenu[0].x() + 6, _frameMenu[0].y() + i + 1);
		wcout << options[i];
	}

	while (keyboard != ENTER) {
		gotoXY(_frameMenu[0].x() + 2, _frameMenu[0].y() + _menuChoice + 1);
		wcout << bullet;

		if (_kbhit()) {
			keyboard = _getch();

			if ((keyboard == 'w' || keyboard == 'W')) {
				//remove current bullet
				gotoXY(_frameMenu[0].x() + 2, _frameMenu[0].y() + _menuChoice + 1);
				wcout << L"  ";

				if (_menuChoice > 0) _menuChoice--;
				else _menuChoice = 3;
			}
			else if ((keyboard == 's' || keyboard == 'S')) {
				//remove current bullet
				gotoXY(_frameMenu[0].x() + 2, _frameMenu[0].y() + _menuChoice + 1);
				wcout << L"  ";

				if (_menuChoice < 3) _menuChoice++;
				else _menuChoice = 0;
			}
		}
	}
	return _menuChoice;
}

void UI::catalogProcessing() {
	shared_ptr<DrawCatalog> catalog = DrawCatalog::instance();
	char keyboard = ' ';
	clrscr();

	catalog->brandProcessing();
	catalog->resetVariables();
}

void UI::orderProcessing() {
	shared_ptr<DrawOrder> drawOrder = DrawOrder::instance();
	char keyboard = ' ';

	while (keyboard != ESC) {
		clrscr();
		keyboard = drawOrder->monthProcessing();

		if (keyboard == ENTER) {
			clrscr();
			while (keyboard != ESC) {
				keyboard = drawOrder->idProcessing();

				if (keyboard == ENTER) 
					drawOrder->singleOrderProcessing();
			}
			keyboard = ' '; //reset keyboard
			drawOrder->setPage(1);
			drawOrder->setOrderChoice(0);
		}
	}
	drawOrder->resetVariables();
}

void UI::statsProcessing() {
	shared_ptr<DrawStats> drawStats = DrawStats::instance();
	Draw drawObj;
	char keyboard = ' ';

	while (keyboard != ESC) {
		clrscr();
		keyboard = drawStats->menuProcessing();

		if (keyboard != ESC) {
			clrscr();

			switch (keyboard) {
			case 0:
				keyboard = drawStats->runoutLaptopProcessing();
				break;
			case 1:
				keyboard = drawStats->bestsellerProcessing();
				break;
			case 2:
				keyboard = drawStats->saleProcessing();
				break;
			}
			keyboard = ' '; //reset keyboard
		}
	}
	drawStats->resetVariables();
}

void UI::mainProcessing() {
	while (_menuChoice != 3) { //EXIT
		menu();

		switch (_menuChoice) {
		case 0:
			catalogProcessing();
			break;
		case 1:
			orderProcessing();
			break;
		case 2:
			statsProcessing();
			break;
		}
	}
}