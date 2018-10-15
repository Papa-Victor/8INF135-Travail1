#ifndef CLEMENT_H
#define CLEMENT

#include <string>

class Clement
{
#define AliceKey "alic"
#define AliceNonce "lrk4"
#define BobKey "bobk"
#define BobNonce "m953"

private:
	std::string keyAB;
	std::string nonceAB;

public:
	Clement();
	~Clement();
};
#endif //!CLEMENT_H
