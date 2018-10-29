#ifndef CLEMENT_H
#define CLEMENT

#include <string>
#include "Utils.h"

class Clement
{
#define AliceKey "alic"
#define AliceNonce "lrk4"
#define BobKey "bobk"
#define BobNonce "m953"

#define CBPort 65004
#define CAPort 65005

private:
	std::string keyAB;
	std::string nonceAB;
	void CreateKey() { keyAB = KeyGenerator(4); }
	void CreateNonce() { nonceAB = KeyGenerator(4); }

public:
	Clement();
	~Clement();

#pragma region Get/Set
	std::string GetKeyAB() const { return keyAB; }
	std::string GetNonceAB() const { return nonceAB; }
#pragma endregion

};
#endif //!CLEMENT_H
