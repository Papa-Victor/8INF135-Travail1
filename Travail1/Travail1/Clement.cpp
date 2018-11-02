#include <iostream>
#include "Clement.h"
#include "Encryption.h"


//Le serveur attend une connection et envoie les cl�s et les IV n�c�ssaire � la communication entre Alice et Bob
bool Clement::keyServeur(std::string port, std::string key, std::string IV)
{

	SOCKET socket;

	ListenTo(socket, port);


//Le bloc suivant pr�pare le message � envoie et v�rifie qu'il n'y ait pas d'erreurs
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
//Fin du bloc

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


//Le constructeur cr�e les cl�s � envoyer � Alice et Bob
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


	//Le syst�me est synchrone, donc Alice demande toujours les informations avant Bob 
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
