#ifndef UTILS_H
#define UTILS_H

#include <array>
using std::string;
using std::array;

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
void RotateArrayRight(array<T,SIZE> &rArray, int numRotations) {
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

string StringXOR(string string1, string string2) {
	int string1l = string1.length();
	if (string1l != string2.length()) {
		return "";
	}
	string returnString = "";
	for (int i = 0; i < string1l; i++) {
		returnString += string1[i] ^ string2[i];
	}
	return returnString;
}


//Prend un charactère ASCII qui représente du Base64 et retourne l'index Base64
// le Charactère '=' considéré comme index 64
int CharToB64Index(char c) {
	if (c >= 65 && c <= 90) {
		return c - 65;
	}
	else if (c >= 97 && c <= 122) {
		return c - 71;
	}
	else if (c >= 48 && c <= 57) {
		return c + 4;
	}
	else if (c == '+') {
		return 62;
	}
	else if (c == '/') {
		return 63;
	}
	else if (c == '=') {
		return 64;
	}
	else {
		return -1;
	}
}

char B64IndexToChar(int index) {
	if (index >= 0 && index <= 25) {
		return (char)(index + 65);
	}
	else if (index >= 26 && index <= 51) {
		return (char)(index + 71);
	}
	else if (index >= 52 && index <= 61) {
		return (char)(index - 4);
	}
	else if (index == 62) {
		return '+';
	}
	else if (index == 63) {
		return '/';
	}
	else if (index == 64) {
		return '=';
	}
	else {
		return -1;
	}
}

string KeyGenerator() {
	string key = "";
	for (int i = 0; i < (rand()%5) + 4; i++) {
		key += (char)((rand() % 95) + 32);
	}
	return key;
}


string KeyGenerator(int keyLength) {
	string key = "";
	for (int i = 0; i < keyLength; i++) {
		key += (char)((rand() % 95) + 32);
	}
	return key;
}

#endif // !UTILS_H
