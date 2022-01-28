#pragma once
#include"Catalog.h"
#include"OrderFactory.h"

class Stats {
private:
	//inline static Stats* _instance = 0;

	Stats() { }
public:
	static shared_ptr<Stats> instance() {
		static shared_ptr<Stats> _instance(new Stats());
		return _instance;
	}

	unsigned long long revenue(int month) {
		vector<Order> ordersMonth = OrderFactory::instance()->ordersByMonth(month);
		unsigned long long res = 0;

		for (auto order : ordersMonth) 
			res += order.price();
		return res;
	}

	unsigned long long profit(int month) {
		vector<Order> ordersMonth = OrderFactory::instance()->ordersByMonth(month);
		unsigned long long res = 0;
		for (auto order : ordersMonth)
			res += order.product().price();
		res = revenue(month) - res;
		return res;
	}
	
	vector<pair<Laptop, int>> bestsellersPrevMonth() {
		time_t t = time(0);
		tm* now = localtime(&t);
		int currentMonth = now->tm_mon + 1;
		int prevMonth = currentMonth == 1 ? 12 : currentMonth - 1;
		vector<pair<Laptop, int>> frequency = OrderFactory::instance()->numberSold(prevMonth);
		vector<pair<Laptop, int>> res;

		for (auto it = frequency.begin(); it != frequency.end(); ++it) {
			if (it->second > 1)
				res.push_back(make_pair(it->first, it->second + 7));
		}
		return res;
	}

	vector<Laptop> under10() {
		vector<vector<Laptop>> allLaptops = Catalog::instance()->laptops();
		vector<Laptop> res;

		for (int i = 0; i < allLaptops.size(); ++i) {
			for (int j = 0; j < allLaptops[i].size(); ++j) {
				Laptop lap = allLaptops[i][j];
				if (lap.amount() < 10 && lap.amount() > 0)
					res.push_back(lap);
			}
		}
		return res;
	}
};