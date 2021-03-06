#ifndef BASE64_H
#define BASE64_h

//
//  base64 encoding and decoding with C++.
//  Version: 1.01.00
//
//Source : https://renenyffenegger.ch/notes/development/Base64/Encoding-and-decoding-base-64-with-cpp

#ifndef BASE64_H_C0CE2A47_D10E_42C9_A27C_C883944E704A
#define BASE64_H_C0CE2A47_D10E_42C9_A27C_C883944E704A

#include <string>

std::string base64_encode(unsigned char const*, unsigned int len);
std::string base64_decode(std::string const& s);

#endif /* BASE64_H_C0CE2A47_D10E_42C9_A27C_C883944E704A */




#endif // !BASE64_H

