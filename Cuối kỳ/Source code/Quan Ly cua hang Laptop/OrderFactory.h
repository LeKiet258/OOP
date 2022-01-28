#pragma once
#include"OrderMock.h"

class OrderFactory {
private:
	//inline static OrderFactory* _instance = 0;
	int _totalOrders; //orders of 12 months
	vector<vector<Order>> _orders; //12 months
	
	OrderFactory() {
		_orders.push_back({ }); //month "0"

		for (int month = 1; month <= 12; ++month) {
			int orderSingleMonth = Random::instance()->nextInt(30, 1000);
			_totalOrders += orderSingleMonth;
			vector<Order> tmp;

			for (int j = 0; j < orderSingleMonth; ++j) 
				tmp.push_back(OrderMock::instance()->next(month));
			_orders.push_back(tmp);
		}
	}

public:
	static shared_ptr<OrderFactory> instance() {
		static shared_ptr<OrderFactory> _instance(new OrderFactory());
		return _instance;
	}

	vector<Order> ordersByMonth(int month) { return _orders[month]; }
	
	void updateOrder(int month, int orderi, Order newOrd) {
		_orders[month][orderi] = newOrd;
	}

	void removeOrder(int monthi, int orderi) {
		_orders[monthi].erase(_orders[monthi].begin() + orderi);
		_totalOrders--;
	}

	vector<pair<Laptop, int>> numberSold(int month) {
		set<Laptop> setLaptops;
		multimap<int, Laptop, greater<int>> _res;
		vector<pair<Laptop, int>> res;
		int idx = 0;

		for (auto item : _orders[month])
			setLaptops.insert(item.product());
		vector<int> freq(setLaptops.size(), 0);

		for (auto itr = setLaptops.begin(); itr != setLaptops.end(); itr++) {
			Laptop lap = *itr;
			for (auto order : _orders[month]) {
				if (lap.name() == order.product().name())
					freq[idx]++;
			}
			_res.insert(make_pair( freq[idx], lap ));
			idx++;
		}

		for (auto it = _res.begin(); it != _res.end(); ++it) 
			res.push_back(make_pair(it->second, it->first));

		return res;
	}
};