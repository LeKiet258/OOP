#include"DrawOrder.h"
#include"Rectangle.h"

void DrawOrder::resetVariables() {
	_orderChoice = 0;
	_monthChoice = _page = 1;
}

void DrawOrder::drawFrameInstruction(int code) {
	vector<wstring> instructions;
	class Rectangle rec;

	if (code == 0) {
		instructions = { L"[a/d]: qua trang trái/phải", L"[x]: Xóa đơn hàng", L"[Enter]: Chọn đơn hàng", L"[Esc]: Trở lại Menu"};
	}
	else if (code == 1) {
		instructions = { L"[t]: Thêm chi tiết", L"[x]: Xóa chi tiết", L"[f]: Sửa chi tiết", L"[Esc]: Trở lại" };
	}

	int maxMessageLen = longestStringLength(instructions);
	int yEnd = _frameInstruction[0].y() + instructions.size() + 1;
	int yStart = _frameInstruction[0].y();
	int xStart = (consoleWidth - (maxMessageLen + 4)) / 2 + 1;
	int xEnd = xStart + maxMessageLen + 3;
	
	_frameInstruction[0].setX(xStart);
	_frameInstruction[1].setX(xEnd);
	_frameInstruction[1].setY(yEnd);

	rec = class Rectangle(_frameInstruction[0], _frameInstruction[1]);
	rec.draw();
	for (int i = 0; i < instructions.size(); ++i) {
		gotoXY(_frameInstruction[0].x() + 2, _frameInstruction[0].y() + i + 1);
		std::wcout << instructions[i];
	}
}

void DrawOrder::clearInstruction() {
	clearRegion(Point(1, _frameInstruction[0].y()),
		Point(consoleWidth - 1, _frameInstruction[1].y()));
}

void DrawOrder::drawFrameIdTitle() {
	class Rectangle rec(_frameIdTitle[0], _frameIdTitle[1]);
	rec.draw();
	gotoXY(_frameIdTitle[0].x() + 1, _frameIdTitle[0].y() + 1);
	wcout << L" Mã đơn hàng";
}

void DrawOrder::drawFrameDetailTitle() {
	class Rectangle rec(_frameDetailTitle[0], _frameDetailTitle[1]);
	rec.draw();
	wstring mess = L"Chi tiết đơn hàng";
	int x = (_frameDetailTitle[1].x() - _frameDetailTitle[0].x() - mess.length()) / 2 + _frameDetailTitle[0].x();
	gotoXY(x, _frameDetailTitle[0].y() + 1);
	wcout << mess;
}

void DrawOrder::drawFrameIds() {
	class Rectangle rec(_frameIds[0], _frameIds[1]);
	rec.draw();

}

void DrawOrder::drawFramePage() {
	gotoXY(_framePage[0].x(), _framePage[0].y());
	wcout << L"Trang ";
	if (_page < 10) wcout << L"0";
	wcout << _page;
}

void DrawOrder::drawFrameMonths() {
	class Rectangle rec(_frameMonths[0], _frameMonths[1]);
	rec.draw();
	for (int i = 1; i <= 12; ++i) {
		gotoXY(_frameMonths[0].x() + _indent + 3, _frameMonths[0].y() + i);
		wcout << L"Tháng " << i;
	}
}

int DrawOrder::monthProcessing() {
	char keyboard = ' ';

	drawFrameTitle(L"ĐƠN HÀNG");
	drawFrameMonths();

	while (keyboard != ENTER && keyboard != ESC) {
		gotoXY(_frameMonths[0].x() + _indent, _frameMonths[0].y() + _monthChoice);
		std::wcout << _bullet;

		if (_kbhit()) {
			keyboard = _getch();

			if ((keyboard == 'w' || keyboard == 'W') && _monthChoice > 1) {
				//remove current _bullet
				gotoXY(_frameMonths[0].x() + _indent, _frameMonths[0].y() + _monthChoice);
				std::wcout << L"  ";
				_monthChoice--;
			}
			else if ((keyboard == 's' || keyboard == 'S') && _monthChoice < 12) {
				//remove current _bullet
				gotoXY(_frameMonths[0].x() + _indent, _frameMonths[0].y() + _monthChoice);
				std::wcout << L"  ";
				_monthChoice++;
			}
		}
	}
	return keyboard;
}

