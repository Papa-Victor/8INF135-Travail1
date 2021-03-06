#include "Bob.h"
#include "Encryption.h"
#include "IP.h"



bool Bob::ServeurBob()
{
	SOCKET socketAlice;
	
	ListenTo(socketAlice, BAPort);

	if (!ClientClement()) {
		closeSocket(socketAlice);
		return false;
	}

	std::string messageComplet = "";
	std::string messageSeul = "";
	std::string mac = "";
	int iResult;
	bool envoi = true;

	//R�ception du Bool�en, si vrai, Alice envoie un message
	iResult = recv(socketAlice, (char*)&envoi, sizeof(bool), 0);
	if (iResult < 0) {
		printf("Server : recv failed with error: %d\n", WSAGetLastError());
		return iResult;
	}

	//Tant qu'Alice envoie des messages, on les re�oit
	while (envoi) {
		receiveFrom(socketAlice, messageComplet);

		//D�chiffrement
		messageComplet = Decrypt(messageComplet, aliceKey, IV);

		//V�rification de l'int�grit�
		ConvertMessage(messageComplet, messageSeul, mac);
		if (CompareMac(messageSeul, mac, aliceKeyMAC, IV)) {
			std::cout << "Message Re�u : " << messageSeul << std::endl;
		}
		else {
			std::cout << "Message non integre\n";
			closeSocket(socketAlice);
			return false;
		}

		//R�ception du Bool�en, si vrai, Alice envoie un message
		iResult = recv(socketAlice, (char*)&envoi, sizeof(bool), 0);
		if (iResult < 0) {
			printf("Server : recv failed with error: %d\n", WSAGetLastError());
			return false;
		}
	}

	closeSocket(socketAlice);
	return true;
}


//Communication avec Clement
//Re�oit les cl�s et l'IV pour la communication avec Alice
bool Bob::ClientClement()
{
	SOCKET socketClement;

	while (!connectTo(socketClement, IP_Clement, BCPort)) {}

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
		aliceKey = message;
	}
	else {
		std::cout << "Message non integre\n";
		closeSocket(socketClement);
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
		aliceKeyMAC = message;
	}
	else {
		std::cout << "Message non integre\n";
		closeSocket(socketClement);
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
		closeSocket(socketClement);
		return false;
	}

	closeSocket(socketClement);
	return true;
}

Bob::Bob()
{
}


Bob::~Bob()
{
}

int Bob::run()
{
	InitialiseWinsock();

	if (!ServeurBob()) {
		CleanupWinsock();
		return -1;
	}

	CleanupWinsock();
	return 0;
}
