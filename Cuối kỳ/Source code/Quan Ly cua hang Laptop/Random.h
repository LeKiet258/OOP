#pragma once
#include<iostream>
#include<ctime>

using namespace std;

class Random {
private:
	//inline static Random* _instance = 0;
	inline static bool _seeded = false;
	Random(){ }
public:
	static shared_ptr<Random> instance() {
		static shared_ptr<Random> _instance(new Random());
		return _instance;
	}

	int nextInt() {
		if (!_seeded) {
			srand(time(NULL));
			_seeded = true;
		}

		return rand();
	}

	int nextInt(int ceiling) {
		if (!_seeded) {
			srand(time(NULL));
			_seeded = true;
		}

		return rand() % ceiling;
	}

	int nextInt(int left, int right) {
		if (!_seeded) {
			srand(time(NULL));
			_seeded = true;
		}

		return left + rand() % (right - left + 1);
	}
};

