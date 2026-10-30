// Copyright (c) 2026. Shvalev Dmitrij

/* Given a doubly linked list and a pointer to the first element of this list. Create a
text file and write the contents of the list to it in reverse order. Delete the elements
from the list as it is being written. Print the numbers on one line, separated by exactly
one space, with no space at the end of the line.

All dynamic data structures must be implemented through classes. Do not use the STL.
For each dynamic structure, a standard set of methods for adding/removing/printing
elements must be provided. A friendly interface is mandatory in all tasks. Data is
entered from the keyboard. */

#include <clocale>
#include <iostream>
#include <string>

#include "CDoublyLinkedList04.h"
#include "InputOutput04.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian"); // Locale used for Cyrillic output

    CDoublyLinkedList List;
    List.Initialize();

    // Read numbers from the keyboard until the user enters the exit value
    cout << "=== Ввод чисел в список === " << endl;
    while (true) {
        int Number = ReadNumber();
        if (Number == ExitValue) {
            break;
        }
        List.AddElement(Number);
    }

    // Show the list before writing it to the file
    List.Print();

    cout << "\n=== Запись в файл ===" << endl;
    string FileName;
    cout << "Введите имя файла: ";
    cin >> FileName;

    // Write the list to the file in reverse order and clear it, then show the file content
    List.WriteToFileAndClear(FileName);
    PrintFileContent(FileName);
    List.Clear();

    return 0;
}
