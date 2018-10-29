#include <stdio.h>
#include <iostream>
#include <string>
#include <array>
#include "Encryption.h"
#include "MAC.h"
#include "Utils.h"
#include "Alice.h"
#include "Bob.h"

using std::cout;
using std::endl;
using std::string;
using std::array;

//Les nonces sont de longs de 4 charactères (4 octets)
//Les MAC sont donc longs de 8 charactères (8 octets) 

int main(int argc, char* argv[]) {
	cout << argv[1] << endl;
	if (argc == 2) {
		if ((string)argv[1] == "-a") {
			Alice a;
			a.run();
		}
		else if ((string)argv[1] == "-b") {
			Bob b;
			b.run();
		}
	}
	else {
		cout << "pas assez d'arg" << endl;
	}


	getchar();
	return 0;
}