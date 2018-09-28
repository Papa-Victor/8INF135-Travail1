#include <stdio.h>
#include <iostream>
#include "Encryption.h"


using std::cout;
using std::endl;
using std::string;
using std::array;


int main(int argc, char* argv[]) {

	cout << Encrypt("Antoine Est Un Beau Bonhomme", "kdu651", "lapo") << endl;

	getchar();
	return 0;
}