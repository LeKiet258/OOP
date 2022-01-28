#include<iostream>
#include <io.h>
#include <fcntl.h>
#include"Order.h"
#include"LaptopMock.h"
#include"UI.h"

using namespace std;

int main(int argc, char** argv) {
	_setmode(_fileno(stdin), _O_WTEXT); 
	_setmode(_fileno(stdout), _O_WTEXT);
	nocursortype();

	//UI::instance()->menu();
	//UI::instance()->catalogProcessing();
	//UI::instance()->orderProcessing();
	//UI::instance()->statsProcessing();
	UI::instance()->mainProcessing();


	wcout << L"\n\n";
	return 0;
}