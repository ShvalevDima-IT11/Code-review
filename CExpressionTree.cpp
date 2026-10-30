#include "CExpressionTree.h"

#include <cctype>
#include <fstream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string_view>

#include "EOperation.h"
#include "SNode.h"

namespace {

    /// <summary>Symbols that denote operations.</summary>
    constexpr std::string_view OperationSymbols = "+-*/%^";

    constexpr char AdditionSymbol = '+';
    constexpr char SubtractionSymbol = '-';
    constexpr char MultiplicationSymbol = '*';
    constexpr char DivisionSymbol = '/';
    constexpr char RemainderSymbol = '%';
    constexpr char PowerSymbol = '^';

    /// <summary>Symbol of the smallest operand.</summary>
    constexpr char ZeroDigit = '0';

    /// <summary>Symbol of the largest operand.</summary>
    constexpr char NineDigit = '9';

    /// <summary>Byte order mark that some editors put at the start of UTF-8 files.</summary>
    const std::string Utf8ByteOrderMark = "\xEF\xBB\xBF";

    /// <summary>Separator between tokens in the diagnostic output.</summary>
    constexpr char TokenSeparator = ' ';

    /// <summary>Checks whether a symbol is an operand (a digit from 0 to 9).</summary>
    /// <param name="_Symbol">Symbol to check.</param>
    /// <returns>True if the symbol is a digit; otherwise false.</returns>
    bool IsOperandSymbol(char _Symbol) {
        return _Symbol >= ZeroDigit && _Symbol <= NineDigit;
    }

    /// <summary>Checks whether a symbol denotes an operation.</summary>
    /// <param name="_Symbol">Symbol to check.</param>
    /// <returns>True if the symbol is one of + - * / % ^; otherwise false.</returns>
    bool IsOperationSymbol(char _Symbol) {
        return OperationSymbols.find(_Symbol) != std::string_view::npos;
    }

    /// <summary>Converts an operation symbol to the operation code.</summary>
    /// <param name="_Symbol">One of + - * / % ^.</param>
    /// <returns>Corresponding operation.</returns>
    /// <exception cref="std::invalid_argument">The symbol is not an operation.</exception>
    EOperation ToOperation(char _Symbol) {
        switch (_Symbol) {
        case AdditionSymbol:
            return EOperation::Addition;
        case SubtractionSymbol:
            return EOperation::Subtraction;
        case MultiplicationSymbol:
            return EOperation::Multiplication;
        case DivisionSymbol:
            return EOperation::Division;
        case RemainderSymbol:
            return EOperation::Remainder;
        case PowerSymbol:
            return EOperation::Power;
        default:
            throw std::invalid_argument("Unknown operation symbol");
        }
    }

    /// <summary>Converts an operation code to its symbol.</summary>
    /// <param name="_Operation">Operation to convert.</param>
    /// <returns>One of + - * / % ^.</returns>
    /// <exception cref="std::logic_error">The operation code is unknown.</exception>
    char ToSymbol(EOperation _Operation) {
        switch (_Operation) {
        case EOperation::Addition:
            return AdditionSymbol;
        case EOperation::Subtraction:
            return SubtractionSymbol;
        case EOperation::Multiplication:
            return MultiplicationSymbol;


        case EOperation::Division:
            return DivisionSymbol;
        case EOperation::Remainder:
            return RemainderSymbol;
        case EOperation::Power:
            return PowerSymbol;
        default:
            throw std::logic_error("Unknown operation code");
        }
    }

    /// <summary>Checks whether a node has no children.</summary>
    /// <param name="_Node">Node to check.</param>
    /// <returns>True if the node is a leaf; otherwise false.</returns>
    bool IsLeaf(const SNode& _Node) {
        return _Node.Left == nullptr && _Node.Right == nullptr;
    }

    /// <summary>Checks whether a node is the power operation.</summary>
    /// <param name="_Node">Node to check.</param>
    /// <returns>True if the node is an inner node with the power operation; otherwise false.</returns>
    bool IsPowerNode(const SNode& _Node) {
        return !IsLeaf(_Node) && _Node.Data == static_cast<int>(EOperation::Power);
    }

