#pragma once
#include"Catalog.h"
#include"Draw.h"

class DrawCatalog : public Draw{
private:
	//inline static shared_ptr<DrawCatalog> _instance = 0;
	shared_ptr<Catalog> _catalog; //source of truth
	vector<Point> _frameBrand;
	vector<Point> _frameLaptop;
	vector<Point> _frameChangeBrand;
	vector<Point> _frameEdit;
	vector<Point> _frameLaptopSpecs;
	vector<Point> _frameField;
	vector<Point> _frameInput;
	int _brandChoice;
	int _laptopChoice;

	DrawCatalog() 
	{
		_catalog = Catalog::instance();
		_indent = 2;
		_brandChoice = _laptopChoice = 0;

		int x = _frameTitle[0].x();
		int y = _frameTitle[0].y();
				
		x = (consoleWidth - 22) / 2 + 1;
		_frameEdit = { Point(x, y + 11), Point(x + 21, y + 13) };

		x = (consoleWidth - 83) / 2 + 1;
		_frameBrand = { Point(x, y + 15), Point(x + 22, y + 34) };
		_frameLaptop = { Point(x + 24, y + 15), Point(x + 80, y + 34)};

		x = (consoleWidth - 82) / 2 + 1;
		_frameLaptopSpecs = { Point(x, y + 20),Point(x +81 , y + 32) };

		x = (consoleWidth - 73) / 2 + 1;
		_frameField = { Point(x, _frameInstruction[1].y() + 3), Point(x + 72,  _frameInstruction[1].y() + 5) };
		_frameInput = { Point(x,  _frameInstruction[1].y() + 6), Point(x + 72,  _frameInstruction[1].y() + 8) };
	}

public:
	static shared_ptr<DrawCatalog> instance() {
		static shared_ptr<DrawCatalog> _instance(new DrawCatalog());
		return _instance;
	}

	void resetVariables();
	//getters
	int brandChoice() { return _brandChoice; }
	vector<Point> frameBrandDisplay() { return _frameBrand; }
	vector<Point> frameLaptopDisplay() { return _frameLaptop; }

	void drawButtonUpLaptops();
	void drawButtonDownLaptops();
	void drawButtonUpBrand();
	void drawButtonDownBrand();
	void drawFrameField();
	void drawFrameInput();
	void drawFrameLaptopSpecs();
	void drawFrameBrands();
	void drawFrameLaptops();
	void drawInstruction(int code);
	
	void clearFrameLaptopsContent();
	void clearFrameField();
	void clearFrameInput();
	void clearFrameInstruction();
	void clearButtonUpBrand();
	void clearButtonDownBrand();
	void clearButtonDownLaptops();
	void clearButtonUpLaptops();
	void clearFrameBrandContent();
	void clearFrameSpecsContent();

	void viewBrands(int, int);
	void viewLaptops();

	int brandProcessing();
	int laptopsProcessing();
	int singleLaptopProcessing();

	//~DrawCatalog();
};