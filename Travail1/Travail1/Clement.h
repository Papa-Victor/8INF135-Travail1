#ifndef CLEMENT_H
#define CLEMENT

#include <string>
#include "Utils.h"
#include "MAC.h"

class Clement
{
#define AliceKey "alic"
#define AliceNonce "lrk4"
#define BobKey "bobk"
#define BobNonce "m953"

#define CBPort "65000"
#define CAPort "65001"

#define IP "10.0.1.14"

private:
	std::string keyAB;
	std::string nonceAB;
	void CreateKey() { keyAB = KeyGenerator(4); }
	void CreateNonce() { nonceAB = KeyGenerator(4); }
	bool keyServeur(std::string port, std::string key, std::string nonce);

public:
	Clement();
	~Clement();

	int run();
};
#endif //!CLEMENT_H
