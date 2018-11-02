#include <iostream>
#include "Clement.h"
#include "Encryption.h"



bool Clement::keyServeur(std::string port, std::string key, std::string IV)
{

	SOCKET socket;

	ListenTo(socket, port);

	std::string message = keyAB;
	std::string mac = MAC(message, key, IV);
	if (mac == "") {
		std::cout << "Erreur Creation du MAC\n";
		closeSocket(socket);
		return false;
	}
	message += mac;
	message = Encrypt(message, key, IV);
	if (message == "") {
		std::cout << "Erreur Chiffrement\n";
		closeSocket(socket);
		return false;
	}

	std::cout << "\nMessage envoye: " << message << "\n\n";

	sendTo(socket, message);

	message = keyAB_MAC;
	mac = MAC(message, key, IV);
	if (mac == "") {
		std::cout << "Erreur Creation du MAC\n";
		closeSocket(socket);
		return false;
	}
	message += mac;
	message = Encrypt(message, key, IV);
	if (message == "") {
		std::cout << "Erreur Chiffrement\n";
		closeSocket(socket);
		return false;
	}

	std::cout << "\nMessage envoye: " << message << "\n\n";

	sendTo(socket, message);

	message = IVAB;
	mac = MAC(message, key, IV);
	if (mac == "") {
		std::cout << "Erreur Creation du MAC\n";
		closeSocket(socket);
		return false;
	}
	message += mac;
	message = Encrypt(message, key, IV);
	if (message == "") {
		std::cout << "Erreur Chiffrement\n";
		closeSocket(socket);
		return false;
	}

	std::cout << "\nMessage envoye: " << message << "\n\n";

	sendTo(socket, message);

	closeSocket(socket);
	return true;
}

Clement::Clement()
{
	CreateKey();
	CreateKeyMAC();
	CreateIV();
}


Clement::~Clement()
{
}

int Clement::run()
{
	InitialiseWinsock();

	if (!keyServeur(CAPort, AliceKey, AliceIV)) {
		CleanupWinsock();
		return -1;
	}
	if (!keyServeur(CBPort, BobKey, BobIV)) {
		CleanupWinsock();
		return -1;
	}

	CleanupWinsock();

	return 0;
}
