#pragma once
#include"FullName.h"
#include"Random.h"

class FullNameMock {
private:
	vector<wstring> _ho;
	vector<wstring> _tenDemNu;
	vector<wstring> _tenDemNam;
	vector<wstring> _tenNu;
	vector<wstring> _tenNam;
public:
	FullNameMock() {
		locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);  // UTF-8
		wifstream fin_ho("ho.txt");
		wifstream fin_tenDemNu("tenDemNu.txt");
		wifstream fin_tenDemNam("tenDemNam.txt");
		wifstream fin_tenNu("tenNu.txt");
		wifstream fin_tenNam("tenNam.txt");

		fin_ho.imbue(loc);
		fin_tenDemNu.imbue(loc);
		fin_tenDemNam.imbue(loc);
		fin_tenNu.imbue(loc);
		fin_tenNam.imbue(loc);

		wstring tmp;

		while (!fin_ho.eof()) {
			getline(fin_ho, tmp);
			_ho.push_back(tmp);
		}

		while (!fin_tenDemNam.eof()) {
			getline(fin_tenDemNam, tmp);
			_tenDemNam.push_back(tmp);
		}

		while (!fin_tenDemNu.eof()) {
			getline(fin_tenDemNu, tmp);
			_tenDemNu.push_back(tmp);
		}
		while (!fin_tenNu.eof()) {
			getline(fin_tenNu, tmp);
			_tenNu.push_back(tmp);
		}
		while (!fin_tenNam.eof()) {
			getline(fin_tenNam, tmp);
			_tenNam.push_back(tmp);
		}

	}

	FullName next(bool male = true) {
		int i = Random::instance()->nextInt(_ho.size());
		wstring ho = _ho[i];
		wstring tenDem, ten;

		if (male) {
			i = Random::instance()->nextInt(_tenDemNam.size());
			tenDem = _tenDemNam[i];
			i = Random::instance()->nextInt(_tenNam.size());
			ten = _tenNam[i];
		}
		else {
			i = Random::instance()->nextInt(_tenDemNu.size());
			tenDem = _tenDemNu[i];
			i = Random::instance()->nextInt(_tenNu.size());
			ten = _tenNu[i];
		}

		FullName res(ho, tenDem, ten);
		return res;
	}
};