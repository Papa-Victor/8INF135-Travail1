#include <stdio.h>
#include "Encryption.h"
#include "base64.h"
#include "Utils.h"

using std::string;
using std::array;

//basé dur l'équivalent dans Base.cpp
//ajout de '='
static const std::string base64_chars_enc =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/=";


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
	const array<array<char, 65>, 65> tableVig = CreationTableVigenere(base64_chars_enc);

	const string key = base64_encode(reinterpret_cast<unsigned const char*>(keyTemp.c_str()), keyTemp.length());

	const int blocSize = IVTemp.length();
	string IV = base64_encode(reinterpret_cast<unsigned const char*>(IVTemp.c_str()), IVTemp.length());
	const int blocSize64 = IV.length();

	while (messageTemp.length() % blocSize != 0 || messageTemp.length() < keyTemp.length()) {
		messageTemp += (char)0;
	}

	const string message = messageTemp;

	int positionInKey = 0;
	string cryptogramme = "", bloc = IV, messageSub = "";

	int nombreBlocs = message.length() / blocSize;

	for (int i = 0; i < nombreBlocs; i++) {

		bloc = base64_decode(bloc);
		if (bloc.length() > blocSize) {
			bloc = bloc.substr(0, blocSize);
		}
		while (bloc.length() < blocSize) {
			bloc += " ";
		}

		messageSub = message.substr(i * blocSize, blocSize);
		messageSub = StringXOR(messageSub, bloc);
		messageSub = base64_encode(reinterpret_cast<const unsigned char*>(messageSub.c_str()), messageSub.length());

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

	return cryptogramme;
}

string Decrypt(const string cryptogramme, const string keyTemp, const string IVTemp) {
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
		if (prevSubCrypto.length() > blocSize) {
			prevSubCrypto = prevSubCrypto.substr(0, blocSize);
		}
		while (prevSubCrypto.length() < blocSize) {
			prevSubCrypto += (char)0;
		}

		message += StringXOR(base64_decode(subMessage), prevSubCrypto);
		subMessage = "";
		prevSubCrypto = subCrypto;


	}

	return message;
}