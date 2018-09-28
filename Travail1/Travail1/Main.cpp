#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include "Encryption.h"


using std::cout;
using std::endl;
using std::string;
using std::array;


int main(int argc, char* argv[]) {

	for (int i = 0; i < 25; i++) {
		string key = KeyGenerator();

		string crypto = Encrypt("William est un tres beau garcon", key, "09l3");

		cout << crypto << endl;
	}

	//cout << Decrypt(crypto, key, "09l3") << endl;


	getchar();
	return 0;
}