#include <stdio.h>
#include <iostream>
#include "Encryption.h"


using std::cout;
using std::endl;
using std::string;
using std::array;


int main(int argc, char* argv[]) {

	string crypto = Encrypt("Ait-ce que Vincent est un genie?", "ley362", "jdkjds");

	cout << crypto << endl;
	cout << Decrypt(crypto, "ley362", "jd213he") << endl;

	getchar();
	return 0;
}