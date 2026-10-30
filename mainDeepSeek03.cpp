#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "CGraphAnalyzer.h"

int main() {
    std::string FileName;
    std::cout << "Enter file name for graph: ";
    std::getline(std::cin, FileName);

    int StartCity = 0;
    int MaxTransfers = 0;

    std::cout << "Enter start city (1-based): ";
    std::cin >> StartCity;
    std::cout << "Enter L (fewer than L transfers): ";
    std::cin >> MaxTransfers;

    try {
        CGraphAnalyzer Graph(FileName);
        const std::vector<int> Cities =
            Graph.FindCitiesWithFewerTransfers(StartCity, MaxTransfers);

        if (Cities.empty()) {
            std::cout << -1 << '\n';
        }
        else {
            for (int City : Cities) {
                std::cout << City << ' ';
            }
            std::cout << '\n';
        }
    }
    catch (const std::exception& Exception) {
        std::cerr << "Error: " << Exception.what() << '\n';
        return 1;
    }

    return 0;
}
