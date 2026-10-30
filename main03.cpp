// Copyright (c) 2026. Shvalev Dmitrij

/* Given a singly linked list and a pointer P1 to the head of the list. The values of the
list elements are sorted in ascending order. Create a copy of the original list, then
insert the value M into the newly created list so that it remains sorted, and print the
pointer to the first element of the resulting list P2.

For each dynamic structure, a standard set of methods for adding/removing/printing
elements must be provided. A friendly interface is mandatory in all tasks. Data is
entered from the keyboard. */

#include <iostream>
#include <windows.h>

#include "CList03.h"
#include "EUserChoice03.h"

using namespace std;

int main() {
    // Use the Windows-1251 code page so that Cyrillic text is displayed correctly
    setlocale(LC_ALL, "Russian"); // Locale used for Cyrillic output
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    CList OriginalList;
    int ElementCount;   // Number of elements to be entered
    int ValueToInsert;  // Value M to insert into the copy

    // Print the welcome message and the task description
    cout << "Добро пожаловать! \n"
        << "Перед нами последняя задача: \n"
        << "Дан односвязный линейный список. "
        << "Значения элементов списка упорядочены по возрастанию. \n"
        << "Необходимо создать копию исходного списка, "
        << "после чего во вновь созданном списке вставить \n"
        << "значение M так, чтобы он остался упорядоченным "
        << "и вывести ссылку на первый элемент полученного списка P2. \n" << endl << endl
        << "---------------------------------------------" << endl << endl
        << "Вам необхожимо будет ввести количество элементов в списке, \n"
        << "а позже ввести значения элементов СТРОГО В ПОРЯДКЕ ВОЗРАСТАНИЯ \n"
        << "и ввести число которое вы хотите вставить. \n"
        << "ПРИМЕР ПОРЯДКА ВОЗРАСТАНИЯ 1 2 3 4 5 6 \n"
        << "----------------------------------------------" << endl << endl

        << "Введите число n - количество элементов в списке: ";
    cin >> ElementCount;

    // Read the elements in ascending order and append them to the original list
    cout << endl << "Введите " << ElementCount << " чисел в порядке возрастания (!!!!): ";
    for (int Index = 0; Index < ElementCount; Index++) {
        int Value;
        cin >> Value;
        OriginalList.Add(Value);
    }

    // Create a deep copy of the original list using the copy constructor
    CList CopyList(OriginalList);

    cout << endl << "Введите целое значение числа m, которое необходимо будет вставить: ";
    cin >> ValueToInsert;

    // Show the original list before any change
    OriginalList.Print(false);
    cout << endl;

    // Insert M into the copy keeping the ascending order
    CopyList.InsertSorted(ValueToInsert);
    CopyList.Print(false);

    // Ask the user whether any elements should be deleted
    int Choice;
    cout << endl << "Хотите удалить какой-нибудь элемент?" << endl;
    cout << "Если да, то напишите 1" << endl;
    cout << "Если нет, то напишите 2" << endl;
    cout << "Ваш выбор: ";
    cin >> Choice;
    cout << endl;

    switch (static_cast<EUserChoice>(Choice)) {
    case EUserChoice::Yes: {
        // Read how many elements to delete and remove them one by one
        cout << "Введите число - количество элементов которое вы хотите удалить: ";
        int DeleteCount;
        cin >> DeleteCount;
        for (int Index = 0; Index < DeleteCount; Index++) {
            cout << "Введите значение элемента, который вы хотите удалить: ";
            int ValueToDelete;
            cin >> ValueToDelete;
            cout << endl;
            cout << "Удаление...." << endl;
            CopyList.DeleteByValue(ValueToDelete);
        }
        // Print the result; if the list became empty, show the corresponding message
        CopyList.Print(true);
        break;
    }

    case EUserChoice::No: {
        cout << "Спасибо за терпение!!!" << endl;
        cout << "До свидания!!!" << endl;
        break;
    }

    default: {
        cout << "Введено неверное число";
        break;
    }
    }
    return 0;
}
