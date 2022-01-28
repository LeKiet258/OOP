#include"Catalog.h"

vector<Laptop> Catalog::laptopsOfBrand(int idx) {
	return _laptops[idx];
}

//the brand must exists in current products (return true); otherwise, the function returns false
void Catalog::removeBrand(int idx) {
	_brands.erase(_brands.begin() + idx);
}

void Catalog::changeBrand(int brandi, wstring newName) {
	_brands[brandi] = newName;
	for (int i = 0; i < _laptops[brandi].size(); ++i) {
		_laptops[brandi][i].setBrand(newName);
	}
}

void Catalog::addBrand(wstring newName) {
	_brands.push_back(newName);
}

vector<wstring> Catalog::laptopNames(int idx) {
	vector<wstring> res;
	for (int i = 0; i < _laptops[idx].size(); ++i) {
		res.push_back(_laptops[idx][i].name());
	}
	return res;
}


void Catalog::addLaptop(int idx, Laptop laptop) {
	if (idx == - 1) //push_back
		_laptops.push_back({  });
	else
		_laptops[idx].push_back(laptop);
}

void Catalog::removeLaptop(int brandi, int lapi) {
	_laptops[brandi].erase(_laptops[brandi].begin() + lapi);
}

void Catalog::setLaptop(int brandi, int laptopi, Laptop lap) {
	_laptops[brandi][laptopi] = lap;
}

