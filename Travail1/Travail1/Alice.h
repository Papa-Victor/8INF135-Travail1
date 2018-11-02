#ifndef ALICE_H
#define ALICE_H

#include <string>
#include <iostream>
#include "Utils.h"
#include "MAC.h"
class Alice
{
#define ClementKey "alic"
#define ClementIV "lrk4"

#define ACPort "65001"
#define ABPort "65002"

private:
	std::string bobKeyMAC;
	std::string bobKey;
	std::string IV;
	bool ClientBob();
	bool ClientClement();
public:
	Alice();
	~Alice();
	int run();
};
#endif;//!ALICE_H