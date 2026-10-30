#include "Task2_CalcTree.h"
#include <iostream>

int main() {
    std::cout << "========================================\n";
    std::cout << "   LABORATORY WORK #3 - OPTION 5\n";
    std::cout << "========================================\n\n";

    std::cout << "--- TASK 2: CalcTree6 (Prefix Tree & Power Elimination) ---\n";
    CCalcTree ExpressionTree;
    std::string TreeFileName = "filename.txt";

    if (ExpressionTree.BuildFromPrefixFile(TreeFileName)) {
        std::cout << "Successfully loaded expression tree from " << TreeFileName << "\n";
        ExpressionTree.EliminateExponentiation();
        STreeNode* RootPtr = ExpressionTree.GetRoot();
        std::cout << "Transformed Root Pointer: " << static_cast<void*>(RootPtr) << "\n";
        if (RootPtr != nullptr) {
            std::cout << "Root Node Value: " << RootPtr->Value << "\n";
        }
    }
    else {
        std::cout << "Note: Create '" << TreeFileName << "' to test tree construction.\n";
    }
    std::cout << "\n";

    return 0;
}
