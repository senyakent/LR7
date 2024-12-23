#include <iostream>
#include <string>
#include "h.h"

// Основная функция
int main() {
    long long number;
    std::cout << "Введите число: ";
    std::cin >> number;

    std::string result = toTwosComplement(number);
    std::cout << "Число в дополнительном коде: " << result << std::endl;

    return 0;
}