void DrawOrder::drawFrameDetails(int yEnd) {
	if (yEnd != _frameDetails[1].y()) {
		clearRegion(_frameDetails[0], _frameDetails[1]); //clear frameDetails
		_frameDetails[1].setY(yEnd);
	}

	class Rectangle rec(_frameDetails[0], _frameDetails[1]); //Point(_frameDetails[1].x(), y)
	rec.draw();
}

void DrawOrder::clearFrameDetailContent() {
	int n = _orderFactory->ordersByMonth(_monthChoice)[_orderChoice].totalDetails();
	int y = _frameDetails[0].y() + n + 1;
	clearRegion(Point(_frameDetails[0].x() + 1, _frameDetails[0].y() + 1),
		Point(_frameDetails[1].x() - 1, _frameDetails[1].y() - 1));
}

void DrawOrder::drawArrowLeft() {
	gotoXY(_framePage[0].x() - 2, _framePage[0].y());
	wcout << L"◄";
}

void DrawOrder::drawArrowRight() {
	gotoXY(_framePage[1].x() + 1, _framePage[1].y());
	wcout << L"►";
}

void DrawOrder::clearArrowLeft() {
	gotoXY(_framePage[0].x() - 2, _framePage[0].y());
	wcout << L" ";
}

void DrawOrder::clearArrowRight() {
	gotoXY(_framePage[1].x() + 1, _framePage[1].y());
	wcout << L" ";
}

void DrawOrder::drawFrameTotalOrders() {
	vector<Order> v = _orderFactory->ordersByMonth(_monthChoice);
	wstring field = L"Tổng đơn hàng: ";
	int n1 = field.length();
	int n2 = log10(v.size()) + 1;
	int x = (consoleWidth - (n1 + n2)) / 2 + 1;
	gotoXY(x, _frameInstruction[1].y() + 1); //52
	wcout << field << v.size() << L" ";
}

int DrawOrder::idProcessing() {
	char keyboard = ' ';
	vector<Order> ordersByMonth = _orderFactory->ordersByMonth(_monthChoice);
	bool reviewDetail = 0;
	bool reviewIds = 0;
	int totalPages = ceil(ordersByMonth.size() * 1.0 / 10);
	int choiceDisplay = 0;
	int yEnd = _frameDetails[0].y() + ordersByMonth[_orderChoice].totalDetails() + 1;

	clearFrameTitle();
	drawFrameTitle(L"ĐƠN HÀNG");
	clearInstruction();
	drawFrameInstruction(0);
	drawFrameTotalOrders();
	drawFrameIdTitle();
	drawFrameIds();
	drawFrameDetailTitle();
	drawFramePage();
	drawFrameDetails(yEnd);
	viewDetails();
	viewIds();

	while (keyboard != ENTER && keyboard != ESC) {
		choiceDisplay = _orderChoice % 10;
		gotoXY(_frameIds[0].x() + _indent, _frameIds[0].y() + choiceDisplay + 1);
		std::wcout << _bullet;

		if (reviewDetail) {
			clearFrameDetailContent();
			viewDetails();
			reviewDetail = 0;
		}
		if (reviewIds) {
			clearFrameIdContent();
			viewIds();
			reviewIds = 0;
		}

		//draw arrows
		if (_page > 1) drawArrowLeft();
		else clearArrowLeft();
		if (_page < totalPages) drawArrowRight();
		else clearArrowRight();

		if (_kbhit()) {
			keyboard = _getch();

			if ((keyboard == 'w' || keyboard == 'W') && choiceDisplay > 0) {
				//remove current _bullet
				gotoXY(_frameIds[0].x() + _indent, _frameIds[0].y() + choiceDisplay + 1);
				std::wcout << L"  ";

				_orderChoice--;
				reviewDetail = 1;

				yEnd = _frameDetails[0].y() + ordersByMonth[_orderChoice].totalDetails() + 1;
				drawFrameDetails(yEnd);
			}
			else if ((keyboard == 's' || keyboard == 'S') && _orderChoice < ordersByMonth.size() - 1 && choiceDisplay < 9) {
				//remove current _bullet
				gotoXY(_frameIds[0].x() + _indent, _frameIds[0].y() + choiceDisplay + 1);
				std::wcout << L"  ";

				_orderChoice++;
				reviewDetail = 1;

				yEnd = _frameDetails[0].y() + ordersByMonth[_orderChoice].totalDetails() + 1;
				drawFrameDetails(yEnd);
			}
			else if ((keyboard == 'd' || keyboard == 'D') && _page < totalPages) {
				//remove current _bullet
				gotoXY(_frameIds[0].x() + _indent, _frameIds[0].y() + choiceDisplay + 1);
				std::wcout << L"  ";

				_page++;
				_orderChoice = 10 * _page - 10;
				reviewDetail = 1;
				reviewIds = 1;
				
				drawFramePage();
				yEnd = _frameDetails[0].y() + ordersByMonth[_orderChoice].totalDetails() + 1;
				drawFrameDetails(yEnd);
			}
			else if ((keyboard == 'a' || keyboard == 'A') && _page > 1) {
				//remove current _bullet
				gotoXY(_frameIds[0].x() + _indent, _frameIds[0].y() + choiceDisplay + 1);
				std::wcout << L"  ";
				
				_page--;
				_orderChoice = (_orderChoice - 10) / 10 * 10;
				reviewDetail = 1;
				reviewIds = 1;

				drawFramePage();
				yEnd = _frameDetails[0].y() + ordersByMonth[_orderChoice].totalDetails() + 1;
				drawFrameDetails(yEnd);
			}
			else if ((keyboard == 'x' || keyboard == 'X') && !ordersByMonth.empty()) {
				_orderFactory->removeOrder(_monthChoice, _orderChoice);
				if (_orderChoice == ordersByMonth.size() - 1)
					_orderChoice--;
				ordersByMonth.erase(ordersByMonth.begin() + _orderChoice);

				//reload totalPages
				totalPages = ceil(ordersByMonth.size() * 1.0 / 10);
				if (_page > totalPages && totalPages >= 1) {
					_page--;
					drawFramePage();
				}
				drawFrameTotalOrders();
				reviewIds = reviewDetail = 1;
			}
		}
	}
	//_page = 1;
	return keyboard;
}

