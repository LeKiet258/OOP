#pragma once
#include"Random.h"

class Dice {
private:
	Random _rng;
public:
	int roll() { return _rng.nextInt(1, 6); }
};