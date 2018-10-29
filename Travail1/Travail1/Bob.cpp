#include "Bob.h"



bool Bob::ServeurBob()
{
	SOCKET socketAlice;
	
	ListenTo(socketAlice, BAPort);

	std::string messageComplet = "";
	std::string messageSeul = "";
	std::string mac = "";
	int iResult;
	bool envoi = true;

	iResult = recv(socketAlice, (char*)&envoi, sizeof(bool), 0);
	if (iResult < 0) {
		printf("Server : recv failed with error: %d\n", WSAGetLastError());
		return iResult;
	}
	while (envoi) {
		receiveFrom(socketAlice, messageComplet);
		ConvertMessage(messageComplet, messageSeul, mac);
		if (CompareMac(messageSeul, mac, aliceKey, nonce)) {
			std::cout << "Message Reçu : " << messageSeul << std::endl;
		}
		else {
			std::cout << "Message non integre\n";
			return false;
		}
		iResult = recv(socketAlice, (char*)&envoi, sizeof(bool), 0);
		if (iResult < 0) {
			printf("Server : recv failed with error: %d\n", WSAGetLastError());
			return false;
		}
	}

	closeSocket(socketAlice);
	return true;
}

Bob::Bob()
{
	aliceKey = "1234";
	nonce = "5678";
}


Bob::~Bob()
{
}

void Bob::run()
{
	InitialiseWinsock();

	ServeurBob();

	CleanupWinsock();
}
