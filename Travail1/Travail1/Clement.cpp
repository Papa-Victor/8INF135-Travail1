#include <iostream>
#include "Clement.h"
#include "Encryption.h"



bool Clement::keyServeur(std::string port, std::string key, std::string nonce)
{

	SOCKET socket;

	ListenTo(socket, port);

	std::string message = keyAB;
	std::string mac = MAC(message, key, nonce);
	if (mac == "") {
		std::cout << "Erreur Creation du MAC\n";
		closeSocket(socket);
		return false;
	}
	message += mac;
	message = Encrypt(message, key, nonce);
	if (message == "") {
		std::cout << "Erreur Chiffrement\n";
		closeSocket(socket);
		return false;
	}

	sendTo(socket, message);

	message = nonceAB;
	mac = MAC(message, key, nonce);
	if (mac == "") {
		std::cout << "Erreur Creation du MAC\n";
		closeSocket(socket);
		return false;
	}
	message += mac;
	message = Encrypt(message, key, nonce);
	if (message == "") {
		std::cout << "Erreur Chiffrement\n";
		closeSocket(socket);
		return false;
	}

	sendTo(socket, message);

	closeSocket(socket);
	return true;
}

Clement::Clement()
{
	CreateKey();
	CreateNonce();
}


Clement::~Clement()
{
}

int Clement::run()
{
	InitialiseWinsock();

	if (!keyServeur(CAPort, AliceKey, AliceNonce)) {
		CleanupWinsock();
		return -1;
	}
	if (!keyServeur(CBPort, BobKey, BobNonce)) {
		CleanupWinsock();
		return -1;
	}

	CleanupWinsock();

	return 0;
}
