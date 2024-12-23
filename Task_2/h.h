#pragma once
#include <string>
std::string decimalToBinary(long long number);
std::string invertBits(const std::string& binary);
std::string addOneToBinary(const std::string& binary);
std::string toTwosComplement(long long number) ;
std::string addInTwosComplement(std::string binary1, std::string binary2);
std::string convertToSignMagnitude(std::string result);