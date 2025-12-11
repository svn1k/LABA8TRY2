#include <iostream>
#include <iomanip>

using namespace std;

#include "book_subscription.h"
#include "file_reader.h"
#include "constants.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Лабораторная работа №8. GIT\n";
    cout << "Вариант №0. Библиотечный абонемент\n";
    cout << "Автор: Сергей Ермоченко\n\n";
    book_subscription* subscriptions[MAX_FILE_ROWS_COUNT];
    int size;
    try
    {
        read("data.txt", subscriptions, size);
        cout << "***** Библиотечный абонемент *****\n\n";
        for (int i = 0; i < size; i++)
        {
            /********** вывод читателя **********/
            cout << "Читатель........: ";
            // вывод фамилии
            cout << subscriptions[i]->reader.last_name << " ";
            // вывод первой буквы имени
            cout << subscriptions[i]->reader.first_name[0] << ". ";
            // вывод первой буквы отчества
            cout << subscriptions[i]->reader.middle_name[0] << ".";
            cout << '\n';
            /********** вывод книги **********/
            cout << "Книга...........: ";
            // вывод фамилии автора
            cout << subscriptions[i]->author.last_name << " ";
            // вывод первой буквы имени автора
            cout << subscriptions[i]->author.first_name[0] << ". ";
            // вывод первой буквы отчества автора
            cout << subscriptions[i]->author.middle_name[0] << ".";
            cout << ", ";
            // вывод названия
            cout << '"' << subscriptions[i]->title << '"';
            cout << '\n';
            /********** вывод даты выдачи **********/
            // вывод года
            cout << "Дата выдачи.....: ";
            cout << setw(4) << setfill('0') << subscriptions[i]->start.year << '-';
            // вывод месяца
            cout << setw(2) << setfill('0') << subscriptions[i]->start.month << '-';
            // вывод числа
            cout << setw(2) << setfill('0') << subscriptions[i]->start.day;
            cout << '\n';
            /********** вывод даты возврата **********/
            // вывод года
            cout << "Дата возврата...: ";
            cout << setw(4) << setfill('0') << subscriptions[i]->finish.year << '-';
            // вывод месяца
            cout << setw(2) << setfill('0') << subscriptions[i]->finish.month << '-';
            // вывод числа
            cout << setw(2) << setfill('0') << subscriptions[i]->finish.day;
            cout << '\n';
            cout << '\n';
        }
        for (int i = 0; i < size; i++)
        {
            delete subscriptions[i];
        }
    }
    catch (const char* error)
    {
        cout << error << '\n';
    }
    return 0;
}