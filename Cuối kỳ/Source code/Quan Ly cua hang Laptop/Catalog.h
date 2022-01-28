#pragma once
#include"LaptopMock.h"
#include"ClasslessFunctions.h"

class Catalog {
private:
	vector<wstring> _brands;
	vector<vector<Laptop>> _laptops;
	//inline static Catalog* _instance = 0;

	Catalog(){
		_brands = LaptopMock::instance()->brands();
		vector<vector<wstring>> laptopNames = LaptopMock::instance()->laptopNames();

		for (int i = 0; i < _brands.size(); ++i) {
			vector<Laptop> l;

			for (int j = 0; j < laptopNames[i].size(); ++j) {
				Laptop lap = LaptopMock::instance()->next(_brands[i], laptopNames[i][j]);
				l.push_back(lap);
			}
			_laptops.push_back(l);
		}
	}
public:
	static shared_ptr<Catalog> instance() {
		static shared_ptr<Catalog> _instance(new Catalog());
		return _instance;
	}

	vector<wstring> brands() { return _brands; }
	wstring brand(int idx) { return _brands[idx]; }
	vector<Laptop> laptopsOfBrand(int idx);
	vector<wstring> laptopNames(int idx);
	int totalBrand() { return _brands.size(); }
	vector<vector<Laptop>> laptops() { return _laptops; }
	void setLaptop(int, int, Laptop);

	void removeBrand(int); //remove brand -> remove laptop of brand
	void changeBrand(int idx, wstring newName);
	void addBrand(wstring newName);
	void addLaptop(int idx, Laptop = Laptop());
	void removeLaptop(int brandIdx, int lapIdx);
	void removeLaptopOfBrand(int idx) { _laptops.erase(_laptops.begin() + idx); }
};