#include<iostream>
#include <io.h>    //_setmode()
#include <fcntl.h> //_O_WTEXT

#include<FullNameMock.h>
#include<TelephoneMock.h>

using namespace std;

int main() {
	_setmode(_fileno(stdout), _O_WTEXT); //needed for output

	FullNameMock nameStore;
	TelephoneMock telStore;
	Random rng;

	wcout << "\t10 random names:\n";
	for (int i = 0; i < 10; ++i) {
		bool gender = rng.nextInt(2);
		FullName fullName = nameStore.next(gender);

		wcout << fullName << endl;
	}

	wcout << "\n\t10 random telephones:\n";
	for (int i = 0; i < 10; ++i) {
		Telephone tel = telStore.next();
		wcout << tel << endl;
	}

	return 0;
}
