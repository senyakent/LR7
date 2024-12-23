#include <iostream>
#include <string>

int charToDigit(char ch) {
    if (ch >= '0' && ch <= '9') {
        return ch - '0';
    }
    if (ch >= 'A' && ch <= 'Z') {
        return ch - 'A' + 10;
    }
    return -1;
}

char digitToChar(int digit) {
    if (digit >= 0 && digit <= 9) {
        return '0' + digit;
    }
    if (digit >= 10) {
        return 'A' + (digit - 10);
    }
    return ' ';
}

std::string addPositive(std::string num1, std::string num2, int base) {
    std::string result = "";
    int carry = 0;

    int len1 = num1.size(), len2 = num2.size();
    int maxLen = std::max(len1, len2);

    // Выравнивание длины чисел
    while (num1.size() < maxLen) num1 = '0' + num1;
    while (num2.size() < maxLen) num2 = '0' + num2;

    for (int i = maxLen - 1; i >= 0; --i) {
        int digit1 = charToDigit(num1[i]);
        int digit2 = charToDigit(num2[i]);
        int sum = digit1 + digit2 + carry;

        result = digitToChar(sum % base) + result;
        carry = sum / base;
    }

    if (carry > 0) {
        result = digitToChar(carry) + result;
    }

    return result;
}

std::string subtractPositive(std::string num1, std::string num2, int base) {
    std::string result = "";
    int borrow = 0;

    int len1 = num1.size(), len2 = num2.size();
    int maxLen = std::max(len1, len2);

    // Выравнивание длины чисел
    while (num1.size() < maxLen) num1 = '0' + num1;
    while (num2.size() < maxLen) num2 = '0' + num2;

    for (int i = maxLen - 1; i >= 0; --i) {
        int digit1 = charToDigit(num1[i]) - borrow;
        int digit2 = charToDigit(num2[i]);

        if (digit1 < digit2) {
            digit1 += base;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result = digitToChar(digit1 - digit2) + result;
    }

    // Убираем ведущие нули
    while (result.size() > 1 && result[0] == '0') {
        result.erase(result.begin());
    }

    return result;
}

std::string addBase(std::string num1, std::string num2, int base) {
    bool isNegative1 = (num1[0] == '-');
    bool isNegative2 = (num2[0] == '-');

    // Убираем знаки для обработки модулей чисел
    if (isNegative1) num1 = num1.substr(1);
    if (isNegative2) num2 = num2.substr(1);

    // Обработка различных случаев
    if (!isNegative1 && !isNegative2) {
        return addPositive(num1, num2, base);
    } else if (isNegative1 && isNegative2) {
        return "-" + addPositive(num1, num2, base);
    } else if (isNegative1 && !isNegative2) {
        if (num1.size() > num2.size() || (num1.size() == num2.size() && num1 > num2)) {
            return "-" + subtractPositive(num1, num2, base);
        } else {
            return subtractPositive(num2, num1, base);
        }
    } else {
        if (num2.size() > num1.size() || (num2.size() == num1.size() && num2 > num1)) {
            return "-" + subtractPositive(num2, num1, base);
        } else {
            return subtractPositive(num1, num2, base);
        }
    }
}

std::string subtractBase(std::string num1, std::string num2, int base) {

    if (num2[0] != '-') {
        num2 = "-" + num2;
    } else {
        num2 = num2.substr(1);
    }
    return addBase(num1, num2, base);
}