#include <iostream>
#include <bitset> // Для вывода чисел в бинарном формате



const int MAX_GROOPS = 30; // Количество групп
const int MAX_SLAVES = 5;  // Количество рабов
const int MAX_BARRELS = 240; // Количество бочек

// Функция для подсчета количества единичных битов в числе
// Сложность: O(log_2(n)), так как цикл выполняется, пока есть ненулевые биты.
int countOnes(int n) {
    int count = 0;
    while (n) { // Цикл проходит по всем битам числа n
        if (n & 1) count++;
        n >>= 1;
    }
    return count;
}

// Функция для запроса на запуск программы
// Сложность: O(1), так как выполняется фиксированное количество проверок.
int askToRunProgram() {
    char choice;
    std::cout << "\n";
    std::cout << "Хотите запустить программу? (y/n) " << "\n";
    while (true) {
        std::cin >> choice;
        if (std::cin.fail() || std::cin.peek() != '\n' || (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')) {
            std::cout << "Введите y/n.\n";
            std::cin.clear();
            std::cin.ignore(100000000, '\n');
            continue;
        }

        if (choice == 'n' || choice == 'N') {
            std::cout << "Спасибо за использование.\n";
            return 0;
        }

        if (choice == 'y' || choice == 'Y') {
            return 1;
        }
    }
}

// Функция для заполнения массива групп
// Сложность: O(MAX_GROOPS), так как цикл выполняется фиксированное количество раз (30).
void ZapolnGroops(int groops[MAX_GROOPS + 1]) {
    groops[0] = 0;
    groops[1] = 32;

    for (int i = 1; i <= 29; ++i) { // Цикл выполняется 29 раз
        int onesCount = countOnes(i); // Сложность: O(log_2(i)), но \( i \) мало, так что близко к O(1).
        int increment = 0;

        if (onesCount == 1) {
            increment = 16;
        } else if (onesCount == 2) {
            increment = 8;
        } else if (onesCount == 3) {
            increment = 4;
        } else if (onesCount == 4) {
            increment = 2;
        }

        groops[i + 1] = groops[i] + increment;
    }
}

// Функция для получения индексов единичных битов числа
// Сложность: O(log_2(n)), так как цикл выполняется, пока есть ненулевые биты.
void getOneBit(int n, int indices[MAX_SLAVES], int &size) {
    int index = 0;
    size = 0;
    while (n > 0) { // Цикл проходит по всем битам числа n
        if (n & 1) {
            indices[size++] = index;
        }
        n >>= 1;
        index++;
    }
}

// Функция для нахождения группы и обновления состояния рабов на основе отравленных бочек
// Сложность: O(MAX_BARRELS), так как внешний цикл проходит по MAX_GROOPS, а внутренний охватывает все бочки.
void FindGroop(const int groops[MAX_GROOPS + 1], bool slaves[MAX_SLAVES], const bool barrels[MAX_BARRELS]) {
    for (int i = 0; i < MAX_GROOPS; ++i) { // Внешний цикл по группам (30 итераций)
        int Ones[MAX_SLAVES];
        int onesCount = 0;
        getOneBit(i, Ones, onesCount); // Сложность: O(log_2(i))

        for (int j = 0; j < onesCount; ++j) { // Цикл по количеству единичных битов (до 5 итераций)
            for (int k = groops[i]; k < groops[i + 1]; ++k) { // Цикл по диапазону бочек (всего 240 бочек)
                if (barrels[k]) {
                    slaves[Ones[j]] = true; // Помечаем раба
                }
            }
        }
    }
}

// Функция для вычисления номера группы из состояния рабов
// Сложность: O(MAX_SLAVES), так как цикл проходит фиксированное количество раз (5).
int NumberGroop_Barr(const bool slaves[MAX_SLAVES]) {
    int result = 0;
    int razr = 1;
    for (int i = 0; i < MAX_SLAVES; ++i) { // Цикл по рабам (5 итераций)
        result += slaves[i] * razr;
        razr *= 2;
    }
    return result;
}

// Функция для очистки массива рабов
// Сложность: O(MAX_SLAVES^2), так как вложенный цикл удаляет элементы из массива.
void CleanSlaves(bool slaves[MAX_SLAVES]) {
    int i = 0;
    while (i < MAX_SLAVES) { // Внешний цикл по массиву (5 итераций)
        if (slaves[i]) {
            for (int j = i; j < MAX_SLAVES - 1; ++j) { // Вложенный цикл для сдвига элементов (до 5
                                slaves[j] = slaves[j + 1];
            }
            slaves[MAX_SLAVES - 1] = false; // Помечаем последний элемент как false
        } else {
            ++i;
        }
    }
}

// Функция для нахождения отравленной бочки по номеру группы
// Сложность: O(MAX_BARRELS), так как цикл проходит по диапазону бочек в указанной группе.
void findBarrel(int number, const int groops[MAX_GROOPS + 1], bool slaves[MAX_SLAVES], const bool barrels[MAX_BARRELS]) {
    for (int k = groops[number], i = 0; k < groops[number + 1]; ++k, ++i) { // Цикл по диапазону бочек группы
        int Ones[MAX_SLAVES];
        int onesCount = 0;
        getOneBit(i, Ones, onesCount); // Сложность: O(log_2(i))

        for (int j = 0; j < onesCount; ++j) { // Цикл по количеству единичных битов
            if (!slaves[Ones[j]]) {
                slaves[Ones[j]] = barrels[k]; // Обновление состояния раба
            }
        }
    }
}

// Функция для отображения состояния рабов
// Сложность: O(MAX_SLAVES), так как цикл проходит фиксированное количество раз (5).
void displaySlavesState(const bool slaves[MAX_SLAVES], const int groops[MAX_GROOPS + 1]) {
    std::cout << "Состояние рабов (какие бочки они пробовали):\n";
    for (int i = 0; i < MAX_SLAVES; ++i) { // Цикл по рабам
        std::cout << "Раб " << i + 1 << " : ";
        std::cout << std::bitset<1>(slaves[i]) << " ";  // Показываем битовое состояние
        if (slaves[i]) {
            std::cout << "Пробовал отравленную бочку (мёртв).\n";
        } else {
            std::cout << "Не пробовал отравленную бочку.\n";
        }
    }
}

// Функция для вывода объяснений
// Сложность: O(MAX_SLAVES), так как вызывает displaySlavesState.
void displayExplanation(const bool slaves[MAX_SLAVES], int day) {
    std::cout << "\nДень " << day << ":\n";
    displaySlavesState(slaves, nullptr); // Переход в первый день
    std::cout << "Объяснение: ";
    if (day == 1) {
        std::cout << "Программа определила, какие рабы умерли, основываясь на том, какие бочки они пробовали и были отравлены.\n";
    } else {
        std::cout << "На основе состояния рабов на второй день программа определяет, какая именно бочка была отравлена.\n";
    }
}

// Функция для вывода диапазона группы
// Сложность: O(1), так как операция простая.
void displayGroupRange(const int groops[MAX_GROOPS + 1], int groupNumber) {
    int start = groops[groupNumber];
    int end = groops[groupNumber + 1] - 1;
    std::cout << "Отравленная бочка находится в диапазоне: " << start + 1 << " - " << end + 1 << "\n";
}


int main() {
    while (askToRunProgram() == 1) {
        // Вывод контекста задачи
        std::cout << "\nПатриций решил устроить праздник и для этого приготовил 240 бочек вина. Однако к нему пробрался недоброжелатель по имени *Пользователь*, "
                  << "который подсыпал яд в одну из бочек. Недоброжелателя тут же поймали, дальнейшая его судьба неизвестна, но ходят слухи, что он проверяет консольный ввод в аду в качестве наказания.\n"
                  << "Про яд известно, что человек, который его выпил, умирает в течение 24 часов. До праздника осталось два дня, то есть 48 часов. "
                  << "У патриция есть пять рабов, которыми он готов пожертвовать, чтобы узнать, в какой именно бочке яд.\n\n";

        std::cout << "Меню:\n"
                  << "1. Все бочки делятся на 31 групп.\n"
                  << "2. Количество групп из 32 бочек — 1.\n"
                  << "3. Количество групп из 16 бочек — 5.\n"
                  << "4. Количество групп из 8 бочек — 10.\n"
                  << "5. Количество групп из 4 бочек — 10.\n"
                  << "6. Количество групп из 2 бочек — 5.\n";

        bool barrels[MAX_BARRELS] = {false};
        bool slaves[MAX_SLAVES] = {false};
        int groops[MAX_GROOPS + 1]; // groops array

        ZapolnGroops(groops);

        int poisen_bar;
        std::cout << "Отравите бочку. Введите номер отравленной бочки.\n";
        std::cin >> poisen_bar;

        barrels[poisen_bar - 1] = true;

        // Этап 1 - Определение, какие рабы умирают (группиро
        FindGroop(groops, slaves, barrels);

        // Выводим состояние рабов с информацией о бочках, которые они пробовали
        std::cout << "\nДень1:\n";
        displaySlavesState(slaves, groops);

        // Преобразование рабов в номер группы
        int a = NumberGroop_Barr(slaves);
        CleanSlaves(slaves);

        // Выводим в какой группе находится отравленная бочка после первого дня
        std::cout << "Группа, в которой находится отравленная бочка после 1 дня: " << a << "\n";

        // Выводим диапазон группы
        displayGroupRange(groops, a);

        // Этап 2 - Определение, какая бочка отравлена
        findBarrel(a, groops, slaves, barrels);
        displayExplanation(slaves, 2);

        // Выводим номер отравленной бочки
        int b = NumberGroop_Barr(slaves) + groops[a] + 1;
        std::cout << "Отравленная бочка: " << b << "\n";
    }
    return 0;
}