#include <stdio.h>
#include <iostream>
#include <string>
#include <array>
#include "Encryption.h"
#include "MAC.h"
#include "Utils.h"
#include "Alice.h"
#include "Bob.h"
#include "Clement.h"

using std::cout;
using std::endl;
using std::string;
using std::array;

//Les IVs sont de longs de 4 charactères (4 octets)
//Les MAC sont donc longs de 16 charactères (16 octets) 

int main(int argc, char* argv[]) {
	if (argc == 2) {
		if ((string)argv[1] == "-a") {
			Alice a;
			return a.run();
		}
		else if ((string)argv[1] == "-b") {
			Bob b;
			return b.run();
		}
		else if ((string)argv[1] == "-c") {
			Clement c;
			return c.run();
		}
		else{
			cout << "Argument invalide" << endl;
		}		
	}
	else {
		cout << "Erreur de structure: Travail1.exe <argument>" << endl;
	}
	return 0;
}