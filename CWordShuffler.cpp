#include "CWordShuffler.h"

#include <algorithm>
#include <stdexcept>

namespace {

    /// <summary>Mask that isolates the two leading bits of a UTF-8 byte.</summary>
    constexpr unsigned char ContinuationMask = 0xC0;

    /// <summary>Value of the two leading bits of a UTF-8 continuation byte (10xxxxxx).</summary>
    constexpr unsigned char ContinuationValue = 0x80;

    /// <summary>Error text for words that exceed the allowed length.</summary>
    const char* const WordTooLongMessage = "Word has too many letters to be shuffled";

} // namespace

CWordShuffler::CWordShuffler()
    : RandomEngine(std::random_device()()) {
}

bool CWordShuffler::IsWordTooLong(const std::string& _Word) const {
    return _SplitIntoLetters(_Word).size() > static_cast<std::size_t>(MaxLetterCount);
}

int CWordShuffler::ShuffleUntilOriginal(const std::string& _Word, std::ostream& _Output) {
    if (IsWordTooLong(_Word)) {
        throw std::length_error(WordTooLongMessage);
    }

    const std::vector<std::string> OriginalLetters = _SplitIntoLetters(_Word);
    if (OriginalLetters.empty()) {
        return 0;
    }

    std::vector<std::string> ShuffledLetters = OriginalLetters;
    int AttemptCount = 0;
    bool bIsOriginalRestored = false;

    while (!bIsOriginalRestored) {
        std::shuffle(ShuffledLetters.begin(), ShuffledLetters.end(), RandomEngine);
        _Output «


            _JoinLetters(ShuffledLetters) « '\n';
        ++AttemptCount;
        bIsOriginalRestored = (ShuffledLetters == OriginalLetters);
    }

    return AttemptCount;
}

std::vector<std::string> CWordShuffler::_SplitIntoLetters(const std::string& _Word) const {
    std::vector<std::string> Letters;

    for (const char Byte : _Word) {
        const unsigned char UnsignedByte = static_cast<unsigned char>(Byte);
        const bool bIsContinuationByte = (UnsignedByte & ContinuationMask) == ContinuationValue;

        if (bIsContinuationByte && !Letters.empty()) {
            Letters.back().push_back(Byte);
        }
        else {
            Letters.push_back(std::string(1, Byte));
        }
    }

    return Letters;
}

std::string CWordShuffler::_JoinLetters(const std::vector<std::string>& _Letters) const {
    std::string Word;

    for (const std::string& Letter : _Letters) {
        Word += Letter;
    }

    return Word;
}
