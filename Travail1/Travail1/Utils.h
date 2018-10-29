#ifndef UTILS_H
#define UTILS_H

#include <array>
#include <string>
#include <ws2tcpip.h>
#include <stdio.h>


//rotates an array one index to the right
template <class T, size_t SIZE>
void RotateArrayRight(std::array<T, SIZE> &rArray) {
	int size = rArray.size();
	T last = rArray[size - 1];
	for (int i = size - 1; i > 0; i--) {
		rArray[i] = rArray[i - 1];
	}
	rArray[0] = last;

}
//rotates an array numRotations indexes to the right
template <class T, size_t SIZE>
void RotateArrayRight(std::array<T, SIZE> &rArray, int numRotations) {
	if (numRotations < 0) {
		return;
	}
	int size = rArray.size();
	for (int j = 0; j < numRotations; j++) {
		T last = rArray[size - 1];
		for (int i = size - 1; i > 0; i--) {
			rArray[i] = rArray[i - 1];
		}
		rArray[0] = last;
	}

}


std::string StringXOR(std::string string1, std::string string2);


//Prend un charactère ASCII qui représente du Base64 et retourne l'index Base64
// le Charactère '=' considéré comme index 64
int CharToB64Index(char c);

char B64IndexToChar(int index);

std::string KeyGenerator();

std::string KeyGenerator(int keyLength);


//Prend un message reçu contenant le message et le MAC et les séparent
void ConvertMessage(std::string messageReceived, std::string& message, std::string& mac);


//----------------------------------------
//Fonctions réseaux
bool InitialiseWinsock();
void CleanupWinsock();

bool ListenTo(SOCKET& socket, const std::string& port);
bool connectTo(SOCKET& socket, const std::string& address, const std::string& port);
bool closeSocket(SOCKET& socket);

bool sendTo(SOCKET& socket, const std::string& inMessage);
int receiveFrom(SOCKET& socket, std::string& outMessage);
//----------------------------------------

#endif
