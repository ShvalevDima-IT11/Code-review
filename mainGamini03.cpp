#include "Task3_AviationGraph.h"
#include <iostream>

int main() {
    std::cout << "========================================\n";
    std::cout << "   LABORATORY WORK #3 - OPTION 5\n";
    std::cout << "========================================\n\n";

    std::cout << "--- TASK 3: Graf5 (Aviation Reachability BFS) ---\n";
    CAviationGraph FlightNetwork;
    std::string GraphFileName = "FileName.txt";

    if (FlightNetwork.LoadFromFile(GraphFileName)) {
        int StartCity = 1;
        int MaxLayovers = 2;
        std::vector<int> ReachableCities = FlightNetwork.GetCitiesWithFewerLayovers(StartCity, MaxLayovers);

        std::cout << "Cities reachable from city " << StartCity
            << " with < " << MaxLayovers << " layover(s): ";
        for (int City : ReachableCities) {
            std::cout << City << " ";
        }
        std::cout << "\n";
    }
    else {
        std::cout << "Note: Create '" << GraphFileName << "' to test graph reachability.\n";
    }

    return 0;
}
