#ifndef ENCRYPTION_H
#define ENCRYPTION_H
#include <stdio.h>
#include <iostream>
#include "base64.h"
#include "Utils.h"

using std::cout;
using std::endl;
using std::string;
//Fonction d'encryption

void Encrypt(string message, string key) {
	string message64 = base64_encode(reinterpret_cast<unsigned const char*>(message.c_str()), message.length());
	cout << message64 << endl;
}






#endif ENCRYPTION_H