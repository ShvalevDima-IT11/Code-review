// Copyright (c) 2026. Shvalev Dmitrij

/* The container elements are integers. To fill a container, use an iterator and the
constructor of the corresponding container; to print the elements, use an iterator
(to print the elements in reverse order, use the reverse iterators returned by the member
functions rbegin and rend). A friendly interface is mandatory. Data input must be organized
in different ways (keyboard, random, file).

Given lists L1 and L2; list L1 has an odd number of elements. Move the middle element of
list L1 to the end of list L2. Use a single call of the member function splice. */

#include <clocale>
#include <cstdlib>
#include <iostream>
#include <list>

#include "ListOperations05.h"

using namespace std;

namespace {
    const char* const FirstListLabel = "L1: ";
    const char* const SecondListLabel = "L2: ";
}

int main() {
    setlocale(LC_ALL, "Russian"); // Locale used for Cyrillic output

    int FirstSize;
    int SecondSize;
    list<int> FirstList;
    list<int> SecondList;

    // Ask for the sizes and fill the first list
    cout << "Введите размерность списка n1 (n1 - нечётное): ";
    cin >> FirstSize;
    FillList(FirstList, FirstSize);

    cout << "Введите размерность списка n2 (n2 >= 0): ";
    cin >> SecondSize;

    // Validate the sizes: n1 must be odd and non-negative, n2 must be non-negative
    if (FirstSize < 0 || SecondSize < 0 || FirstSize % 2 != 1) {
        cout << "Ошибка. Недопустимый размер списка.";
        return EXIT_FAILURE;
    }

    FillList(SecondList, SecondSize);

    // Print the initial content of both lists
    cout << "Изначальное содержимое списков." << endl;
    cout << "L1: ";
    PrintList(FirstList);
    cout << "L2: ";
    PrintList(SecondList);

    // Move the middle element of the first list to the end of the second list
    MoveMiddleElement(FirstList, SecondList);

    // Print the changed content of both lists
    cout << "Изменённое содержание списков." << endl;
    cout << "L1: ";
    PrintList(FirstList);
    cout << "L2: ";
    PrintList(SecondList);

    return EXIT_SUCCESS;
}
