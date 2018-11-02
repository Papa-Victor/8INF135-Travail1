#ifndef BOB_H
#define BOB_H
#include <string>
#include <iostream>
#include "Utils.h"
#include "MAC.h"

class Bob
{
#define ClementKey "bobk"
#define ClementIV "m953"

#define BCPort "65000"
#define BAPort "65002"

private:
	std::string aliceKeyMAC;
	std::string aliceKey;
	std::string IV;
	bool ServeurBob();
	bool ClientClement();
public:
	Bob();
	~Bob();
	int run();
};
#endif //!BOB_H

