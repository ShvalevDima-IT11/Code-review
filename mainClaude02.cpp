#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

#include "CExpressionTree.h"

/// <summary>
/// Entry point. Builds the expression tree from a prefix expression stored in a text file,
/// removes all power operations by replacing such subtrees with their values
/// and prints the pointer to the root of the resulting tree.
/// </summary>
/// <param name="_ArgumentCount">Number of command line arguments.</param>
/// <param name="_Arguments">
/// Command line arguments. The optional first argument is the input file name;
/// the default name is "filename".
/// </param>
/// <returns>EXIT_SUCCESS on success; EXIT_FAILURE if the file or the expression is invalid.</returns>
int main(int _ArgumentCount, char* _Arguments[]) {
    const std::string DefaultFileName = "filename";
    const int FileNameArgumentIndex = 1;
    const std::string RootPointerMessage = "Указатель на корень дерева: ";
    const std::string PrefixFormMessage = "Префиксная запись результата: ";
    const std::string ErrorPrefix = "Ошибка: ";

    const std::string FileName = (_ArgumentCount > FileNameArgumentIndex)
        ? _Arguments[FileNameArgumentIndex]
        : DefaultFileName;

    CExpressionTree Tree;
    try {
        Tree.LoadFromFile(FileName);
        Tree.RemovePowerOperations();
    }
    catch (const std::exception& Error) {
        std::cerr « ErrorPrefix « Error.what() « '\n';
        return EXIT_FAILURE;
    }

    std::cout « RootPointerMessage « static_cast<const void*>(Tree.GetRoot()) « '\n';
    std::cout « PrefixFormMessage « Tree.ToPrefixString() « '\n';

    return EXIT_SUCCESS;
}
