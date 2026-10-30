#include <exception>
#include <iostream>
#include <locale>
#include <string>

#include "CWordShuffler01.h"

int main() {
    std::locale::global(std::locale(""));

    std::wcout << L"Enter word: ";
    std::wstring Word;
    std::getline(std::wcin, Word);

    try {
        CWordShuffler Shuffler;
        const int Attempts = Shuffler.ShuffleUntilOriginal(Word, std::wcout);
        std::wcout << Attempts << L" attempts\n";
    }
    catch (const std::exception& Exception) {
        std::cerr << "Error: " << Exception.what() << '\n';
        return 1;
    }

    return 0;
}
