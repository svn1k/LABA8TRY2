#include <iostream>
#include <locale.h>
#include "phone_call.h"
#include "file_reader.h"
#include "constants.h"
#include "filter.h"
#include "sort.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Лабораторная работа №8. GIT\n";
    cout << "Вариант №9. Телефонные разговоры\n";
    cout << "Автор: Никитенко Святослав\n";
    cout << "Группа: 25ПИнж1д\n\n";

    PhoneCall* calls[MAX_FILE_ROMS_COUNT];
    int size;

    try {
        readPhoneCalls(DATA_FILE, calls, size);

        // ПРОСТОЙ ВЫВОД
        cout << "Прочитано записей: " << size << "\n\n";
        for (int i = 0; i < size; i++) {
            cout << i + 1 << ". " << calls[i]->number << " | "
                << calls[i]->tariff << endl;
        }

        // КРАСИВЫЙ ФОРМАТИРОВАННЫЙ ВЫВОД
        cout << "\n\n==================================================\n";
        cout << "ДЕТАЛЬНАЯ ИНФОРМАЦИЯ О ВСЕХ ЗВОНКАХ:\n";
        cout << "==================================================\n";

        for (int i = 0; i < size; i++) {
            cout << "ЗВОНОК #" << i + 1 << "\n";
            cout << "  Номер телефона:  " << calls[i]->number << "\n";
            cout << "  Дата звонка:     "
                << calls[i]->callDate.day << "."
                << calls[i]->callDate.month << "."
                << calls[i]->callDate.year << "\n";
            cout << "  Время начала:    "
                << calls[i]->startTime.hours << ":"
                << calls[i]->startTime.minutes << ":"
                << calls[i]->startTime.seconds << "\n";
            cout << "  Длительность:    "
                << calls[i]->duration.hours << ":"
                << calls[i]->duration.minutes << ":"
                << calls[i]->duration.seconds << "\n";
            cout << "  Тариф:           " << calls[i]->tariff << "\n";
            cout << "  Стоимость/мин:   " << calls[i]->costPerMinute << " руб.\n";
            cout << "--------------------------------------------------\n";
        }

        // ========== ВЫБОР ОПЕРАЦИИ ==========
        int operation;
        cout << "\n\nВыберите операцию:\n";
        cout << "1 - Фильтрация данных\n";
        cout << "2 - Сортировка данных\n";
        cout << "Ваш выбор: ";
        cin >> operation;

        if (operation == 1) {
            // ========== ФИЛЬТРАЦИЯ ==========
            int filterChoice;
            cout << "\nВыберите критерий фильтрации:\n";
            cout << "1 - Только мобильные звонки\n";
            cout << "2 - Только звонки за ноябрь 2021 года\n";
            cout << "Ваш выбор: ";
            cin >> filterChoice;

            PhoneCall** filteredCalls = nullptr;
            int filteredSize = 0;

            if (filterChoice == 1) {
                filteredCalls = filterPhoneCalls(calls, size, isMobileCall, filteredSize);
                cout << "\n========================================\n";
                cout << "МОБИЛЬНЫЕ ЗВОНКИ (" << filteredSize << " шт.):\n";
            }
            else if (filterChoice == 2) {
                filteredCalls = filterPhoneCalls(calls, size, isNovember2021Call, filteredSize);
                cout << "\n========================================\n";
                cout << "ЗВОНКИ ЗА НОЯБРЬ 2021 (" << filteredSize << " шт.):\n";
            }
            else {
                cout << "Неверный выбор!\n";
                filteredSize = 0;
            }

            // Вывод отфильтрованных данных
            if (filteredSize > 0) {
                cout << "========================================\n";
                for (int i = 0; i < filteredSize; i++) {
                    cout << i + 1 << ". " << filteredCalls[i]->number << " | "
                        << filteredCalls[i]->tariff << " | "
                        << filteredCalls[i]->callDate.day << "."
                        << filteredCalls[i]->callDate.month << "."
                        << filteredCalls[i]->callDate.year << " | "
                        << filteredCalls[i]->duration.hours << ":"
                        << filteredCalls[i]->duration.minutes << ":"
                        << filteredCalls[i]->duration.seconds << "\n";
                }
                delete[] filteredCalls;
            }
            else if (filterChoice == 1 || filterChoice == 2) {
                cout << "Нет данных, соответствующих выбранному критерию.\n";
            }
        }
        else if (operation == 2) {
            // ========== СОРТИРОВКА ==========
            int sortMethod, compareMethod;

            // Выбор метода сортировки
            cout << "\nВыберите метод сортировки:\n";
            cout << "1 - Пирамидальная сортировка (Heap sort)\n";
            cout << "2 - Быстрая сортировка (Quick sort)\n";
            cout << "Ваш выбор: ";
            cin >> sortMethod;

            // Выбор критерия сравнения
            cout << "\nВыберите критерий сортировки:\n";
            cout << "1 - По убыванию продолжительности разговора\n";
            cout << "2 - По возрастанию номера телефона, при равных номерах - по убыванию стоимости\n";
            cout << "Ваш выбор: ";
            cin >> compareMethod;

            // Выбор функции сравнения
            int (*compareFunc)(PhoneCall*, PhoneCall*) = nullptr;
            if (compareMethod == 1) {
                compareFunc = compareByDurationDesc;
                cout << "\n========================================\n";
                cout << "СОРТИРОВКА ПО УБЫВАНИЮ ПРОДОЛЖИТЕЛЬНОСТИ:\n";
            }
            else if (compareMethod == 2) {
                compareFunc = compareByNumberAndCost;
                cout << "\n========================================\n";
                cout << "СОРТИРОВКА ПО НОМЕРУ (↑) И СТОИМОСТИ (↓):\n";
            }
            else {
                cout << "Неверный выбор!\n";
                compareFunc = nullptr;
            }

            // Выполнение сортировки
            if (compareFunc != nullptr) {
                if (sortMethod == 1) {
                    heapSort(calls, size, compareFunc);
                    cout << "Метод: Пирамидальная сортировка\n";
                }
                else if (sortMethod == 2) {
                    quickSort(calls, size, compareFunc);
                    cout << "Метод: Быстрая сортировка\n";
                }

                // Вывод отсортированных данных
                cout << "========================================\n";
                for (int i = 0; i < size; i++) {
                    cout << i + 1 << ". " << calls[i]->number << " | ";

                    if (compareMethod == 1) {
                        // Для сортировки по продолжительности
                        cout << calls[i]->duration.hours << ":"
                            << calls[i]->duration.minutes << ":"
                            << calls[i]->duration.seconds << " | ";
                    }
                    else {
                        // Для сортировки по номеру и стоимости
                        cout << calls[i]->costPerMinute << " руб/мин | ";
                    }

                    cout << calls[i]->tariff << " | "
                        << calls[i]->callDate.day << "."
                        << calls[i]->callDate.month << "."
                        << calls[i]->callDate.year << "\n";
                }
            }
        }
        else {
            cout << "Неверный выбор операции!\n";
        }

        // Очистка памяти исходного массива
        for (int i = 0; i < size; i++) {
            delete calls[i];
        }
    }
    catch (const char* error) {
        cout << "Ошибка: " << error << endl;
    }

    return 0;
}
