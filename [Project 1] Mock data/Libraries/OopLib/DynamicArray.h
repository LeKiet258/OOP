#pragma once
#include<iostream>
#pragma warning(disable : 4996)

using namespace std;

template <class Ty>
class DynamicArray {
private:
	Ty* _a;
	int _currentSize;
	int _bufferSize;
public:
	//default constructor
	DynamicArray(int initSize = 100) {
		_bufferSize = initSize;
		_currentSize = 0;
		_a = new Ty[_bufferSize];
	}

	//copy constructor
	DynamicArray(const DynamicArray& other) {
		_a = new Ty[other._bufferSize];
		memcpy(_a, other._a, other._bufferSize * sizeof(Ty));
		_currentSize = other._currentSize;
		_bufferSize = other._bufferSize ;
	}

	//assignment operator
	DynamicArray& operator=(const DynamicArray& other) {
		_a = new Ty[other._bufferSize];
		memcpy(_a, other._a, other._bufferSize * sizeof(Ty));
		_currentSize = other._currentSize;
		_bufferSize = other._bufferSize;

		return *this;
	}

	int size() { return _currentSize; }

	Ty& getAt(int i) {
		if (i >= _currentSize)
			throw exception("Index out of bound");
		return _a[i];
	}

	void push_back(Ty item) {
		const int OFFSET = 5;

		if (_currentSize >= _bufferSize) {
			_bufferSize += OFFSET;
			Ty* tmp = new Ty[_bufferSize];

			//copy _a to tmp
			memcpy(tmp, _a, _currentSize * sizeof(Ty));
			//delete old _a
			delete[] _a;
			//assign tmp to _a
			_a = tmp;
		}

		_a[_currentSize] = item; 
		++_currentSize;
	}

	//get last element
	Ty back() { return getAt(_currentSize - 1); }

	Ty& operator[] (int index) { return getAt(index); }

	//destructor
	~DynamicArray() {
		if (_a != NULL)
			delete[] _a;
	}

};