int DrawOrder::singleOrderProcessing() {
	char keyboard = ' ';
	int choice = 0;
	Order order = _orderFactory->ordersByMonth(_monthChoice)[_orderChoice];
	int expandFrame = 0;
	bool updateDetails = 0;

	drawFrameTitle(L"CHI TIẾT ĐƠN HÀNG");
	clearInstruction();
	drawFrameInstruction(1);

	while (keyboard != ESC) {
		gotoXY(_frameDetails[0].x() + _indent, _frameDetails[0].y() + choice + 1);
		wcout << _bullet;

		if (expandFrame != 0) {
			//clear the last line
			if (expandFrame == 1) {
				clearRegion(Point(_frameDetails[0].x() + 1, _frameDetails[1].y()),
					Point(_frameDetails[1].x() - 1, _frameDetails[1].y()));
			}
			else {
				clearRegion(Point(_frameDetails[0].x(), _frameDetails[1].y()),
					Point(_frameDetails[1].x(), _frameDetails[1].y()));
			}

			//redraw frame details
			int oldY = _frameDetails[1].y();
			_frameDetails[1].setY(oldY + expandFrame);
			drawFrameDetails(_frameDetails[1].y());
			
			expandFrame = 0;
		}
		if (updateDetails) {
			clearFrameDetailContent();
			viewDetails();

			updateDetails = 0;
		}
		
		if (_kbhit()) {
			keyboard = _getch();

			if ((keyboard == 'w' || keyboard == 'W') && choice > 0) {
				//remove current _bullet
				gotoXY(_frameDetails[0].x() + _indent, _frameDetails[0].y() + choice + 1);
				std::wcout << L"  ";

				choice--;
			}
			else if ((keyboard == 's' || keyboard == 'S') && choice < order.totalDetails() - 1) {
				//remove current _bullet
				gotoXY(_frameDetails[0].x() + _indent, _frameDetails[0].y() + choice + 1);
				std::wcout << L"  ";

				choice++;
			}
			else if (keyboard == 't' || keyboard == 'T') {
				_setmode(_fileno(stdin), _O_WTEXT);
				_setmode(_fileno(stdout), _O_WTEXT);
				wstring msg = L"THÊM THÔNG TIN CHO ĐƠN HÀNG";
				gotoXY((consoleWidth - msg.length()) / 2 + 1, _frameInstruction[1].y() + 3);
				wcout << msg;

				cursortype();
				drawFrameField();
				wstring field;
				getline(wcin, field);

				drawFrameInput();
				wstring input;
				getline(wcin, input);
				nocursortype();

				clearFrameField();
				clearFrameInput();

				order.pushBackDetail(field, input);
				_orderFactory->updateOrder(_monthChoice, _orderChoice, order); //update source of truth
				
				expandFrame = 1;
				updateDetails = 1;

				gotoXY((consoleWidth - msg.length()) / 2 + 1, _frameInstruction[1].y() + 3);
				for (int i = 0; i < msg.length(); ++i) wcout << L" ";
			}
			else if ((keyboard == 'x' || keyboard == 'X') && order.totalDetails() > 0) {
				if (choice == 0) {
					wstring msg = L"KHÔNG THỂ XÓA MÃ ĐƠN HÀNG !";
					int x = (consoleWidth - msg.length()) / 2 + 1;
					gotoXY(x, _frameInstruction[1].y() + 3);
					wcout << msg;
					Sleep(1500);
					gotoXY(x, _frameInstruction[1].y() + 3);
					for (int i = 0; i < msg.length(); ++i)
						wcout << L" ";
				}
				else {
					order.changeDetail(choice, L"");
					_orderFactory->updateOrder(_monthChoice, _orderChoice, order); //update source of truth

					if (order.totalDetails() < _frameDetails[1].y() - _frameDetails[0].y() - 1) {
						expandFrame = -1;
						choice--;
					}
					updateDetails = 1;
				}
			}
			else if (keyboard == 'f' || keyboard == 'F') {
				if (choice == 0) {
					wstring msg = L"KHÔNG THỂ THAY ĐỔI MÃ ĐƠN HÀNG !";
					int x = (consoleWidth - msg.length()) / 2 + 1;
					gotoXY(x, _frameInstruction[1].y() + 3);
					wcout << msg;
					Sleep(1500);
					gotoXY(x, _frameInstruction[1].y() + 3);
					for (int i = 0; i < msg.length(); ++i)
						wcout << L" ";
				}
				else {
					wstring mess = L"Sửa " + order.toString()[choice][0] + L" thành:";
					int startX = (consoleWidth - (mess.length() + 33)) / 2;
					int startY = _frameInstruction[1].y() + (_frameDetailTitle[0].y() - _frameInstruction[1].y() - 3) / 2 + 1;
					wstring newData;
					
					cursortype();
					drawFrameEdit(mess, Point(startX, startY), Point(startX + mess.length() + 33, startY + 2));
					getline(wcin, newData);
					clearRegion(Point(startX, startY), Point(startX + mess.length() + 33, startY + 2));
					nocursortype();

					order.changeDetail(choice, newData);
					_orderFactory->updateOrder(_monthChoice, _orderChoice, order);
					updateDetails = 1;
					}
				}
			}
		}
	
	//clear current _bullet
	gotoXY(_frameDetails[0].x() + _indent, _frameDetails[0].y() + choice + 1);
	std::wcout << L"  ";
	
	return keyboard;
}

