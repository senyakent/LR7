
#include <string>

// Перевод десятичного числа в двоичное представление
std::string decimalToBinary(long long number) {
    std::string binary = "";
    if (number == 0)
        return "0";

    long long absNumber = std::abs(number);
    while (absNumber > 0) {
        binary += (absNumber % 2 == 0) ? '0' : '1';
        absNumber /= 2;
    }

    // Реверс вручную без std::reverse
    std::string reversedBinary = "";
    for (int i = binary.length() - 1; i >= 0; i--) {
        reversedBinary += binary[i];
    }

    return reversedBinary;
}

// Инвертирование битов строки
std::string invertBits(const std::string& binary) {
    std::string inverted = binary;
    for (char& bit : inverted) {
        bit = (bit == '0') ? '1' : '0';
    }
    return inverted;
}

// Добавление единицы к двоичному числу
std::string addOneToBinary(const std::string& binary) {
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

// Преобразование числа в дополнительный код
std::string toTwosComplement(long long number) {
    if (number >= 0) {
        return decimalToBinary(number);
    } else {
        std::string binary = decimalToBinary(-number);
        std::string inverted = invertBits(binary);
        return addOneToBinary(inverted);
    }
}
