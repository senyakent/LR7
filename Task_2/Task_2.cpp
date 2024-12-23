#include <iostream>
#include <string>
#include "h.h"


int main() {
    while (true) {
        char choice;
        std::cout << "Хотите запустить программу?[y/n]: " << '\n';
        std::cin >> choice;

        while (std::cin.fail() || (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Неверный ввод, введите y/n: ";
            std::cin >> choice;
        }

        if (choice == 'n' || choice == 'N') {
            std::cout << "Конец работы" << "\n";
            break;
        }
        long long int number1, number2;
        std::cout << "Введите два числа: ";
        std::cin >> number1 >> number2;

        // Получаем числа в дополнительном коде (обратном коде для отрицательных)
        std::string result1 = toTwosComplement(number1);
        std::string result2 = toTwosComplement(number2);

        if ((result1.size() < result2.size()) && number1 >= 0) {
            result1.insert(0, result2.size() - result1.size(), '0');
        } else if ((result1.size() < result2.size()) && number1 < 0) {
            result1.insert(0, result2.size() - result1.size(), '1');
        }else if ((result1.size() > result2.size()) && number2 >= 0) {
            result2.insert(0, result1.size() - result2.size(), '0');
        }else if ((result1.size() > result2.size()) && number1 < 0) {
            result2.insert(0, result1.size() - result2.size(), '1');
        }
        std::cout << "1: " << result1 << std::endl;
        std::cout << "2: " << result2 << std::endl;
        // Сложение чисел в дополнительном коде
        std::string sumBinary = addInTwosComplement(result1, result2);
        std::cout << "Сумма в обратном коде: " << sumBinary << std::endl;
        // Преобразуем результат в прямой код
        std::string finalResult = convertToSignMagnitude(sumBinary);

        std::cout << "Сумма в прямом коде: " << finalResult << std::endl;
    }
    return 0;
}
