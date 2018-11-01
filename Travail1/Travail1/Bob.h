#ifndef BOB_H
#define BOB_H
#include <string>
#include <iostream>
#include "Utils.h"
#include "MAC.h"

class Bob
{
#define ClementKey "bobk"
#define ClementNonce "m953"

#define BCPort "65000"
#define BAPort "65002"

#define IP "10.0.1.14"

private:
	std::string aliceKey;
	std::string nonce;
	bool ServeurBob();
	bool ClientClement();
public:
	Bob();
	~Bob();
	int run();
	void SetKey(std::string key) { aliceKey = key; }
	void SetNonce(std::string nonce) { this->nonce = nonce; }
};
#endif //!BOB_H