    /// <summary>Creates a leaf node.</summary>
    /// <param name="_Value">Operand value.</param>
    /// <returns>Owning pointer to the new leaf.</returns>
    std::unique_ptr<SNode> CreateLeaf(int _Value) {
        std::unique_ptr<SNode> Leaf = std::make_unique<SNode>();
        Leaf->Data = _Value;
        return Leaf;
    }

    /// <summary>Skips white space in an expression.</summary>
    /// <param name="_Expression">Expression to scan.</param>
    /// <param name="_Position">Index to advance to the next non-white-space symbol.</param>
    void SkipWhiteSpace(const std::string& _Expression, std::size_t& _Position) {
        while (_Position < _Expression.size()
            && std::isspace(static_cast<unsigned char>(_Expression[_Position])) != 0) {
            ++_Position;
        }
    }

    /// <summary>Narrows a wide result to int and checks the range.</summary>
    /// <param name="_Value">Result computed in a wider type.</param>
    /// <returns>The same value as int.</returns>
    /// <exception cref="std::overflow_error">The value does not fit into int.</exception>
    int ToCheckedInt(long long _Value) {
        if (_Value < std::numeric_limits<int>::min() || _Value > std::numeric_limits<int>::max()) {
            throw std::overflow_error("Result does not fit into int");
        }
        return static_cast<int>(_Value);
    }

    /// <summary>
    /// Raises an integer to an integer power using truncating integer semantics
    /// (a negative exponent gives 1/Base^N rounded toward zero).
    /// </summary>
    /// <param name="_Base">Base of the power.</param>
    /// <param name="_Exponent">Exponent of the power.</param>
    /// <returns>The value of _Base ^ _Exponent.</returns>
    /// <exception cref="std::domain_error">Zero is raised to a negative power.</exception>
    /// <exception cref="std::overflow_error">The result does not fit into int.</exception>
    int IntegerPower(int _Base, int _Exponent) {
        if (_Exponent == 0) {
            return 1;
        }
        if (_Base == 0) {
            if (_Exponent < 0) {
                throw std::domain_error("Zero cannot be raised to a negative power");
            }
            return 0;
        }
        if (_Base == 1) {
            return 1;
        }
        if (_Base == -1) {
            return (_Exponent % 2 == 0) ? 1 : -1;
        }
        if (_Exponent < 0) {
            return 0;
        }

        // Here |_Base| >= 2, so the loop leaves through the overflow check after at most 32 steps.
        long long Result = 1;
        for (int Step = 0; Step < _Exponent; ++Step) {
            Result = ToCheckedInt(Result * _Base);
        }
        return static_cast<int>(Result);
    }

    /// <summary>Computes the value of a subtree with int arithmetic.</summary>
    /// <param name="_Node">Root of the subtree.</param>
    /// <returns>Value of the subtree.</returns>
    /// <exception cref="std::domain_error">Division or remainder by zero, or zero to a negative power.</exception>
    /// <exception cref="std::overflow_error">An intermediate result does not fit into int.</exception>
    int Evaluate(const SNode& _Node) {
        if (IsLeaf(_Node)) {
            return _Node.Data;
        }

        const int LeftValue = Evaluate(*_Node.Left);
        const int RightValue = Evaluate(*_Node.Right);

        switch (static_cast<EOperation>(_Node.Data)


            ) {
        case EOperation::Addition:
            return ToCheckedInt(static_cast<long long>(LeftValue) + RightValue);
        case EOperation::Subtraction:
            return ToCheckedInt(static_cast<long long>(LeftValue) - RightValue);
        case EOperation::Multiplication:
            return ToCheckedInt(static_cast<long long>(LeftValue) * RightValue);
        case EOperation::Division:
            if (RightValue == 0) {
                throw std::domain_error("Division by zero");
            }
            return ToCheckedInt(static_cast<long long>(LeftValue) / RightValue);
        case EOperation::Remainder:
            if (RightValue == 0) {
                throw std::domain_error("Remainder of division by zero");
            }
            return ToCheckedInt(static_cast<long long>(LeftValue) % RightValue);
        case EOperation::Power:
            return IntegerPower(LeftValue, RightValue);
        default:
            throw std::logic_error("Unknown operation code");
        }
    }

