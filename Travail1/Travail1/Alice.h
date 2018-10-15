#ifndef ALICE_H
#define ALICE_H
#include <string>
class Alice
{
#define ClementKey "alic"
#define ClementNonce "lrk4"

private:
	std::string bobKey;
	std::string nonce;
public:
	Alice();
	~Alice();
};
#endif;//!ALICE_H

