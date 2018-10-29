#ifndef ALICE_H
#define ALICE_H
#include <string>
#include "Utils.h"
class Alice
{
#define ClementKey "alic"
#define ClementNonce "lrk4"

#define ACPort "65001"
#define ABPort "65002"

#define IP "172.19.131.79"

private:
	std::string bobKey;
	std::string nonce;
	bool ClientBob();
public:
	Alice();
	~Alice();
	void run();
	void SetKey(std::string key) { bobKey = key; }
	void SetNonce(std::string nonce) { this->nonce = nonce; }
};
#endif;//!ALICE_H