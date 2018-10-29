#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include "Alice.h"
#include <WinSock2.h>



bool Alice::ClientBob()
{
	SOCKET socketBob;

	while (!connectTo(socketBob, IP, ABPort)){}

	std::string message = "This is a test message";
	sendTo(socketBob, message);




	closeSocket(socketBob);
	return true;
}

Alice::Alice()
{
	bobKey = "";
	nonce = "";
}


Alice::~Alice()
{
}

void Alice::run()
{
	InitialiseWinsock();
	


	ClientBob();


	CleanupWinsock();
}
