#include <stdio.h>
#include <iostream>
#include "Encryption.h"


using std::cout;
using std::endl;
using std::string;

int main(int argc, char* argv[]) {

	std::array<int, 10> test = { 1,2,3,4,5,6,7,8,9,10 };

	RotateArrayRight(test, 5);
	for (int i = 0; i < sizeof(test) / sizeof(int); i++) {
		cout << test[i] << endl;
	}


	getchar();
	return 0;
}