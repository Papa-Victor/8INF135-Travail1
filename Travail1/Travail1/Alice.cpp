#include <iostream>
#include "Encryption.h"
#include "Alice.h"
#include "IP.h"



bool Alice::ClientBob()
{
	SOCKET socketBob;

	while (!connectTo(socketBob, IP_Bob, ABPort)){}

	int iResult;
	std::string message, mac;
	bool envoi = true;

	std::cout << "Saisir un message. Saisir \"Exit\" pour terminer la communication.\n";
	std::getline(std::cin, message);
	while ((message.length() < bobKeyMAC.length() || message.length() > 128) && message != "Exit") {
		std::cout << "Taille du message invalide, message doit etre de " << bobKeyMAC.length()<< " a 128 caracteres\n";
		std::cout << "Saisir un message. Saisir \"Exit\" pour terminer la communication.\n";
		std::getline(std::cin, message);
	}
	while (message != "Exit") {
		iResult = send(socketBob, (char*)&envoi, sizeof(bool), 0);
		if (iResult < 0) {
			printf("Client : send failed with error: %d\n", WSAGetLastError());
			return false;
		}

		mac = MAC(message, bobKeyMAC, IV);
		if (mac == "") {
			std::cout << "Erreur Creation du MAC\n";
			closeSocket(socketBob);
			return false;
		}
		message += mac;

		message = Encrypt(message, bobKey, IV);

		std::cout << "\nMessage envoye: " << message << "\n\n";

		sendTo(socketBob, message);
		std::cout << "Saisir un message. Saisir \"Exit\" pour terminer la communication.\n";
		std::getline(std::cin, message);
		while (message.length() < bobKeyMAC.length() || message.length() > 128) {
			std::cout << "Taille du message invalide, message doit etre de 4 a 128 caracteres\n";
			std::cout << "Saisir un message. Saisir \"Exit\" pour terminer la communication.\n";
			std::getline(std::cin, message);
		}
	}

	envoi = false;
	iResult = send(socketBob, (char*)&envoi, sizeof(bool), 0);
	if (iResult < 0) {
		printf("Client : send failed with error: %d\n", WSAGetLastError());
		return false;
	}


	closeSocket(socketBob);
	return true;
}

bool Alice::ClientClement()
{
	SOCKET socketClement;

	while (!connectTo(socketClement, IP_Clement, ACPort)){}

	std::string messageComplet = "", message = "", mac = "";

	receiveFrom(socketClement, messageComplet);
	messageComplet = Decrypt(messageComplet, ClementKey, ClementIV);
	if (messageComplet == "") {
		std::cout << "Erreur Dechiffrement\n";
		closeSocket(socketClement);
		return false;
	}

	ConvertMessage(messageComplet, message, mac);
	if (CompareMac(message, mac, ClementKey, ClementIV)) {
		bobKey = message;
	}
	else {
		std::cout << "Message non integre\n";
		return false;
	}

	receiveFrom(socketClement, messageComplet);
	messageComplet = Decrypt(messageComplet, ClementKey, ClementIV);
	if (messageComplet == "") {
		std::cout << "Erreur Dechiffrement\n";
		closeSocket(socketClement);
		return false;
	}

	ConvertMessage(messageComplet, message, mac);
	if (CompareMac(message, mac, ClementKey, ClementIV)) {
		bobKeyMAC = message;
	}
	else {
		std::cout << "Message non integre\n";
		return false;
	}

	receiveFrom(socketClement, messageComplet);
	messageComplet = Decrypt(messageComplet, ClementKey, ClementIV);
	if (messageComplet == "") {
		std::cout << "Erreur Dechiffrement\n";
		closeSocket(socketClement);
		return false;
	}
	ConvertMessage(messageComplet, message, mac);
	if (CompareMac(message, mac, ClementKey, ClementIV)) {
		IV = message;
	}
	else {
		std::cout << "Message non integre\n";
		return false;
	}

	closeSocket(socketClement);
	return true;
}

Alice::Alice()
{
}


Alice::~Alice()
{
}

int Alice::run()
{
	InitialiseWinsock();
	

	if (!ClientClement()) {
		CleanupWinsock();
		return -1;
	}
	if (!ClientBob()) {
		CleanupWinsock();
		return -1;
	}


	CleanupWinsock();
	return 0;
}
