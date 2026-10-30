// Copyright (c) 2026. All rights reserved.

#include <cctype>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>

#include "InputOutput04.h"

using namespace std;

// Read a number from the keyboard, validating that it consists of digits
// (with an optional leading '-') or equals '-1' to stop the input
int ReadNumber() {
    string Input;
    while (true) {
        cout << "Введите число (или '-1' для завершения): ";
        cin >> Input;

        if (Input == "-1") {
            return ExitValue;
        }

        bool bIsCorrect = true;
        int Sign = 1;
        size_t StartIndex = 0;

        if (Input.empty()) {
            bIsCorrect = false;
        }
        else if (Input[0] == '-') {
            Sign = -1;
            StartIndex = 1;
            if (Input.size() == 1) {
                bIsCorrect = false;
            }
        }

        // All remaining characters must be digits
        for (size_t Index = StartIndex; Index < Input.size(); ++Index) {
            if (!isdigit(Input[Index])) {
                bIsCorrect = false;
            }
        }

        if (bIsCorrect) {
            int Number = 0;
            for (size_t Index = StartIndex; Index < Input.size(); ++Index) {
                Number = Number * 10 + (Input[Index] - '0');
            }
            return Number * Sign;
        }

        cout << "Некорректный ввод! Используйте цифры и знак '-' в начале." << endl;
    }
}

// Print the content of the given file line by line
void PrintFileContent(const string& _FileName) {
    ifstream InputFile(_FileName);
    if (!InputFile.is_open()) {
        cout << "Ошибка при открытии файла для чтения!" << endl;
        return;
    }

    cout << "\n=== Содержимое файла ===" << endl;
    string Line;
    while (getline(InputFile, Line)) {
        cout << Line << endl;
    }
    InputFile.close();
}
