#ifndef ENCRYPTION_H
#define ENCRYPTION_H
#include <stdio.h>
#include <iostream>
#include "base64.h"
#include "Utils.h"

using std::cout;
using std::endl;
using std::string;


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




//Fonction d'encryption

string Encrypt(string messageTemp, string keyTemp, string IVTemp) {
	const array<array<char, 65>, 65> tableVig = CreationTableVigenere(base64_chars_enc);
	
	const string key = base64_encode(reinterpret_cast<unsigned const char*>(keyTemp.c_str()), keyTemp.length());

	const int blocSize = IVTemp.length();
	string IV = base64_encode(reinterpret_cast<unsigned const char*>(IVTemp.c_str()), IVTemp.length());
	const int blocSize64 = IV.length();

	while (messageTemp.length() % blocSize != 0) {
		messageTemp += " ";
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









#endif ENCRYPTION_H