#ifndef UTILS_H
#define UTILS_H

#include <array>
using std::string;

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
void RotateArrayRight(std::array<T,SIZE> &rArray, int numRotations) {
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

#endif // !UTILS_H
