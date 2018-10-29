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

#define CBPort "65000"
#define CAPort "65001"

#define IP "172.19.131.79"

private:
	std::string keyAB;
	std::string nonceAB;
	void CreateKey() { keyAB = KeyGenerator(4); }
	void CreateNonce() { nonceAB = KeyGenerator(4); }

public:
	Clement();
	~Clement();

	void run();
};
#endif //!CLEMENT_H
