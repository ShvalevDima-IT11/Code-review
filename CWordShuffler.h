#pragma once

#include <ostream>
#include <random>
#include <string>
#include <vector>

/// <summary>
/// Shuffles the letters of a word until the original word appears again.
/// </summary>
/// <remarks>
/// A word is treated as a UTF-8 string, so multi-byte letters (for example Cyrillic ones)
/// are moved as whole letters and are never split into separate bytes.
/// </remarks>
class CWordShuffler {
public:
    /// <summary>
    /// Maximum number of letters in a word. Longer words are rejected,
    /// because the expected number of attempts grows as a factorial of the length.
    /// </summary>
    static constexpr int MaxLetterCount = 8;

    /// <summary>
    /// Creates a shuffler whose random engine is seeded with a non-deterministic value.
    /// </summary>
    CWordShuffler();

    /// <summary>
    /// Checks whether a word has more letters than <see cref="MaxLetterCount"/>.
    /// </summary>
    /// <param name="_Word">Word in UTF-8 encoding.</param>
    /// <returns>True if the word is too long to be shuffled; otherwise false.</returns>
    bool IsWordTooLong(const std::string& _Word) const;

    /// <summary>
    /// Randomly permutes the letters of a word again and again, printing every result,
    /// until the permuted word equals the original one.
    /// </summary>
    /// <param name="_Word">Original word in UTF-8 encoding.</param>
    /// <param name="_Output">Stream that receives every shuffled word, one per line.</param>
    /// <returns>
    /// Number of printed words (the final word equal to the original is counted,
    /// the original word itself is not printed). Zero for an empty word.
    /// </returns>
    /// <exception cref="std::length_error">The word is longer than <see cref="MaxLetterCount"/>.</exception>
    int ShuffleUntilOriginal(const std::string& _Word, std::ostream& _Output);

private:
    /// <summary>
    /// Splits a UTF-8 string into separate letters (code points).
    /// </summary>
    /// <param name="_Word">Word in UTF-8 encoding.</param>
    /// <returns>Letters of the word in their original order.</returns>
    std::vector<std::string> _SplitIntoLetters(const std::string& _Word) const;

    /// <summary>
    /// Concatenates letters back into a single string.
    /// </summary>
    /// <param name="_Letters">Letters to concatenate.</param>
    /// <returns>The resulting word.</returns>
    std::string _JoinLetters(const std::vector<std::string>& _Letters) const;

    /// <summary>Pseudo-random number generator used for shuffling.</summary>
    std::mt19937 RandomEngine;
};
