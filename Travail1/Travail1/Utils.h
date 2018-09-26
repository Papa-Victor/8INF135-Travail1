#ifndef UTILS_H
#define UTILS_H

#include <array>

template <class T, size_t SIZE>
void RotateArrayRight(std::array<T, SIZE> &rArray) {
	int size = rArray.size();
	T last = rArray[size - 1];
	for (int i = size - 1; i > 0; i--) {
		rArray[i] = rArray[i - 1];
	}
	rArray[0] = last;

}

template <class T, size_t SIZE>
void RotateArrayRight(std::array<T,SIZE> &rArray, int numRotations) {
	int size = rArray.size();
	for (int j = 0; j < numRotations; j++) {
		T last = rArray[size - 1];
		for (int i = size - 1; i > 0; i--) {
			rArray[i] = rArray[i - 1];
		}
		rArray[0] = last;
	}

}

#endif // !UTILS_H
