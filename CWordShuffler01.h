#pragma once

#include <iosfwd>
#include <random>
#include <string>

/// <summary>
/// Shuffles letters of a word until the original word is restored.
/// </summary>
class CWordShuffler {
public:
    CWordShuffler();

    /// <summary>
    /// Randomly shuffles letters of Original and prints every permutation
    /// until the shuffled word equals Original. The final matching permutation
    /// is printed and counted.
    /// </summary>
    /// <param name="Original">Source word.</param>
    /// <param name="Out">Output stream for permutations.</param>
    /// <returns>Number of printed permutations including the final original word.</returns>
    int ShuffleUntilOriginal(const std::wstring& Original, std::wostream& Out);

private:
    std::mt19937 _Engine;
};
