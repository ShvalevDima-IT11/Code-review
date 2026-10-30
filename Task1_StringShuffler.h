#pragma once

#include <string>
#include <vector>
#include <random>

/// <summary>
/// Class responsible for shuffling letters of a given word until it matches the original.
/// </summary>
class CStringShuffler {
public:
    /// <summary>
    /// Default constructor initializing pseudo-random engine.
    /// </summary>
    CStringShuffler();

    /// <summary>
    /// Destructor for CStringShuffler.
    /// </summary>
    ~CStringShuffler();

    /// <summary>
    /// Executes character shuffling loop until generated string equals the original string.
    /// </summary>
    /// <param name="_InputWord">The target word to shuffle.</param>
    /// <returns>Total number of permutation attempts performed (excluding the original word).</returns>
    int ExecuteShuffle(const std::string& _InputWord);

private:
    /// <summary>
    /// Helper method to display a single attempt to console output.
    /// </summary>
    /// <param name="_Attempt">Current string permutation.</param>
    /// <param name="_AttemptIndex">Current attempt number.</param>
    void _PrintAttempt(const std::string& _Attempt, int _AttemptIndex) const;

    std::mt19937 RandomEngine;
};
