#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include "Encryption.h"


using std::cout;
using std::endl;
using std::string;
using std::array;


int main(int argc, char* argv[]) {

	string crypto = Encrypt("il estait", "55F134B6859AD", "09l3");

	cout << crypto << endl;
	cout << Decrypt(crypto, "55F134B6859AD", "09l3") << "k" << endl;

	getchar();
	return 0;
}