#include"Random.h"

Random* Random::instance() {
	if (instance == 0)
		_instance = new Random();
	return _instance;
}

int Random::nextIntInternal() {
	if (!_seeded) {
		srand(time(NULL));
		_seeded = true;
	}

	return rand();
}

int Random::nextIntInternal(int ceiling) {
	if (!_seeded) {
		srand(time(NULL));
		_seeded = true;
	}

	return rand() % ceiling;
}

int Random::nextIntInternal(int left, int right) {
	if (!_seeded) {
		srand(time(NULL));
		_seeded = true;
	}

	return left + rand() % (right - left + 1);
}

int Random::nextInt() { return instance()->nextIntInternal(); }
int Random::nextInt(int ceiling) { return instance()->nextIntInternal(ceiling); }
int Random::nextInt(int a, int b) { return instance()->nextIntInternal(a, b); }
