#pragma once
#include"Stats.h"
#include"Point.h"
#include"Draw.h"

class DrawStats : public Draw {
private:
	//inline static DrawStats* _instance = 0;
	shared_ptr<Stats> stats;
	int _menuChoice;
	int _page;
	vector<Point> _frameMenu;
	vector<Point> _frameBestsellers;
	vector<Point> _frameMonths;
	vector<Point> _frameLaptopNames;
	vector<Point> _frameNumberSold;
	vector<Point> _framePage;
	vector<Point> _frameLaptopSpecs;
	vector<Point> _frameLaptopNameTitle;
	vector<Point> _frameNumberSoldTitle;
	vector<Point> _frameSales;

	DrawStats() {
		_menuChoice = 0;
		_page = 1;
		stats = Stats::instance();

		int x = (consoleWidth - 53) / 2 + 1;
		_frameMenu = { Point(x, _frameInstruction[1].y() + 2), Point(x + 52,_frameInstruction[1].y() + 6) };
		
		x = (consoleWidth - 70) / 2 + 1;
		_frameBestsellers = { Point(x, _frameInstruction[1].y() + 2), Point(x + 69, _frameInstruction[1].y() + 13) };
	
		x = (consoleWidth - 15) / 2 + 1;
		_frameMonths = { Point(x, _frameInstruction[1].y() + 2), Point(x + 16, _frameInstruction[1].y() + 15) };

		x = (consoleWidth - (62 + 15)) / 2 + 1;
		_frameLaptopNameTitle = { Point(x, _frameInstruction[1].y() + 3), Point(x + 61, _frameInstruction[1].y() + 5) };
		_frameNumberSoldTitle = { Point(_frameLaptopNameTitle[1].x() + 1, _frameLaptopNameTitle[0].y()), Point(_frameLaptopNameTitle[1].x() + 14,  _frameLaptopNameTitle[0].y() + 2) };
		_frameLaptopNames = { Point(x, _frameLaptopNameTitle[1].y() + 1), Point(x + 61, _frameLaptopNameTitle[1].y() + 12) };
		_frameNumberSold = { Point(_frameNumberSoldTitle[0].x(), _frameNumberSoldTitle[1].y() + 1), Point(_frameNumberSoldTitle[1].x(), _frameNumberSoldTitle[1].y() + 12) };
		
		_framePage = { Point(_frameLaptopNames[0].x() + 4, _frameLaptopNames[1].y() + 1), Point(_frameLaptopNames[0].x() + 12, _frameLaptopNames[1].y() + 1) };

		x = (consoleWidth - 62) / 2 + 1;
		_frameLaptopSpecs = { Point(x, _frameInstruction[1].y() + 3), Point(x + 61, _frameInstruction[1].y() + 15) }; //yEnd depends
	
		x = (consoleWidth - 33) / 2 + 1;
		_frameSales = { Point(x, _frameInstruction[1].y() + 3), Point(x + 32, _frameInstruction[1].y() + 6) };
	}
public:
	static shared_ptr<DrawStats> instance() {
		static shared_ptr<DrawStats> _instance(new DrawStats());
		return _instance;
	}

	void resetVariables();
	void drawFrameMenu();
	void drawFrameInstruction(int code);
	void drawFrameLaptopNameTitle();
	void drawFrameNumberTitle(wstring);
	void drawFrameLaptopNames();
	void drawFrameNumber();
	void drawFrameLaptopSpecs();
	void drawFramePage();
	void drawFrameMonths();
	void drawFrameSales();
	void drawAllFrames();
	void drawArrowLeft();
	void drawArrowRight();
	void clearArrowLeft();
	void clearArrowRight();

	//view both laptop names & number sold
	void viewLaptopsAndNumber(vector<pair<Laptop, int>>);

	int menuProcessing();
	int bestsellerProcessing();
	int runoutLaptopProcessing();
	int saleProcessing();
};