#ifndef ALICE_H
#define ALICE_H

#include <string>
#include <iostream>
#include "Utils.h"
#include "MAC.h"
class Alice
{
#define ClementKey "alic"
#define ClementNonce "lrk4"

#define ACPort "65001"
#define ABPort "65002"

#define IP "10.0.1.14"

private:
	std::string bobKey;
	std::string nonce;
	bool ClientBob();
	bool ClientClement();
public:
	Alice();
	~Alice();
	int run();
	void SetKey(std::string key) { bobKey = key; }
	void SetNonce(std::string nonce) { this->nonce = nonce; }
};
#endif;//!ALICE_H