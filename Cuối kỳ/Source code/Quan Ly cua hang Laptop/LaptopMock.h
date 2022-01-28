#pragma once
#include"Laptop.h"
#include"Random.h"

class LaptopMock {
private:
	vector<vector<wstring>> _laptops;
	vector<wstring> _CPUs;
	vector<int> _RAMs = { 4,6,8,32 };
	vector<double> _displays = { 13.3, 13.4, 13.5, 14, 15.6, 16, 16.1, 17, 17.3 };
	vector<wstring> _hardDisks;
	vector<wstring> _OSes = { L"Windows 10", L"Windows 10 Home Single Language", L"Windows 10 Pro for Workstations", L"Windows 10 Enterprise" };
	vector<wstring> _VGAs;
	
	//inline static LaptopMock* _instance = 0;
	LaptopMock() {
		locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);  // UTF-8
		wifstream fin_hangLaptop("hangLaptop.txt");
		wifstream fin_cpu("cpu.txt");
		wifstream fin_hardDisk("hardDisk.txt");
		wifstream fin_vga("vga.txt");
		wstring tmp;
		int n, m;

		fin_hangLaptop.imbue(loc);
		fin_cpu.imbue(loc);
		fin_hardDisk.imbue(loc);
		fin_vga.imbue(loc);

		//read hangLaptop.txt
		getline(fin_hangLaptop, tmp);
		n = stoi(tmp);
		for (int i = 0; i < n; ++i) {
			getline(fin_hangLaptop, tmp);
			_laptops.push_back({ tmp }); //get brand name

			getline(fin_hangLaptop, tmp);
			m = stoi(tmp);
			for (int j = 0; j < m; ++j) {
				getline(fin_hangLaptop, tmp);
				_laptops[i].push_back(tmp); //get laptop's name
			}
		}

		//read cpu.txt
		getline(fin_cpu, tmp);
		n = stoi(tmp);
		for (int i = 0; i < n; ++i) {
			getline(fin_cpu, tmp);
			_CPUs.push_back(tmp);
		}

		//read hardDisk.txt
		getline(fin_hardDisk, tmp);
		n = stoi(tmp);
		for (int i = 0; i < n; ++i) {
			getline(fin_hardDisk, tmp);
			_hardDisks.push_back(tmp);
		}

		//read vga.txt
		getline(fin_vga, tmp);
		n = stoi(tmp);
		for (int i = 0; i < n; ++i) {
			getline(fin_vga, tmp);
			_VGAs.push_back(tmp);
		}
	}
public:
	static shared_ptr<LaptopMock> instance() {
		static shared_ptr<LaptopMock> _instance(new LaptopMock());
		return _instance;
	}

	Laptop next(wstring brand, wstring laptopName) {
		int i = Random::instance()->nextInt(_CPUs.size());
		wstring CPU = _CPUs[i];

		i = Random::instance()->nextInt(_RAMs.size());
		int ram = _RAMs[i];

		i = Random::instance()->nextInt(_displays.size());
		double display = _displays[i];

		i = Random::instance()->nextInt(_hardDisks.size());
		wstring hardDisk = _hardDisks[i];

		i = Random::instance()->nextInt(_OSes.size());
		wstring os = _OSes[i];

		i = Random::instance()->nextInt(_VGAs.size());
		wstring vga = _VGAs[i];

		int price = Random::instance()->nextInt(8500, 30000) * 1000;
		double weight = Random::instance()->nextInt(1, 3) * 1.0 + Random::instance()->nextInt(10) * 1.0 / 10.0;
		int amount = Random::instance()->nextInt(1, 30);

		Laptop res(laptopName, brand, CPU, ram, display, hardDisk, weight, price, os, vga, amount);
		return res;
	}

	Laptop next() {
		int i1 = Random::instance()->nextInt(_laptops.size());
		int i2 = Random::instance()->nextInt(1, _laptops[i1].size() - 1);

		wstring brand(_laptops[i1][0]);
		wstring name = _laptops[i1][i2];
		return next(brand, name);
	}

	vector<vector<wstring>> laptops() {	return _laptops; }

	vector<wstring> brands() {
		vector<wstring> res;
		for (int i = 0; i < _laptops.size(); ++i)
			res.push_back(_laptops[i][0]);
		return res;
	}

	vector<vector<wstring>> laptopNames() {
		vector<vector<wstring>> res;
		for (int i = 0; i < _laptops.size(); ++i) {
			vector<wstring> tmp(_laptops[i].begin() + 1, _laptops[i].end());
			res.push_back(tmp);
		}
		return res;
	}

};