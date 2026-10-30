#include "CGraphAnalyzer.h"

#include <algorithm>
#include <fstream>
#include <queue>
#include <stdexcept>

CGraphAnalyzer::CGraphAnalyzer(const std::string& FileName) : _CityCount(0) {
    std::ifstream InputFile(FileName);
    if (!InputFile.is_open()) {
        throw std::runtime_error("Cannot open file: " + FileName);
    }

    InputFile >> _CityCount;
    if (_CityCount <= 0) {
        throw std::runtime_error("Invalid city count");
    }

    _AdjacencyMatrix.assign(_CityCount, std::vector<int>(_CityCount, 0));

    for (int Row = 0; Row < _CityCount; ++Row) {
        for (int Column = 0; Column < _CityCount; ++Column) {
            InputFile >> _AdjacencyMatrix[Row][Column];
        }
    }

    if (!InputFile) {
        throw std::runtime_error("Invalid adjacency matrix");
    }
}

std::vector<int> CGraphAnalyzer::FindCitiesWithFewerTransfers(
    int StartCity,
    int MaxTransfers) const {
    std::vector<int> Result;

    if (StartCity < 1 || StartCity > _CityCount || MaxTransfers < 0) {
        return Result;
    }

    const int StartIndex = StartCity - 1;
    std::vector<int> Distance(_CityCount, -1);
    std::queue<int> Queue;

    Distance[StartIndex] = 0;
    Queue.push(StartIndex);

    while (!Queue.empty()) {
        const int Current = Queue.front();
        Queue.pop();

        for (int Neighbor = 0; Neighbor < _CityCount; ++Neighbor) {
            if (_AdjacencyMatrix[Current][Neighbor] == 0) {
                continue;
            }

            if (Distance[Neighbor] != -1) {
                continue;
            }

            const int NewDistance = Distance[Current] + 1;
            if (NewDistance > MaxTransfers) {
                continue;
            }

            Distance[Neighbor] = NewDistance;
            Queue.push(Neighbor);

            if (Neighbor != StartIndex) {
                Result.push_back(Neighbor + 1);
            }
        }
    }

    std::sort(Result.begin(), Result.end());
    return Result;
}

int CGraphAnalyzer::GetCityCount() const {
    return _CityCount;
}
