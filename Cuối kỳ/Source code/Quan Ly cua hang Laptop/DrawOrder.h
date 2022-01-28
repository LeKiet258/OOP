#pragma once
#include"OrderFactory.h"
#include"Point.h"
#include"Draw.h"

class DrawOrder : public Draw {
private:
	//inline static DrawOrder* _instance = 0;
	shared_ptr<OrderFactory> _orderFactory; //source of truth, with a laptop list based on _catalog
	int _page;
	int _monthChoice; //1-12
	int _orderChoice;

	vector<Point> _frameIds;
	vector<Point> _frameMonths;
	vector<Point> _frameDetails;
	vector<Point> _frameEdit;
	vector<Point> _framePage;
	vector<Point> _frameIdTitle;
	vector<Point> _frameDetailTitle;
	vector<Point> _frameField;
	vector<Point> _frameInput;

	DrawOrder() {
		_orderChoice = 0;
		_monthChoice = _page = 1;
		_orderFactory = OrderFactory::instance();

		int x = (consoleWidth - 22) / 2 + 1;
		int y = 2;
		_frameEdit = { Point(x, y + 11), Point(x + 21, y + 13) };

		x = (consoleWidth - 15) / 2 + 1;
		_frameMonths = { Point(x, _frameInstruction[1].y() + 2), Point(x + 16, _frameInstruction[1].y() + 15) };

		x = (consoleWidth - 73) / 2 + 1;
		_frameField = { Point(x, _frameInstruction[1].y() + 3), Point(x + 72,  _frameInstruction[1].y() + 5) };
		_frameInput = { Point(x,  _frameInstruction[1].y() + 6), Point(x + 72,  _frameInstruction[1].y() + 8) };

		x = (consoleWidth - 87) / 2 + 1;
		_frameDetailTitle = { Point(x + 17, _frameInput[1].y() + 2),Point(x + 83,  _frameInput[1].y() + 4) };
		_frameDetails = { Point(_frameDetailTitle[0].x(), _frameDetailTitle[1].y() + 1), Point(_frameDetailTitle[1].x(), _frameDetailTitle[1].y() + 16) };
		y = _frameDetails[0].y() + (_frameDetails[1].y() - _frameDetailTitle[0].y() - 16) / 2;
		_frameIdTitle = { Point(x, y), Point(x + 15, y + 2) };
		_frameIds = { Point(_frameIdTitle[0].x(), y + 3), Point(_frameIdTitle[1].x(), y + 14) };

		x = _frameIds[0].x() + (_frameIds[1].x() - _frameIds[0].x() - 8) / 2 + 1;
		_framePage = { Point(x, _frameIds[1].y() + 1), Point(x + 8, _frameIds[1].y() + 1) };

	}
public:
	static shared_ptr<DrawOrder> instance() {
		static shared_ptr<DrawOrder> _instance(new DrawOrder());
		return _instance;
	}

	void setOrderChoice(int i) { _orderChoice = i; }
	void setPage(int p) { _page = p; }
	void resetVariables();
	void drawFrameField();
	void drawFrameInput();
	void drawFrameMonths();
	void drawFrameInstruction(int code);
	void drawFrameTotalOrders();
	void drawFrameIdTitle();
	void drawFrameDetailTitle();
	void drawFrameIds();
	void drawFrameDetails(int yEnd);
	void drawFramePage();
	void drawAllFrames(); //checking
	void drawArrowLeft();
	void drawArrowRight();

	void clearFrameDetailContent();
	void clearFrameIdContent();
	void clearInstruction();
	void clearFrameField();
	void clearFrameInput();
	void clearArrowLeft();
	void clearArrowRight();

	void viewIds();
	void viewDetails();
	int monthProcessing();
	int idProcessing();
	int singleOrderProcessing();
};