#ifndef BOB_H
#define BOB_H
#include <string>

class Bob
{
#define ClementKey "bobk"
#define ClementNonce "m953"

#define BCPort 65000
#define BAPort 65001

private:
	std::string aliceKey;
	std::string nonce;
public:
	Bob();
	~Bob();
};
#endif //!BOB_H

