#include <stdio.h>
#include <iostream>
#include <string>
#include <array>
#include "Encryption.h"
#include "MAC.h"


using std::cout;
using std::endl;
using std::string;
using std::array;


int main(int argc, char* argv[]) {

	//cout << HashSimple("s") << endl;

	string crypto = Encrypt("kjsdhkfhsdkjfh", "l0po", "jfkrasw");
	
	cout << crypto << endl;

	cout << Decrypt(crypto, "l0po", "jfkrasw") << endl;

	getchar();
	return 0;
}