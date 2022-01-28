#pragma once
#include<iostream>
#include<string>
#include<vector>
#include"Utils.h"
#pragma warning(disable : 4996)

using namespace std;

class DateTime {
	friend wostream& operator<<(wostream&, DateTime&);
private:
	int _day;
	int _month;
	int _year;
public:
	DateTime(int = 0, int = 0, int = 0);

	void setDay(int d) { _day = d; };
	int day() { return _day; };
	void setMonth(int m) { _month = m; };
	int month() { return _month; };
	void setYear(int y) { _year = y; };
	int year() { return _year; };
	void setDate(int, int, int);

	static int currentDay();
	static int currentMonth();
	static int currentYear();
	static bool isLeapYear(int);
	wstring toString();
	
	//check if the random date is smaller than the date at the moment
	bool isValidNow();
	static DateTime parse(wstring line);
};