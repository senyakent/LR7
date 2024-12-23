#include <iostream>
#include "h.h"
#include <cmath>

int main() //g++ funcs.cpp input.cpp Task_4.cpp -o Task_4
 {
    long long int n;
    std::cout << "введите число =" << '\n';
    std::cin >> n;
    while (std::cin.peek() != '\n' || std::cin.fail() || n <= 0) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Неверный ввод. Пожалуйста, введите целое число большее нуля: ";
        std::cin >> n;
    }

    bool d53 = del(abs(n), 27, 53);
    bool d109 = del(abs(n), 55, 109);
    bool d5 = del(abs(n), 3, 5);

    if (d5 == 1)
    {
        std::cout << "Число делится на 5.\n";
    }
    else if (d5 == 0)
    {
        std::cout << "Число не делится на 5.\n";
    }

    if (d53 == 1)
    {
        std::cout << "Число делится на 53.\n";
    }
    else if (d53 == 0)
    {
        std::cout << "Число не делится на 53.\n";
    }

    if (d109 == 1)
    {
        std::cout << "Число делится на 109.\n";
    }
    else if (d109 == 0)
    {
        std::cout << "Число не делится на 109.\n";
    }

    return 0;
}