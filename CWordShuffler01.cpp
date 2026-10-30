#include "CWordShuffler01.h"

#include <algorithm>
#include <stdexcept>

CWordShuffler::CWordShuffler() : _Engine(std::random_device{}()) {
}

int CWordShuffler::ShuffleUntilOriginal(const std::wstring& Original, std::wostream& Out) {
    if (Original.empty()) {
        throw std::invalid_argument("Word must not be empty");
    }

    std::wstring Shuffled = Original;
    int Attempts = 0;

    do {
        std::shuffle(Shuffled.begin(), Shuffled.end(), _Engine);
        ++Attempts;
        Out << Shuffled << L'\n';
    } while (Shuffled != Original);

    return Attempts;
}
