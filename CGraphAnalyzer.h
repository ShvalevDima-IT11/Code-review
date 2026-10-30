#pragma once

#include <string>
#include <vector>

/// <summary>
/// Analyzes an undirected graph represented by an adjacency matrix.
/// </summary>
class CGraphAnalyzer {
public:
    /// <summary>
    /// Loads a graph from a file.
    /// </summary>
    /// <param name="FileName">Path to the file: first line n, then n lines of adjacency matrix.</param>
    explicit CGraphAnalyzer(const std::string& FileName);

    /// <summary>
    /// Finds cities reachable from StartCity with fewer than MaxTransfers transfers.
    /// A direct flight has 0 transfers. A path with E edges has E - 1 transfers.
    /// </summary>
    /// <param name="StartCity">1-based start city number.</param>
    /// <param name="MaxTransfers">Exclusive upper bound for the number of transfers.</param>
    /// <returns>Sorted 1-based city numbers excluding the start city.</returns>
    std::vector<int> FindCitiesWithFewerTransfers(int StartCity, int MaxTransfers) const;

    /// <summary>
    /// Returns the number of cities in the graph.
    /// </summary>
    /// <returns>City count.</returns>
    int GetCityCount() const;

private:
    std::vector<std::vector<int>> _AdjacencyMatrix;
    int _CityCount;
};
