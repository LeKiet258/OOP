#pragma once
#include"Header.h"
#include"ClasslessFunctions.h"

class Laptop {
	friend bool operator<(const Laptop& lap1, const Laptop& lap2) {
		return lap1._amount < lap2._amount;
	}
private: //>=11 properties
	wstring _brand;
	wstring _name;
	wstring _cpu; //core
	int _ram;
	double _display; //inch
	wstring _hardDisk;
	double _weight;
	wstring _os; //operating system
	wstring _vga;
	int _price;
	int _amount; //the number of laptops of the same type in stock 
	vector<vector<wstring>> _otherSpecs; //ex: Battery: 2-3 cells
public:
	Laptop() {
		_brand = _name = _cpu = _hardDisk = _os = _vga = L"";
		_ram = _price = _amount = 0;
		_weight = _display = 0.0;
		//_otherSpecs = {};
	}
	Laptop(wstring name, wstring brand, wstring cpu, int ram, double displ, wstring hd, double w, int pr, wstring os, wstring vga, int amount) :
		_name(name), _brand(brand), _cpu(cpu), _ram(ram), _display(displ), _hardDisk(hd),_weight(w), _price(pr), _os(os), _vga(vga), _amount(amount)
	{}

	wstring name() { return _name; }
	void setBrand(wstring brand) { _brand = brand; }
	void addSpec(vector<wstring> specs) { _otherSpecs.push_back(specs); }
	vector<vector<wstring>> otherSpecs() { return _otherSpecs; }
	int totalProperties() { return 11 + _otherSpecs.size(); }
	int price() { return _price; }
	int amount() { return _amount; }

	void changeSpec(int idx, wstring val) {
		if (idx >= 11) {
			idx = idx % 11;
			if (val != L"") 
				_otherSpecs[idx][1] = val;
			else
				_otherSpecs.erase(_otherSpecs.begin() + idx);
		}
		else {
			switch(idx){
			case 0:
				_brand = val;
				break;
			case 1:
				_name = val;
				break;
			case 2:
				_cpu = val;
				break;
			case 3:
				_ram = val != L""? stoi(val) : 0;
				break;
			case 4:
				_display = val != L"" ? stof(val) : 0;
				break;
			case 5:
				_hardDisk = val;
				break;
			case 6:
				_weight = val != L"" ? stof(val) : 0;
				break;
			case 7:
				_os = val;
				break;
			case 8:
				_vga = val;
				break;
			case 9:
				_price = val != L"" ? stoi(val) : 0;
				break;
			case 10:
				_amount = val != L""? stoi(val) : 0;
				break;
			}
		}
	}

	bool removeSpecs(int idx) {
		if (idx == 0 || idx == 1)
			return false;
		if (idx == 2)
			_cpu = L"";
		else if (idx == 3)
			_ram = 0;
		else if (idx == 4)
			_display = 0.0;
		else if (idx == 5)
			_hardDisk = L"";
		else if (idx == 6)
			_weight = 0.0;
		else if (idx == 7)
			_os = L"";
		else if (idx == 8)
			_vga = L"";
		else if (idx == 9)
			_price = 0;
		else if (idx == 10)
			_amount = 0;
		else if (idx > 10) {
			idx = idx % 11;
			_otherSpecs.erase(_otherSpecs.begin() + idx);
		}

		return true;
	}

	vector<vector<wstring>> toString() {
		vector<vector<wstring>> res;
		wstringstream wss;

		res.push_back({ L"Hãng sản xuất", _brand });
		res.push_back({ L"Tên sản phẩm", _name });
		res.push_back({ L"CPU", _cpu});
		res.push_back({ L"RAM", (_ram == 0? L"" : to_wstring(_ram)) + L" GB" });
		
		wss << std::defaultfloat << _display;
		res.push_back({ L"Kích thước màn hình", _display == 0? L"" : wss.str() + L" inch"});
		wss.str(L"");

		res.push_back({ L"Ổ cứng", _hardDisk });

		wss << std::defaultfloat << _weight;
		res.push_back({ L"Trọng lượng", (_weight == 0 ? L"" : wss.str()) + L" kg" });
		wss.str(L"");

		res.push_back({ L"Hệ điều hành", _os });
		res.push_back({ L"Card", _vga });
		res.push_back({L"Giá", formattedPrice(_price) + L" VND"});
		res.push_back({L"Số lượng trong kho", _amount == 0? L"" : to_wstring(_amount)});

		for (int i = 0; i < _otherSpecs.size(); ++i) 
			res.push_back(_otherSpecs[i]);
			
		return res;
	}
};