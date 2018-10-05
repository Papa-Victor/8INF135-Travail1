#ifndef MAC_H
#define MAC_H

#include <string>

std::string HashSimple(std::string message);

std::string MAC(std::string message, std::string key, std::string nonce);

bool CompareMac(std::string message, std::string macReceived, std::string key, std::string nonce);



#endif // !MAC_H

