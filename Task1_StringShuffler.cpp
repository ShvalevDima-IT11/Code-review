#include "Task1_StringShuffler.h"
#include <iostream>
#include <algorithm>

CStringShuffler::CStringShuffler() {
    std::random_device RandomDevice;
    RandomEngine.seed(RandomDevice());
}

CStringShuffler::~CStringShuffler() {
}

int CStringShuffler::ExecuteShuffle(const std::string& _InputWord) {
    if (_InputWord.empty()) {
        return 0;
    }

    std::string CurrentPermutation = _InputWord;
    int TotalAttempts = 0;
    bool bIsMatching = false;

    while (!bIsMatching) {
        std::shuffle(CurrentPermutation.begin(), CurrentPermutation.end(), RandomEngine);
        TotalAttempts++;
        _PrintAttempt(CurrentPermutation, TotalAttempts);

        if (CurrentPermutation == _InputWord) {
            bIsMatching = true;
        }
    }

    return TotalAttempts;
}

void CStringShuffler::_PrintAttempt(const std::string& _Attempt, int _AttemptIndex) const {
    std::cout << _Attempt << "\n";
}
