#include "Task3_AviationGraph.h"
#include <fstream>
#include <queue>
#include <algorithm>

CAviationGraph::CAviationGraph() {
    CityCount = 0;
}

CAviationGraph::~CAviationGraph() {
}

bool CAviationGraph::LoadFromFile(const std::string& _FilePath) {
    std::ifstream InputFile(_FilePath);
    if (!InputFile.is_open()) {
        return false;
    }

    InputFile >> CityCount;
    AdjacencyMatrix.assign(CityCount, std::vector<int>(CityCount, 0));

    for (int Row = 0; Row < CityCount; ++Row) {
        for (int Column = 0; Column < CityCount; ++Column) {
            InputFile >> AdjacencyMatrix[Row][Column];
        }
    }

    InputFile.close();
    return true;
}

std::vector<int> CAviationGraph::GetCitiesWithFewerLayovers(int _StartCity, int _MaxLayovers) const {
    if (CityCount == 0 || _StartCity < 1 || _StartCity > CityCount) {
        return { -1 };
    }

    int StartIndex = _StartCity - 1;
    std::vector<int> Distance(CityCount, -1);
    std::queue<int> BFSQueue;

    Distance[StartIndex] = 0;
    BFSQueue.push(StartIndex);

    while (!BFSQueue.empty()) {
        int CurrentCity = BFSQueue.front();
        BFSQueue.pop();

        for (int Neighbor = 0; Neighbor < CityCount; ++Neighbor) {
            if (AdjacencyMatrix[CurrentCity][Neighbor] == 1 && Distance[Neighbor] == -1) {
                Distance[Neighbor] = Distance[CurrentCity] + 1;
                BFSQueue.push(Neighbor);
            }
        }
    }

    std::vector<int> ResultCities;
    for (int Index = 0; Index < CityCount; ++Index) {
        if (Index == StartIndex) {
            continue;
        }

        int FlightHops = Distance[Index];
        if (FlightHops != -1) {
            int Layovers = FlightHops - 1;
            if (Layovers < _MaxLayovers) {
                ResultCities.push_back(Index + 1);
            }
        }
    }

    if (ResultCities.empty()) {
        return { -1 };
    }

    std::sort(ResultCities.begin(), ResultCities.end());
    return ResultCities;
}
