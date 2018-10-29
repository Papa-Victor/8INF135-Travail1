#ifndef BOB_H
#define BOB_H
#include <string>
#include <iostream>
#include "Utils.h"

class Bob
{
#define ClementKey "bobk"
#define ClementNonce "m953"

#define BCPort "65000"
#define BAPort "65002"

#define IP "172.19.131.79"

private:
	std::string aliceKey;
	std::string nonce;
	bool ServeurBob();
public:
	Bob();
	~Bob();
	void run();
	void SetKey(std::string key) { aliceKey = key; }
	void SetNonce(std::string nonce) { this->nonce = nonce; }
};
#endif //!BOB_H

