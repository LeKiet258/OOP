#pragma once
#include"Header.h"

class DateTime {
private:
	int _ngay, _thang, _nam;
public:
	DateTime(int a = 0, int b = 0, int c = 0): _ngay(a), _thang(b),_nam(c){}

	wstring toString() {
		wstringstream wss;
		wss << (_ngay < 10? L"0" : L"") << _ngay << L"/"
			<< (_thang < 10 ? L"0" : L"") << _thang << L"/" 
			<< _nam;
		return wss.str();
	}

};

class DateTimeMock {
private:
	int totalMonths[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	inline static DateTimeMock* _instance = 0;
public:
	DateTimeMock() { }

	DateTime next(int thang) {
		int nam = 2021;

		if (thang == 2)
			totalMonths[2] = 29;
		int ngay = Random::instance()->nextInt(1, totalMonths[thang]);
		return DateTime(ngay, thang, nam);
	}

	DateTime next() {
		int thang = Random::instance()->nextInt(1, 12);
		return next(thang);
	}

	~DateTimeMock() {
		wcout << L"DateTime deleted";
	}
};