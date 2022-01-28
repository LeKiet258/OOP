#include<iostream>
#include<fstream>
#include<vector>
#include<typeinfo>

#include"Line.h"
#include"Tokenizer.h"
#include"Random.h"
#include"Circle.h"
#include"Rectangle.h"
#include"ShapeFactory.h"
#include"Square.h"

using namespace std;

const int totalShapes = ShapeFactory::totalShapes;
Random rng;

int main() {
	int n = rng.nextInt(5, 20);
	vector<IShape_ptr> shapes;
	ofstream fout("output.txt");

	//generate n shapes of either circle, line, rectangle
	for (int i = 0; i < n; ++i) {
		int type = rng.nextInt(totalShapes);
		shapes.push_back(ShapeFactory::create(type));
	}
	
	//write n shapes to output.txt
	fout << n << endl;
	for (int i = 0; i < n; ++i) {
		fout << shapes[i]->type() << ": " << shapes[i]->toString() << endl;
	}

	fout.close();

	//reset variables
	n = 0;
	shapes.clear();

	//read n shapes from output.txt and print to console
	ifstream fin("output.txt");
	string s;
	
	getline(fin, s);
	n = stoi(s);

	for (int i = 0; i < n; ++i) {
		getline(fin, s);
		vector<string> tokens = Tokenizer::split(s, ": ");
		IShape_ptr shape = ShapeFactory::parse(tokens[0], tokens[1]);

		shapes.push_back(shape);
	}

	for (auto item : shapes)
		cout << item->type() << ": " << item->toString() << endl;

	return 0;
}


