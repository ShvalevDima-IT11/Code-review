#include "Task1_StringShuffler.h"
#include <iostream>

int main() {
    std::cout << "========================================\n";
    std::cout << "   LABORATORY WORK #3 - OPTION 5\n";
    std::cout << "========================================\n\n";

    std::cout << "--- TASK 1: Word Shuffle Permutation ---\n";
    CStringShuffler Shuffler;
    std::string TargetWord = "корова";
    std::cout << "Target Word: " << TargetWord << "\n";
    int Attempts = Shuffler.ExecuteShuffle(TargetWord);
    std::cout << "Total Shuffles (excluding initial): " << Attempts << "\n\n";
    return 0;
}
