#include"Random.h"

bool Random::_seeded = false;

int Random::nextInt() {
	if (!_seeded) {
		srand(time(NULL));
		_seeded = true;
	}

	return rand();
}

int Random::nextInt(int ceiling) {
	if (!_seeded) {
		srand(time(NULL));
		_seeded = true;
	}

	return rand() % ceiling;
}

int Random::nextInt(int left, int right) {
	if (!_seeded) {
		srand(time(NULL));
		_seeded = true;
	}

	return left + rand() % (right - left + 1);
}