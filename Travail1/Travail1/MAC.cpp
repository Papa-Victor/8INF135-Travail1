#include "MAC.h"
#include "Utils.h"
#include "Encryption.h"

using std::string;

string HashSimple(string message)
{
	int hashLength = 4;

	string hashCode = "";

	for (int i = 0; i < hashLength; i++) {
		hashCode += " ";
	}
	while (message.length() % hashLength != 0) {
		message += " ";
	}
	for (int i = 0; i < message.length(); i += hashLength) {
		hashCode = StringXOR(hashCode, message.substr(i, hashLength));
	}

	return hashCode;
}

std::string MAC(std::string message, std::string key, std::string nonce)
{
	if (message.length() < key.length()) return "";

	string mac;

	mac = HashSimple(message);

	mac = Encrypt(mac, key, nonce);

	return mac;
}

bool CompareMac(std::string message, std::string macReceived, std::string key, std::string nonce)
{
	string hashReceived = Decrypt(macReceived, key, nonce);

	string hashMessage = HashSimple(message);

	return hashReceived == hashMessage;
}
