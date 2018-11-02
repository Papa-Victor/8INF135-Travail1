#include "Utils.h"
#include <random>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

using std::string;
using std::array;


string StringXOR(string string1, string string2) {
	int string1l = string1.length();
	if (string1l != string2.length()) {
		return "";
	}
	string returnString = "";
	for (int i = 0; i < string1l; i++) {
		returnString += string1[i] ^ string2[i];
	}
	return returnString;
}


//Prend un charactère ASCII qui représente du Base64 et retourne l'index Base64
// le Charactère '=' considéré comme index 64
int CharToB64Index(char c) {
	if (c >= 65 && c <= 90) {
		return c - 65;
	}
	else if (c >= 97 && c <= 122) {
		return c - 71;
	}
	else if (c >= 48 && c <= 57) {
		return c + 4;
	}
	else if (c == '+') {
		return 62;
	}
	else if (c == '/') {
		return 63;
	}
	else if (c == '=') {
		return 64;
	}
	else {
		return -1;
	}
}

char B64IndexToChar(int index) {
	if (index >= 0 && index <= 25) {
		return (char)(index + 65);
	}
	else if (index >= 26 && index <= 51) {
		return (char)(index + 71);
	}
	else if (index >= 52 && index <= 61) {
		return (char)(index - 4);
	}
	else if (index == 62) {
		return '+';
	}
	else if (index == 63) {
		return '/';
	}
	else if (index == 64) {
		return '=';
	}
	else {
		return -1;
	}
}

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> keyChar(32, 128);

string KeyGenerator() {
	string key = "";
	for (int i = 0; i < (rand() % 5) + 4; i++) {
		key += (char)keyChar(gen);
	}
	return key;
}


string KeyGenerator(int keyLength) {
	string key = "";
	for (int i = 0; i < keyLength; i++) {
		key += (char)keyChar(gen);
	}
	return key;
}


void ConvertMessage(string messageReceived, string & message, string & mac)
{
	message = messageReceived.substr(0, messageReceived.length() - 16);
	mac = messageReceived.substr(messageReceived.length() - 16, 16);
}


//----------------------------------------
//Par David Gagnon, moodle.uqac.ca, Sécurité des réseaux et du web, Automne 2018
//Fonctions réseaux
bool InitialiseWinsock()
{
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup failed with error: %d\n", iResult);
		return false;
	}
	return true;
}

void CleanupWinsock()
{
	WSACleanup();
}

bool ListenTo(SOCKET& clientSocket, const std::string& port)
{
	SOCKET listenSocket = INVALID_SOCKET;

	int iResult;
	struct addrinfo *result = NULL;
	struct addrinfo hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, port.c_str(), &hints, &result);
	if (iResult != 0) {
		printf("Server : getaddrinfo failed with error: %d\n", iResult);
		return false;
	}

	// Create a SOCKET for connecting to server
	listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (listenSocket == INVALID_SOCKET) {
		printf("Server : socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		return false;
	}

	// Setup the TCP listening socket
	iResult = bind(listenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("Server : bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(listenSocket);
		return false;
	}

	freeaddrinfo(result);

	iResult = listen(listenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("Server : listen failed with error: %d\n", WSAGetLastError());
		closesocket(listenSocket);
		return false;
	}

	// Accept a client socket
	clientSocket = accept(listenSocket, NULL, NULL);
	if (clientSocket == INVALID_SOCKET) {
		printf("Server : accept failed with error: %d\n", WSAGetLastError());
		closesocket(listenSocket);
		return false;
	}

	// No longer need server socket
	closesocket(listenSocket);

	return true;
}

bool connectTo(SOCKET& connectSocket, const std::string& address, const std::string& port)
{
	int iResult;
	struct addrinfo *result;
	struct addrinfo *ptr = NULL;
	struct addrinfo hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(address.c_str(), port.c_str(), &hints, &result);
	if (iResult != 0)
	{
		printf("Client : getaddrinfo failed with error: %d\n", iResult);
		return false;
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
	{
		// Create a SOCKET for connecting to server
		connectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (connectSocket == INVALID_SOCKET)
		{
			printf("Client : socket failed with error: %ld\n", WSAGetLastError());
			return false;
		}

		// Connect to server.
		iResult = connect(connectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR)
		{
			closesocket(connectSocket);
			connectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (connectSocket == INVALID_SOCKET) {
		return false;
	}

	return true;
}

bool closeSocket(SOCKET& socket)
{
	int iResult = 0;
	if (socket != INVALID_SOCKET)
	{
		iResult = closesocket(socket);
		socket = INVALID_SOCKET;
		if (iResult == 0)
		{
			return true;
		}
		else
		{
			printf("Server : closesocket failed with error: %d\n", WSAGetLastError());
			return false;
		}
	}
	return true;
}


bool sendTo(SOCKET& socket, const std::string& inMessage)
{
	int iResult;
	int size = inMessage.size();
	iResult = send(socket, (char*)&size, sizeof(int), 0);
	if (iResult == SOCKET_ERROR) {
		printf("Server : send failed with error: %d\n", WSAGetLastError());
		closesocket(socket);
		return false;
	}

	// Send an initial buffer
	iResult = send(socket, inMessage.c_str(), (int)inMessage.size(), 0);
	if (iResult == SOCKET_ERROR) {
		printf("Server : send failed with error: %d\n", WSAGetLastError());
		closesocket(socket);
		return false;
	}
	return true;
}

int receiveFrom(SOCKET& socket, std::string& outMessage)
{
	char recvbuf[128];
	memset(recvbuf, 0, 128);

	int messageSize = 0;

	int iResult = 0;

	iResult = recv(socket, (char*)&messageSize, sizeof(int), 0);
	if (iResult < 0) {
		printf("Server : recv failed with error: %d\n", WSAGetLastError());
		outMessage.clear();
		return iResult;
	}
	// Receive until the peer closes the connection
	outMessage.clear();
	int count = 0;
	while (count < messageSize) {
		iResult = recv(socket, recvbuf, 128, 0);
		if (iResult < 0) {
			printf("Server : recv failed with error: %d\n", WSAGetLastError());
			outMessage.clear();
			return iResult;
		}
		outMessage += recvbuf;
		count += iResult;
	}

	return iResult;
}

//----------------------------------------
