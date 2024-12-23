#include <iostream>
#include <string>
#include "h.h"


int main() {
    while (true) {
        char choice;
        std::cout << "Хотите запустить программу?[y/n]: ";
        std::cin >> choice;

        if (choice == 'n' || choice == 'N') {
            std::cout << "Конец работы\n";
            break;
        }

        int base;
        std::string num1, num2;
        char operation;

        std::cout << "Введите основание системы счисления (2-36): ";
        std::cin >> base;

        if (base < 2 || base > 36) {
            std::cerr << "Основание системы счисления должно быть в диапазоне от 2 до 36.\n";
            continue;
        }

        std::cout << "Введите два числа: ";
        std::cin >> num1 >> num2;

        std::cout << "Введите операцию (+ или -): ";
        std::cin >> operation;

        if (operation == '+') {
            std::cout << "Результат сложения: " << addBase(num1, num2, base) << "\n";
        } else if (operation == '-') {
            std::cout << "Результат вычитания: " << subtractBase(num1, num2, base) << "\n";
        } else {
            std::cerr << "Недопустимая операция.\n";
        }
    }
    return 0;
}