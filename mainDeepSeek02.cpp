#include <exception>
#include <iostream>
#include <string>

#include "CExpressionTree02.h"

int main() {
    std::string FileName;
    std::cout << "Enter file name for expression: ";
    std::getline(std::cin, FileName);

    try {
        CExpressionTree Tree;
        Tree.BuildFromPrefixFile(FileName);

        std::cout << "Original prefix: ";
        Tree.PrintPrefix(std::cout);
        std::cout << "Original value: " << Tree.Evaluate() << '\n';

        Tree.TransformPowerSubtreesToValues();

        std::cout << "Transformed prefix: ";
        Tree.PrintPrefix(std::cout);
        std::cout << "Root pointer: ";
        Tree.PrintRootPointer(std::cout);
    }
    catch (const std::exception& Exception) {
        std::cerr << "Error: " << Exception.what() << '\n';
        return 1;
    }

    return 0;
}
