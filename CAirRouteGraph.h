#pragma once

#include <string>
#include <vector>

/// <summary>
/// Directed graph of air connections between cities, stored as an adjacency
/// matrix. Cities are numbered from 1 in the public interface.
/// </summary>
class CAirRouteGraph {
public:
    /// Maximum number of cities allowed by the task statement.
    static constexpr int MaxCityCount = 25;

    /// <summary>
    /// Loads the graph from a text file: the first number is the city count n,
    /// followed by n rows of n values (0 = no flight, 1 = flight i -> j).
    /// </summary>
    /// <param name="_FilePath">Path to the text file.</param>
    /// <exception cref="std::runtime_error">The file cannot be opened.</exception>
    /// <exception cref="std::invalid_argument">The file content is invalid.</exception>
    void LoadFromFile(const std::string& _FilePath);

    /// <summary>
    /// Gets the number of cities in the loaded graph.
    /// </summary>
    /// <returns>City count (0 when nothing is loaded).</returns>
    int GetCityCount() const;

    /// <summary>
    /// Finds all cities that can be reached from the start city with fewer
    /// than the given number of transfers. A route of F flights has F - 1
    /// transfers; the start city itself is never included.
    /// </summary>
    /// <param name="_StartCity">Start city number, from 1 to the city count.</param>
    /// <param name="_TransferLimit">Exclusive upper bound for transfers (L).</param>
    /// <returns>City numbers in ascending order (empty if there are none).</returns>
    /// <exception cref="std::out_of_range">The start city number is invalid.</exception>
    std::vector<int> FindCitiesWithFewerTransfers(int _StartCity,
        int _TransferLimit) const;

private:
    /// <summary>
    /// Runs breadth-first search and measures the flight count to each city.
    /// </summary>
    /// <param name="_StartIndex">Zero-based index of the start city.</param>
    /// <returns>Minimal flight count per city; -1 for unreachable cities.</returns>
    std::vector<int> _CalculateFlightCounts(int _StartIndex) const;

    /// Adjacency matrix: Connections[i][j] is 1 if a flight i -> j exists.
    std::vector < std::vector < int» Connections;
};
