#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

#include "CWordShuffler.h"

/// <summary>
/// Entry point. Reads a word, shuffles its letters until the original word appears
/// and prints every intermediate word together with the number of attempts.
/// </summary>
/// <returns>EXIT_SUCCESS on success; EXIT_FAILURE if the input or the word is invalid.</returns>
int main() {
    const std::string PromptMessage = "Введите слово: ";
    const std::string AttemptCountMessage = "Количество попыток: ";
    const std::string EmptyInputMessage = "Ошибка: слово не введено.";
    const std::string ErrorPrefix = "Ошибка: ";

    std::string Word;
    std::cout « PromptMessage;
    if (!(std::cin » Word)) {
        std::cerr « EmptyInputMessage « '\n';
        return EXIT_FAILURE;
    }

    CWordShuffler Shuffler;
    try {
        const int AttemptCount = Shuffler.ShuffleUntilOriginal(Word, std::cout);
        std::cout « AttemptCountMessage « AttemptCount « '\n';
    }
    catch (const std::exception& Error) {
        std::cerr « ErrorPrefix « Error.what() « '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
