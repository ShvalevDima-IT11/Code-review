// Copyright (c) 2026. Shvalev Dmitrij

#include <ctime>
#include <fstream>
#include <iostream>
#include <list>
#include <random>

#include "EInputMethod05.h"
#include "ListOperations05.h"

using namespace std;

namespace {
    const char* const Separator = " "; // Separator between printed values

    const int MinRandomValue = -50; // Minimum value of a generated random number
    const int MaxRandomValue = 50;  // Maximum value of a generated random number
    const int MiddleDivisor = 2;    // Divisor used to find the middle element

    const char* const InputFileName = "a.txt"; // File with the input data

    const char* const MethodPrompt = "Выберете способ заполнения контейнера: ";
    const char* const KeyboardOption = "1)Ввод с клавиатуры.";
    const char* const RandomOption = "2)Ввод с помощью рандомайзера.";
    const char* const FileOption = "3)Ввод данных из текстового файла.";
    const char* const ElementPromptPrefix = "Введите ";
    const char* const ElementPromptSuffix = " элемент: ";
    const char* const FileOpenErrorMessage = "Ошибка. Файл не был открыт.";
    const char* const InputErrorMessage = "Ошибка ввода.";
}

// Fill the list using the method chosen by the user
void FillList(list<int>& _List, int _Count) {
    int Choice;
    int Value;

    // Ask the user how the data should be entered
    cout << MethodPrompt << endl;
    cout << KeyboardOption << endl;
    cout << RandomOption << endl;
    cout << FileOption << endl;
    cin >> Choice;

    switch (static_cast<EInputMethod>(Choice)) {
    case EInputMethod::Keyboard: {
        // Read _Count values from the keyboard
        for (int Index = 0; Index < _Count; Index++) {
            cout << ElementPromptPrefix << Index + 1 << ElementPromptSuffix;
            cin >> Value;
            _List.insert(_List.end(), Value);
        }
        break;
    }

    case EInputMethod::Random: {
        // Generate _Count random values with a modern pseudo-random generator
        random_device RandomDevice;
        mt19937 Generator(RandomDevice());
        uniform_int_distribution<int> Distribution(MinRandomValue, MaxRandomValue);
        for (int Index = 0; Index < _Count; Index++) {
            _List.insert(_List.end(), Distribution(Generator));
        }
        break;
    }

    case EInputMethod::File: {
        // Example of the content of a.txt: 27 -8 -11 -25 33 47 -30 -41 -8 3 -13 -29 -38 -18
        ifstream InputFile(InputFileName, ios::in);
        if (!InputFile) {
            cout << FileOpenErrorMessage << endl;
            return;
        }
        for (int Index = 0; Index < _Count; Index++) {
            InputFile >> Value;
            _List.insert(_List.end(), Value);
        }
        InputFile.close();
        break;
    }

    default: {
        cout << InputErrorMessage << endl;
        break;
    }
    }
}

// Print all elements of the list using a forward iterator
void PrintList(const list<int>& _List) {
    for (list<int>::const_iterator Iterator = _List.begin();
        Iterator != _List.end();
        Iterator++) {
        cout << *Iterator << Separator;
    }
    cout << endl;
}

// Move the middle element of the source list to the end of the destination list
// using a single call to list::splice
void MoveMiddleElement(list<int>& _SourceList, list<int>& _DestinationList) {
    list<int>::iterator MiddleIterator = _SourceList.begin();
    size_t Size = _SourceList.size();
    for (size_t Index = 0; Index < Size / MiddleDivisor; Index++) {
        ++MiddleIterator;
    }
    _DestinationList.splice(_DestinationList.end(), _SourceList, MiddleIterator);
}
