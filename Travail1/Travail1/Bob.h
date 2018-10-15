#ifndef BOB_H
#define BOB_H
#include <string>

class Bob
{
#define ClementKey "bobk"
#define ClementNonce "m953"

private:
	std::string aliceKey;
	std::string nonce;
public:
	Bob();
	~Bob();
};
#endif //!BOB_H

