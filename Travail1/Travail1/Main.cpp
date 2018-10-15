#include <stdio.h>
#include <iostream>
#include <string>
#include <array>
#include "Encryption.h"
#include "MAC.h"
#include "Utils.h"


using std::cout;
using std::endl;
using std::string;
using std::array;

//Les nonces sont de longs de 4 charactères (4 octets)
//Les MAC sont donc longs de 16 charactères (16 octets) 

int main(int argc, char* argv[]) {

	string message = "MessageTest";
	string key = KeyGenerator(4);
	string nonce = KeyGenerator(4);
	string mac = MAC(message, key, nonce);
	message += mac;

	string messaceCon = "";
	string macCon = "";

	ConvertMessage(message, messaceCon, macCon);
	cout << message << endl;
	cout << messaceCon << " " << macCon << endl;


	getchar();
	return 0;
}