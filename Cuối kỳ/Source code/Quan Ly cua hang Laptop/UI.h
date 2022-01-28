#pragma once
#include"Rectangle.h"
#include"DrawCatalog.h"
#include"DrawOrder.h"
#include"DrawStats.h"
#include"Draw.h"

class UI {
private:
	//inline static UI* _instance = 0;
	vector<wstring> _bigTitle;
	vector<Point> _frameBigTitle;
	vector<Point> _frameMenu;
	int _menuChoice;
	
	UI(){
		//source: https://patorjk.com/software/taag/#p=display&f=Graffiti&t=Type%20Something%20
		_bigTitle.push_back(L"         ___                 _");
		_bigTitle.push_back(L"  _____ (__ )         _     ( )                  _                 _               ");
		_bigTitle.push_back(L" / ____| (_/_        | |     \\|                 | |               | |             ");
		_bigTitle.push_back(L"| |    _   ) )__ _   | |__   __ _ _ __   __ _   | |     __ _ _ __ | |_ ___  _ __  ");
		_bigTitle.push_back(L"| |   | | | |/ _` |  | '_ \\ / _` | '_ \\ / _` |  | |    / _` | '_ \\| __/ _ \\| '_ \\ ");
		_bigTitle.push_back(L"| |___| |_| | (_| |  | | | | (_| | | | | (_| |  | |___| (_| | |_) | || (_) | |_) |  ");
		_bigTitle.push_back(L" \\____ \\__,_|\\__,_|  |_| |_|\\__,_|_| |_|\\__, |  |______\\__,_| .__/ \\__\\___/| .__/ ");
		_bigTitle.push_back(L"                                         __/ |              | |            | |    ");
		_bigTitle.push_back(L"                                        |___/               |_|            |_|    ");
	
		int x = (consoleWidth - longestStringLength(_bigTitle)) / 2 + 1;
		int y = (consoleHeight - (_bigTitle.size() + 2 + 6)) / 2 + 1;
		_frameBigTitle = { Point(x, y), Point(x + longestStringLength(_bigTitle), y + _bigTitle.size()) };
		
		x = _frameBigTitle[0].x() + (longestStringLength(_bigTitle) - 25) / 2 + 1;
		_frameMenu = { Point(x, _frameBigTitle[1].y() + 2), Point(x + 25, _frameBigTitle[1].y() + 7) };
	
		_menuChoice = 0;
	}
public:
	static shared_ptr<UI> instance() {
		static shared_ptr<UI> _instance(new UI());
		return _instance;
	}

	void drawFrameMenu();
	void drawFrameBigTitle();
	
	int menu();
	void catalogProcessing();
	void orderProcessing();
	void statsProcessing();
	void mainProcessing();
};