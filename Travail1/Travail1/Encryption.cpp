#include <stdio.h>
#include <iostream>
#include "Encryption.h"
#include "base64.h"
#include "Utils.h"

using std::string;
using std::array;

//basé dur l'équivalent dans Base.cpp
//ajout de '=' pour le chiffrement
static const std::string base64_chars_enc =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/=";


//crée une table de Vigenere contenant de tableaux contenant les éléments de base64_char_enc
//chaque sous tableau est décalé par rapport aux autres
array<array<char, 65>, 65> CreationTableVigenere(string base64_chars) {
	array<array<char, 65>, 65> tableVig;
	for (int i = 0; i < tableVig.size(); i++) {
		for (int j = 0; j < tableVig[i].size(); j++)
		{
			tableVig[i][j] = base64_chars[j];
		}
		RotateArrayRight(tableVig[i], i);
	}

	return tableVig;
}


string Encrypt(string messageTemp, string keyTemp, string IVTemp) {

	std::cout << "----------Log Encrypt----------\n";
	std::cout << "Input:\n" << "\tMessage: " << messageTemp << std::endl << "\tKey: " << keyTemp
	<< std::endl << "\tIV: " << IVTemp << std::endl;


	if (messageTemp.length() < keyTemp.length()) return "";

	const array<array<char, 65>, 65> tableVig = CreationTableVigenere(base64_chars_enc);

	const string key = base64_encode(reinterpret_cast<unsigned const char*>(keyTemp.c_str()), keyTemp.length());


	//la taille des blocs dépend de la taille de l'IV
	const int blocSize = IVTemp.length();
	string IV = base64_encode(reinterpret_cast<unsigned const char*>(IVTemp.c_str()), IVTemp.length());
	const int blocSize64 = IV.length();

	char messageLength = messageTemp.length();
	//ajout de padding
	while (messageTemp.length() % blocSize != blocSize - 1) {
		messageTemp += CHAR_MAX;
	}
	//ajoute la taille du message original à la fin de padding pour retrouver le message original au déchiffrement
	messageTemp += messageLength;

	const string message = messageTemp;

	int positionInKey = 0;
	string cryptogramme = "", bloc = IV, messageSub = "";

	int nombreBlocs = message.length() / blocSize;

	for (int i = 0; i < nombreBlocs; i++) {

		bloc = base64_decode(bloc);
		//S'assurer que le bloc est de la bonne taille après le décodage
		if (bloc.length() > blocSize) {
			bloc = bloc.substr(0, blocSize);
		}
		while (bloc.length() < blocSize) {
			bloc += " ";
		}

		//ou exclusif avec le cryptogramme précédent
		messageSub = message.substr(i * blocSize, blocSize);
		messageSub = StringXOR(messageSub, bloc);
		messageSub = base64_encode(reinterpret_cast<const unsigned char*>(messageSub.c_str()), messageSub.length());
		//réencode pour s'assurer de n'avoir que de la base64 après le ou exclusif


		//Chiffrement de Vigenère au bloc courant
		bloc = "";
		for (int j = 0; j < blocSize64; j++) {
			bloc += tableVig[CharToB64Index(key[positionInKey])][CharToB64Index(messageSub[j])];
			positionInKey++;
			if (positionInKey > key.length() - 1) {
				positionInKey = 0;
			}
		}
		cryptogramme += bloc;
	}

	std::cout << "Output: \n\tCryptogramme: " << cryptogramme << std::endl;
	std::cout << "----------Log Encrypt End----------\n";

	return cryptogramme;
}

string Decrypt(const string cryptogramme, const string keyTemp, const string IVTemp) {

	std::cout << "----------Log Decrypt----------\n";
	std::cout << "Input:\n" << "\tCryptogramme: " << cryptogramme << std::endl << "\tKey: " << keyTemp
	<< std::endl << "\tIV: " << IVTemp << std::endl;

	const array<array<char, 65>, 65> tableVig = CreationTableVigenere(base64_chars_enc);

	int positionInKey = 0;
	string key = base64_encode(reinterpret_cast<unsigned const char*>(keyTemp.c_str()), keyTemp.length());

	const int blocSize = IVTemp.length();
	const string IV = base64_encode(reinterpret_cast<const unsigned char*>(IVTemp.c_str()), IVTemp.length());
	const int blocSize64 = IV.length();
	const int numBloc = cryptogramme.length() / blocSize64;

	string subCrypto = "", prevSubCrypto = IV;
	string message = "", subMessage = "";

	for (int i = 0; i < numBloc; i++) {

		//Déchiffrement de Vigenère au bloc courant
		subCrypto = cryptogramme.substr(i * blocSize64, blocSize64);
		for (int j = 0; j < blocSize64; j++) {

			for (int k = 0; k < tableVig[CharToB64Index(key[positionInKey])].size(); k++) {
				if (subCrypto[j] == tableVig[CharToB64Index(key[positionInKey])][k]) {
					subMessage += B64IndexToChar(k);
					break;
				}
			}

			positionInKey++;
			if (positionInKey > key.length() - 1) {
				positionInKey = 0;
			}
		}

		prevSubCrypto = base64_decode(prevSubCrypto);
		//même vérification qu'au chiffrement sur la taille du bloc
		if (prevSubCrypto.length() > blocSize) {
			prevSubCrypto = prevSubCrypto.substr(0, blocSize);
		}
		while (prevSubCrypto.length() < blocSize) {
			prevSubCrypto += " ";
		}

		message += StringXOR(base64_decode(subMessage), prevSubCrypto);
		subMessage = "";
		prevSubCrypto = subCrypto;


	}

	//enlève le padding
	size_t messageLength = message.back();

	std::string messagesub = message.substr(0, messageLength);

	std::cout << "Output: \n\tMessage: " << messagesub << std::endl;
	std::cout << "----------Log Decrypt End----------\n";

	return messagesub;

}