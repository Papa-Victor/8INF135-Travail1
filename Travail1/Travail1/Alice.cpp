#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include "Alice.h"
#include <WinSock2.h>



bool Alice::ClientBob()
{
	SOCKET socketBob;

	while (!connectTo(socketBob, IP, ABPort)){}

	int iResult;
	std::string message;
	bool envoi = true;

	std::cout << "Enter a message, Enter \"Exit\" to stop the communication\n";
	std::getline(std::cin, message);
	while (message.length() < bobKey.length()) {
		std::cout << "Taille du message trop petite, message doit etre au moins " << bobKey.length() << "Caracteres.\n";
		std::cout << "Enter a message, Enter \"Exit\" to stop the communication\n";
		std::getline(std::cin, message);
	}
	while (message != "Exit") {
		iResult = send(socketBob, (char*)&envoi, sizeof(bool), 0);
		if (iResult < 0) {
			printf("Client : send failed with error: %d\n", WSAGetLastError());
			return false;
		}

		message += MAC(message, bobKey, nonce);
		sendTo(socketBob, message);
		std::cout << "Enter a message, Enter \"Exit\" to stop the communication\n";
		std::getline(std::cin, message);
		while (message.length() < bobKey.length()) {
			std::cout << "Taille du message trop petite, message doit etre au moins " << bobKey.length() << "Caracteres.\n";
			std::cout << "Enter a message, Enter \"Exit\" to stop the communication\n";
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

Alice::Alice()
{
	bobKey = "1234";
	nonce = "5678";
}


Alice::~Alice()
{
}

void Alice::run()
{
	InitialiseWinsock();
	


	ClientBob();


	CleanupWinsock();
}
