// Copyright (c) 2026. All rights reserved.

/* Given a number N (> 0) and pointers P1 and P2 to the head and the tail of a non-empty
queue. Extract N leading elements from the queue and print their values (if the queue
contains fewer than N elements, extract all of them). Also print the new addresses of the
head and the tail (for an empty queue print nullptr twice). After extracting the elements,
free the memory they occupied.

For each dynamic structure, a standard set of methods for adding/removing/printing
elements must be provided. A friendly interface is mandatory in all tasks. Data is
entered from the keyboard. */

#include <clocale>
#include <iostream>
#include <windows.h>

#include "CQueue02.h"

using namespace std;

int main() {
    // Use the Russian locale and the Windows-1251 code page for Cyrillic output
    setlocale(LC_ALL, "Russian"); // Locale used for Cyrillic output
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    CQueue Queue;
    int ElementCount; // Number of elements in the queue
    int ExtractCount; // Number of elements to extract

    // Print the welcome message and the task description
    cout << "Добро пожаловать! \n"
        << "Перед нами новая задача: \n"
        << "Дано число ExtractCount (> 0) и указатели Head и Tail "
        << "на начало и конец непустой очереди. \n"
        << "Извлечь из очереди N начальных элементов \n"
        << "--------------------------------------------------------- \n"
        << "Вам необходимо ввести количество элементов "
        << "очереди и их значения через пробел \n"
        << "Мы выведем новые адреса начала и конца очереди, "
        << "извлечем n значений и выведем на экран \n"
        << endl << endl
        << "---------------------------------------------------------- \n"

        << "Введите число ElementCount - количество элементов очереди: \n";
    cin >> ElementCount;

    // Read the given number of values and append them to the queue
    cout << "Введите " << ElementCount
        << " значений элементов очереди через пробел ";
    for (int Index = 0; Index < ElementCount; Index++) {
        int Value;
        cin >> Value;
        Queue.Add(Value);
    }

    // Ask how many leading elements should be extracted
    cout << endl << endl
        << "Введите число ExtractCount (> 0) - количество элементов "
        << "очереди, которые нужно извлечь из очереди: ";
    cin >> ExtractCount;

    // Print the initial state, extract the elements and print the result
    Queue.ShowInitial();
    Queue.ExtractElements(ExtractCount);
    Queue.ShowAfterExtraction();

    return 0;
}
