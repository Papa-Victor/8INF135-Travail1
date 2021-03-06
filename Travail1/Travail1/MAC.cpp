#include <iostream>
#include "MAC.h"
#include "Utils.h"
#include "Encryption.h"

using std::string;

string HashSimple(string message)
{
	std::cout << "----------Log Hash----------\n";
	std::cout << "Input: \n\tMessage: " << message << std::endl;

	int hashLength = 4;

	string hashCode = "";

	//cr�e un bloc de taille 4 pour l'initialisation
	for (int i = 0; i < hashLength; i++) {
		hashCode += " ";
	}

	//s'assure que le message est divisible en bloc de hashlength
	while (message.length() % hashLength != 0) {
		message += " ";
	}
	for (int i = 0; i < message.length(); i += hashLength) {
		hashCode = StringXOR(hashCode, message.substr(i, hashLength));
	}

	std::cout << "Ouput: \n\tHash: " << hashCode << std::endl;
	std::cout << "----------Log Hash End----------\n";

	return hashCode;
}

//Cr�ation du MAC � partir du message et de la cl�
std::string MAC(std::string message, std::string key, std::string IV)
{
	std::cout << "----------Log MAC----------\n";
	std::cout << "Input:\n\tMessage: " << message << std::endl << "\tKey: " << key << std::endl << "\tIV: " << IV << std::endl;
	if (message.length() < key.length()) return "";

	string mac;

	mac = HashSimple(message);

	mac = Encrypt(mac, key, IV);


	std::cout << "Output\n\tMAC: " << mac << std::endl;
	std::cout << "----------Log MAC End----------\n";
	return mac;
}


//prend un message et un MAC et v�rifie s'ils correspondent
bool CompareMac(std::string message, std::string macReceived, std::string key, std::string IV)
{
	std::cout << "----------Log CompareMac----------\n";
	std::cout << "Input: \n\tMessage: " << message << std::endl << "\tMAC: " << macReceived << std::endl
	<< "\tKey: " << key << std::endl << "\tIV: " << IV << std::endl;
	
	string hashReceived = Decrypt(macReceived, key, IV);

	string hashMessage = HashSimple(message);

	std::cout << "Output\n\tIdentical :" << (hashReceived == hashMessage) << std::endl;
	std::cout << "----------Log CompareMac End----------\n";

	return hashReceived == hashMessage;
}