    /// <summary>Appends the prefix form of a subtree to a string.</summary>
    /// <param name="_Node">Root of the subtree.</param>
    /// <param name="_Result">String that receives the tokens.</param>
    void AppendPrefix(const SNode& _Node, std::string& _Result) {
        if (!_Result.empty()) {
            _Result.push_back(TokenSeparator);
        }

        if (IsLeaf(_Node)) {
            _Result += std::to_string(_Node.Data);
            return;
        }

        _Result.push_back(ToSymbol(static_cast<EOperation>(_Node.Data)));
        AppendPrefix(*_Node.Left, _Result);
        AppendPrefix(*_Node.Right, _Result);
    }

} // namespace

CExpressionTree::CExpressionTree() {
}

CExpressionTree::~CExpressionTree() {
}

void CExpressionTree::LoadFromFile(const std::string& _FileName) {
    std::ifstream InputFile(_FileName);
    if (!InputFile.is_open()) {
        throw std::runtime_error("Cannot open file: " + _FileName);
    }

    std::ostringstream Buffer;
    Buffer « InputFile.rdbuf();
    std::string Content = Buffer.str();

    if (Content.compare(0, Utf8ByteOrderMark.size(), Utf8ByteOrderMark) == 0) {
        Content.erase(0, Utf8ByteOrderMark.size());
    }

    BuildFromPrefix(Content);
}

void CExpressionTree::BuildFromPrefix(const std::string& _Expression) {
    std::size_t Position = 0;
    std::unique_ptr<SNode> NewRoot = _ParseNode(_Expression, Position);

    SkipWhiteSpace(_Expression, Position);
    if (Position < _Expression.size()) {
        throw std::invalid_argument("Unexpected symbols after the end of the expression");
    }

    Root = std::move(NewRoot);
}

void CExpressionTree::RemovePowerOperations() {
    _CollapsePowers(Root);
}

bool CExpressionTree::IsEmpty() const {
    return Root == nullptr;
}

const SNode* CExpressionTree::GetRoot() const {
    return Root.get();
}

std::string CExpressionTree::ToPrefixString() const {
    std::string Result;
    if (Root != nullptr) {
        AppendPrefix(*Root, Result);
    }
    return Result;
}

std::unique_ptr<SNode> CExpressionTree::_ParseNode(const std::string& _Expression,
    std::size_t& _Position) const {
    SkipWhiteSpace(_Expression, _Position);
    if (_Position >= _Expression.size()) {
        throw std::invalid_argument("Unexpected end of the expression");
    }

    const char Symbol = _Expression[_Position];
    ++_Position;

    if (IsOperandSymbol(Symbol)) {
        return CreateLeaf(Symbol - ZeroDigit);
    }
    if (!IsOperationSymbol(Symbol)) {
        throw std::invalid_argument(std::string("Unexpected symbol: ") + Symbol);
    }

    std::unique_ptr<SNode> Node = std::make_unique<SNode>();
    Node->Data = static_cast<int>(ToOperation(Symbol));
    Node->Left = _ParseNode(_Expression, _Position);
    Node->Right = _ParseNode(_Expression, _Position);
    return Node;
}

void CExpressionTree::_CollapsePowers(std::unique_ptr<SNode>& _Node) const {
    if (_Node == nullptr) {
        return;
    }

    if (IsPowerNode(*_Node)) {
        const int Value = E


            valuate(*_Node);
        _Node = CreateLeaf(Value);
        return;
    }

    _CollapsePowers(_Node->Left);
    _CollapsePowers(_Node->Right);
}
