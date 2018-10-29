#include "Bob.h"



bool Bob::ServeurBob()
{
	SOCKET socketAlice;
	
	ListenTo(socketAlice, BAPort);

	std::string message = "";

	receiveFrom(socketAlice, message);

	closeSocket(socketAlice);
	return true;
}

Bob::Bob()
{
	aliceKey = "";
	nonce = "";
}


Bob::~Bob()
{
}

void Bob::run()
{
	InitialiseWinsock();

	ServeurBob();

	CleanupWinsock();
}
