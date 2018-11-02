#ifndef CLEMENT_H
#define CLEMENT

#include <string>
#include "Utils.h"
#include "MAC.h"

class Clement
{
#define AliceKey "alic"
#define AliceIV "lrk4"
#define BobKey "bobk"
#define BobIV "m953"

#define CBPort "65000"
#define CAPort "65001"

private:
	std::string keyAB;
	std::string keyAB_MAC;
	std::string IVAB;
	void CreateKey() { keyAB = KeyGenerator(4); }
	void CreateKeyMAC() { keyAB_MAC = KeyGenerator(4); }
	void CreateIV() { IVAB = KeyGenerator(4); }
	bool keyServeur(std::string port, std::string key, std::string IV);

public:
	Clement();
	~Clement();

	int run();
};
#endif //!CLEMENT_H
