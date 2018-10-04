#ifndef UTILS_H
#define UTILS_H

#include <array>
#include <string>


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

#endif
