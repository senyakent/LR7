#include <iostream>
#include <string>
#include <cmath>

std::string decimalToBinary(long long number) {
    std::string binary = "";
    if (number == 0)
        return "0";

    long long absNumber = std::abs(number);
    while (absNumber > 0) {
        binary += (absNumber % 2 == 0) ? '0' : '1';
        absNumber /= 2;
    }

    std::string reversedBinary = "";
    for (int i = binary.length() - 1; i >= 0; i--) {
        reversedBinary += binary[i];
    }

    return reversedBinary;
}

std::string invertBits(const std::string &binary) {
    std::string inverted = binary;
    for (char &bit: inverted) {
        bit = (bit == '0') ? '1' : '0';
    }
    return inverted;
}

std::string addOneToBinary(const std::string &binary) {
    std::string result = "";

    bool carry = true;
    for (int i = binary.length() - 1; i >= 0; i--) {
        char bit = binary[i];
        if (carry) {
            if (bit == '0') {
                result = '1' + result;
                carry = false;
            } else {
                result = '0' + result;
            }
        } else {
            result = bit + result;
        }
    }

    if (carry)
        result = '1' + result;

    return result;
}

std::string toTwosComplement(long long number) {
    if (number >= 0) {
        return decimalToBinary(number);
    } else {
        std::string binary = decimalToBinary(-number);
        std::string inverted = invertBits(binary);
        inverted = '1' + inverted;
        return inverted;
    }
}

std::string addInTwosComplement(std::string binary1, std::string binary2) {
    std::string result = "";
    bool carry = false;

    for (int i = binary1.size() - 1; i >= 0; i--) {
        bool bit1 = binary1[i] == '1';
        bool bit2 = binary2[i] == '1';

        bool sum = bit1 ^ bit2 ^ carry;
        carry = (bit1 && bit2) || (bit1 && carry) || (bit2 && carry);

        result = (sum ? '1' : '0') + result;
    }

    if (carry) {
        result = '1' + result;
    }

    return result;
}

std::string convertToSignMagnitude(std::string result) {
    if (result[0] == '1') {
        std::string inverted = invertBits(result);
        inverted[0] = '1';
        return inverted;
    }

    return result;
}