void DrawOrder::drawFrameField() {
	drawFrameEdit(L"Trường:   ", _frameField[0], _frameField[1]);
}

void DrawOrder::drawFrameInput() {
	drawFrameEdit(L"Thông tin:", _frameInput[0], _frameInput[1]);
}

void DrawOrder::clearFrameField() {
	clearRegion(_frameField[0], _frameField[1]);
}

void DrawOrder::clearFrameInput() {
	clearRegion(_frameInput[0], _frameInput[1]);
}

void DrawOrder::clearFrameIdContent() {
	clearRegion(Point(_frameIds[0].x() + 1, _frameIds[0].y() + 1),
		Point(_frameIds[1].x() - 1, _frameIds[1].y() - 1));
}

void DrawOrder::viewDetails() {
	Order order = _orderFactory->ordersByMonth(_monthChoice)[_orderChoice];
	vector<vector<wstring>> details = order.toString();

	for (int i = 0; i < details.size(); ++i) {
		gotoXY(_frameDetails[0].x() + _indent + 3, _frameDetails[0].y() + i + 1);
		wcout << details[i][0] << L": " << details[i][1];
	}
}

void DrawOrder::viewIds() {
	vector<Order> ordersByMonth = _orderFactory->ordersByMonth(_monthChoice);
	int n = ordersByMonth.size();
	int end = _page <= n / 10 ? 10*_page - 1 : n - 1;
	int start = _page * 10 - 10;

	for (int i = start; i <= end; ++i) {
		gotoXY(_frameIds[0].x() + 2 * _indent + 1, _frameIds[0].y() + (i % 10) + 1);
		wcout << ordersByMonth[i].orderId();
	}
}

