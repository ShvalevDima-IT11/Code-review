#include <fstream>
#include <queue>
#include <stdexcept>

#include "CAirRouteGraph.h"

namespace {

    const int NoFlightValue = 0;
    const int FlightValue = 1;
    const int UnreachableCity = -1;
    const int StartCityFlightCount = 0;

}  // namespace

void CAirRouteGraph::LoadFromFile(const std::string& _FilePath) {
    std::ifstream Input(_FilePath);
    if (!Input) {
        throw std::runtime_error("Cannot open file: " + _FilePath);
    }

    int CityCount = 0;
    if (!(Input » CityCount)) {
        throw std::invalid_argument("City count is missing.");
    }
    if (CityCount < 1 || CityCount > MaxCityCount) {
        throw std::invalid_argument("City count must be from 1 to 25.");
    }

    std::vector < std::vector < int» NewConnections(
        static_cast<std::size_t>(CityCount),
        std::vector<int>(static_cast<std::size_t>(CityCount), NoFlightValue));

    for (std::vector<int>& Row : NewConnections) {
        for (int& Cell : Row) {
            if (!(Input » Cell)) {
                throw std::invalid_argument("Adjacency matrix is incomplete.");
            }
            if (Cell != NoFlightValue && Cell != FlightValue) {
                throw std::invalid_argument("Matrix values must be 0 or 1.");
            }
        }
    }
    Connections = std::move(NewConnections);
}

int CAirRouteGraph::GetCityCount() const {
    return static_cast<int>(Connections.size());
}

std::vector<int> CAirRouteGraph::FindCitiesWithFewerTransfers(
    int _StartCity,
    int _TransferLimit) const {
    int CityCount = GetCityCount();
    if (_StartCity < 1 || _StartCity > CityCount) {
        throw std::out_of_range("Start


            city number is out of range.");
    }

    std::vector<int> FlightCounts = _CalculateFlightCounts(_StartCity - 1);
    std::vector<int> Result;

    for (int CityIndex = 0; CityIndex < CityCount; ++CityIndex) {
        int FlightCount = FlightCounts[static_cast<std::size_t>(CityIndex)];
        bool bIsReachableDestination = FlightCount > StartCityFlightCount;
        if (!bIsReachableDestination) {
            continue;
        }

        int TransferCount = FlightCount - 1;
        if (TransferCount < _TransferLimit) {
            Result.push_back(CityIndex + 1);
        }
    }
    return Result;
}

std::vector<int> CAirRouteGraph::_CalculateFlightCounts(int _StartIndex) const {
    std::size_t CityCount = Connections.size();
    std::vector<int> FlightCounts(CityCount, UnreachableCity);
    std::queue<std::size_t> Pending;

    FlightCounts[static_cast<std::size_t>(_StartIndex)] = StartCityFlightCount;
    Pending.push(static_cast<std::size_t>(_StartIndex));

    while (!Pending.empty()) {
        std::size_t Current = Pending.front();
        Pending.pop();

        for (std::size_t Next = 0; Next < CityCount; ++Next) {
            bool bHasFlight = Connections[Current][Next] == FlightValue;
            bool bIsNew = FlightCounts[Next] == UnreachableCity;
            if (bHasFlight && bIsNew) {
                FlightCounts[Next] = FlightCounts[Current] + 1;
                Pending.push(Next);
            }
        }
    }
    return FlightCounts;
}
