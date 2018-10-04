#include "MAC.h"
#include "Utils.h"

using std::string;

string HashSimple(string message)
{
	int hashLength = 8;

	string hashCode = "";

	for (int i = 0; i < hashLength; i++) {
		hashCode += char(0);
	}
	while (message.length() % hashLength != 0) {
		message += char(0);
	}
	for (int i = 0; i < message.length(); i += hashLength) {
		hashCode = StringXOR(hashCode, message.substr(i, hashLength));
	}




	return hashCode;
}
