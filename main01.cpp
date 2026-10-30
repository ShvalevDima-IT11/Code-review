// Copyright (c) 2026. Shvalev Dmitrij

/* Given a number D and a pointer P1 to the top of a non-empty stack.
Add an element with the value D to the stack and print the address P2 of the new top.

For each dynamic structure, a standard set of methods for adding/removing/printing
elements must be provided. A friendly interface is mandatory in all tasks. Data is
entered from the keyboard. */

#include <clocale>
#include <iostream>
#include <windows.h>

#include "CStack01.h"

using namespace std;

int main() {
    // Use the Russian locale and the Windows-1251 code page for Cyrillic output
    setlocale(LC_ALL, "Russian"); // Locale used for Cyrillic output
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    CStack Stack;
    int ElementCount;  // Number of elements to push into the stack
    int InputValue;    // Value entered from the keyboard

    // Ask how many elements the user wants in the stack
    cout << "Сколько чисел вы хотите, чтобы было в стеке? ";
    cin >> ElementCount;

    // Read the given number of values and push them onto the stack
    for (int Index = 0; Index < ElementCount; Index++) {
        cout << "Введите число " << Index + 1 << ": ";
        cin >> InputValue;
        Stack.Push(InputValue);
    }

    // Print the address of the top of the stack and its content
    Stack.ShowAddress();
    cout << "Элементы в стеке: ";
    Stack.Show();

    // Read a new value and push it on top of the stack
    int ValueToPush;
    cout << "Введите значение ValueToPush для добавления в стек: ";
    cin >> ValueToPush;
    Stack.Push(ValueToPush);

    // Print the new content and the new top address
    cout << "Элементы в новом стеке: ";
    Stack.Show();
    Stack.ShowAddress();

    // Print the value of the new top, or a warning if the stack is empty
    if (!Stack.IsEmpty()) {
        cout << "Значение новой вершины: " << Stack.GetTopValue() << endl;
    }
    else {
        cout << "Стек пуст!" << endl;
    }

    return 0;
}
