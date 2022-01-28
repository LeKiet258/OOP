#pragma once
#include"ClasslessFunctions.h"
#include"FullNameMock.h"
#include"DateTime.h"
#include"Laptop.h"
#include"Tokenizer.h"

class Order {
private:
	wstring _orderId;
	FullName _customerName;
	DateTime _date;
	Laptop _product;
	int _price;
	vector<vector<wstring>> _otherDetails;
public:

	Order(wstring id, FullName fn, DateTime dt, Laptop product) :
		_orderId(id), _customerName(fn), _date(dt), _product(product)
	{ 
		_price = 1.1 * _product.price();
		_otherDetails = { };
	}

	wstring id() { return _orderId; }

	int price() { return _price; }

	Laptop product() { return _product; }

	int totalDetails() { return 4 + _otherDetails.size() + _product.totalProperties() - 1; }

	void changeDetail(int idx, wstring val) {
		if (idx == 0)
			_orderId = val;
		else if (idx == 1) {
			if (val != L"") {
				vector<wstring> tokens = Tokenizer::split(val, L" ");
				if (tokens.size() == 2)
					_customerName = FullName(tokens[0], L"", tokens[1]);
				else if (tokens.size() == 3)
					_customerName = FullName(tokens[0], tokens[1], tokens[2]);
			}
			else
				_customerName = FullName(); //empty name
		}
		else if (idx == 2) {
			int day = stoi(val.substr(0, 2));
			int month = stoi(val.substr(3, 2));
			int year = stoi(val.substr(6, 4));
			_date = DateTime(day, month, year);
		}
		else if (3 <= idx && idx <= 12)  //right constraint: _price
			_product.changeSpec(idx - 3, val);	
		if (_product.otherSpecs().empty()) {
			if(idx == 13)
				_price = val == L"" ? 0 : stoi(val);
			else if (idx >= 14) {
				idx -= 14;
				if (val != L"") _otherDetails[idx][1] = val;
				else _otherDetails.erase(_otherDetails.begin() + idx);
			}
		}
		else {
			if (idx >= 13 && idx <= 13 + _product.otherSpecs().size())
				_product.changeSpec(idx - 2, val);
			else if (idx == _product.otherSpecs().size() + 14)
				_price = val == L"" ? 0 : stoi(val);
			else if (idx >= _product.otherSpecs().size() + 15) {
				idx -= (_product.otherSpecs().size() + 15);
				if (val != L"") _otherDetails[idx][1] = val;
				else _otherDetails.erase(_otherDetails.begin() + idx);
			}
		}
	}

	wstring orderId() { return _orderId; }

	vector<vector<wstring>> toString() {
		vector<vector<wstring>> res;
		res.push_back({ L"Mã đơn hàng", _orderId });
		res.push_back({ L"Tên khách hàng", _customerName.toString() });
		res.push_back({ L"Ngày tạo", _date.toString() });
		
		vector<vector<wstring>> specs = _product.toString();
		specs.erase(specs.begin() + 10); //remove 'amount' property
		res.insert(res.end(), specs.begin(), specs.end());
		
		res.push_back({ L"Trả phí (bao gồm VAT)" , formattedPrice(_price) + L" VND"});

		for (int i = 0; i < _otherDetails.size(); ++i) 
			res.push_back(_otherDetails[i]);

		return res;
	}

	void pushBackDetail(wstring field, wstring val) {
		_otherDetails.push_back({ field, val });
	}
};

