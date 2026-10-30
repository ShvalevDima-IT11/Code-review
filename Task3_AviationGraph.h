#pragma once

#include <string>
#include <vector>

/// <summary>
/// Class representing aviation network adjacency matrix and flight queries.
/// </summary>
class CAviationGraph {
public:
    /// <summary>
    /// Constructor.
    /// </summary>
    CAviationGraph();

    /// <summary>
    /// Destructor.
    /// </summary>
    ~CAviationGraph();

    /// <summary>
    /// Loads adjacency matrix from file.
    /// </summary>
    /// <param name="_FilePath">Path to text file containing graph definition.</param>
    /// <returns>True on successful file read.</returns>
    bool LoadFromFile(const std::string& _FilePath);

    /// <summary>
    /// Finds all cities reachable from StartCity with strictly fewer than MaxLayovers layovers.
    /// </summary>
    /// <param name="_StartCity">1-based index of starting city K.</param>
    /// <param name="_MaxLayovers">Upper bound threshold for layovers L.</param>
    /// <returns>Vector of 1-based sorted city indices, or {-1} if none exist.</returns>
    std::vector<int> GetCitiesWithFewerLayovers(int _StartCity, int _MaxLayovers) const;

private:
    int CityCount;
    std::vector<std::vector<int>> AdjacencyMatrix;
};
