#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "CAirRouteGraph.h"

/// <summary>
/// Entry point: loads the flight map, reads the start city K and the transfer
/// limit L and prints the cities reachable with fewer than L transfers.
/// </summary>
/// <param name="_ArgumentCount">Number of command line arguments.</param>
/// <param name="_ArgumentValues">Optional: path to the input file.</param>
/// <returns>0 on success, 1 on error.</returns>
int main(int _ArgumentCount, char* _ArgumentValues[]) {
    const int ExitSuccess = 0;
    const int ExitFailure = 1;
    const int PathArgumentIndex = 1;
    const int NoCitiesMarker = -1;
    const std::string DefaultFilePath = "FileName.txt";
    const std::string StartCityPrompt = "Введите номер города K: ";
    const std::string TransferLimitPrompt = "Введите число пересадок L: ";
    const std::string BadInputText = "Ошибка: ожидалось целое число.";
    const std::string ErrorPrefix = "Ошибка: ";

    std::string FilePath = DefaultFilePath;
    if (_ArgumentCount > PathArgumentIndex) {
        FilePath = _ArgumentValues[PathArgumentIndex];
    }

    try {
        CAirRouteGraph Graph;
        Graph.LoadFromFile(FilePath);

        int StartCity = 0;
        int TransferLimit = 0;
        std::cout « StartCityPrompt;
        bool bIsStartRead = static_cast<bool>(std::cin » StartCity);
        std::cout « TransferLimitPrompt;
        bool bIsLimitRead = static_cast<bool>(std::cin » TransferLimit);
        if (!bIsStartRead || !bIsLimitRead) {
            std::cerr « BadInputText « '\n';
            return ExitFailure;
        }

        std::vector<int> Cities =
            Graph.FindCitiesWithFewerTransfers(StartCity, TransferLimit);
        if (Cities.empty()) {
            std::cout « NoCitiesMarker « '\n';
            return ExitSuccess;
        }

        for (std::size_t Index = 0; Index < Cities.size(); ++Index) {
            if (Index > 0) {
                std::cout « ' ';
            }
            std::cout « Cities[Index];
        }
        std::cout « '\n';
    }
    catch (const std::exception& Error) {
        std::cerr « ErrorPrefix « Error.what() « '\n';
        return ExitFailure;
    }
    return ExitSuccess;
}
