#pragma once
#include"Order.h"
#include"Random.h"
#include"Catalog.h"

class OrderMock {
private:
	FullNameMock _nameStore;
	DateTimeMock _dateTimeStore;
	vector<Laptop> _laptopsStore;

	OrderMock() {
		vector<vector<Laptop>> allLaptops = Catalog::instance()->laptops();
		for (int i = 0; i < allLaptops.size(); ++i) {
			for (int j = 0; j < allLaptops[i].size(); ++j)
				_laptopsStore.push_back(allLaptops[i][j]);
		}
	}
public:
	static shared_ptr<OrderMock> instance() {
		static shared_ptr<OrderMock> _instance(new OrderMock());
		return _instance;
	}

	Order next() {
		FullName customerName = _nameStore.next(Random::instance()->nextInt(2));
		DateTime date = _dateTimeStore.next();
		Laptop product = _laptopsStore[Random::instance()->nextInt(_laptopsStore.size())];
		wstring id = L"DH";
	
		for (int i = 0; i < 4; ++i) {
			wstring digit = to_wstring(Random::instance()->nextInt(10));
			id += digit;
		}

		return Order(id, customerName, date, product);
	}

	Order next(int month) {
		FullName customerName = _nameStore.next(Random::instance()->nextInt(2));
		DateTime date = _dateTimeStore.next(month);
		Laptop product = _laptopsStore[Random::instance()->nextInt(_laptopsStore.size())];
		wstring id = L"DH";

		for (int i = 0; i < 4; ++i) {
			wstring digit = to_wstring(Random::instance()->nextInt(10));
			id += digit;
		}

		return Order(id, customerName, date, product);
	}
};