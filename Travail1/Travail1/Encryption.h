#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <array>
#include <string>


std::array<std::array<char, 65>, 65> CreationTableVigenere(std::string base64_chars);

std::string Encrypt(std::string messageTemp, std::string keyTemp, std::string IVTemp);

std::string Decrypt(const std::string cryptogramme, const std::string keyTemp, const std::string IVTemp);


#endif ENCRYPTION_H