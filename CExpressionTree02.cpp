#include "CExpressionTree02.h"

#include <cctype>
#include <fstream>
#include <iostream>
#include <stdexcept>

CExpressionTree::CExpressionTree() : _Root(nullptr) {
}

CExpressionTree::~CExpressionTree() {
    _DestroyTree(_Root);
}

void CExpressionTree::BuildFromPrefixFile(const std::string& FileName) {
    std::ifstream InputFile(FileName);
    if (!InputFile.is_open()) {
        throw std::runtime_error("Cannot open file: " + FileName);
    }

    std::string Expression;
    std::getline(InputFile, Expression, '\0');

    _DestroyTree(_Root);
    _Root = nullptr;

    std::size_t Index = 0;
    _Root = _ParsePrefix(Expression, Index);
}

SExpressionNode* CExpressionTree::_ParsePrefix(const std::string& Expression, std::size_t& Index) {
    while (Index < Expression.size() &&
        std::isspace(static_cast<unsigned char>(Expression[Index]))) {
        ++Index;
    }

    if (Index >= Expression.size()) {
        return nullptr;
    }

    const char Token = Expression[Index++];

    if (std::isdigit(static_cast<unsigned char>(Token))) {
        SExpressionNode* Leaf = new SExpressionNode{ Token - '0', nullptr, nullptr };
        return Leaf;
    }

    int OperationCode = 0;
    if (Token == '+') {
        OperationCode = -1;
    }
    else if (Token == '-') {
        OperationCode = -2;
    }
    else if (Token == '*') {
        OperationCode = -3;
    }
    else if (Token == '/') {
        OperationCode = -4;
    }
    else if (Token == '%') {
        OperationCode = -5;
    }
    else if (Token == '^') {
        OperationCode = -6;
    }
    else {
        throw std::runtime_error("Invalid token in expression");
    }

    SExpressionNode* Node = new SExpressionNode{ OperationCode, nullptr, nullptr };
    Node->Left = _ParsePrefix(Expression, Index);
    Node->Right = _ParsePrefix(Expression, Index);

    if (Node->Left == nullptr || Node->Right == nullptr) {
        _DestroyTree(Node);
        throw std::runtime_error("Incomplete expression");
    }

    return Node;
}

void CExpressionTree::TransformPowerSubtreesToValues() {
    _Root = _TransformNode(_Root);
}

SExpressionNode* CExpressionTree::_TransformNode(SExpressionNode* Node) {
    if (Node == nullptr) {
        return nullptr;
    }

    if (_ContainsPower(Node)) {
        const int Value = _EvaluateNode(Node);
        _DestroyTree(Node);
        return new SExpressionNode{ Value, nullptr, nullptr };
    }

    Node->Left = _TransformNode(Node->Left);
    Node->Right = _TransformNode(Node->Right);
    return Node;
}

bool CExpressionTree::_ContainsPower(const SExpressionNode* Node) const {
    if (Node == nullptr) {
        return false;
    }

    if (Node->Value == -6) {
        return true;
    }

    return _ContainsPower(Node->Left) || _ContainsPower(Node->Right);
}

int CExpressionTree::_EvaluateNode(const SExpressionNode* Node) const {
    if (Node == nullptr) {
        throw std::runtime_error("Null node");
    }

    if (Node->Value >= 0) {
        return Node->Value;
    }

    const int LeftValue = _EvaluateNode(Node->Left);
    const int RightValue = _EvaluateNode(Node->Right);

    switch (Node->Value) {
    case -1:
        return LeftValue + RightValue;
    case -2:
        return LeftValue - RightValue;
    case -3:
        return LeftValue * RightValue;
    case -4:
        if (RightValue == 0) {
            throw std::runtime_error("Division by zero");
        }
        return LeftValue / RightValue;
    case -5:
        if (RightValue == 0) {
            throw std::runtime_error("Modulo by zero");
        }
        return LeftValue % RightValue;
    case -6:
        return _IntegerPower(LeftValue, RightValue);
    default:
        throw std::runtime_error("Unknown operation");
    }
}

int CExpressionTree::_IntegerPower(int Base, int Exponent) const {
    if (Exponent < 0) {
        throw std::runtime_error("Negative exponent is not supported");
    }

    int Result = 1;
    for (int Step = 0; Step < Exponent; ++Step) {
        Result *= Base;
    }
    return Result;
}

void CExpressionTree::PrintPrefix(std::ostream& Out) const {
    _PrintPrefixNode(_Root, Out);
    Out << '\n';
}

void CExpressionTree::_PrintPrefixNode(const SExpressionNode* Node, std::ostream& Out) const {
    if (Node == nullptr) {
        return;
    }

    if (Node->Value >= 0) {
        Out << Node->Value << ' ';
    }
    else {
        char Operation = '?';
        if (Node->Value == -1) {
            Operation = '+';
        }
        else if (Node->Value == -2) {
            Operation = '-';
        }
        else if (Node->Value == -3) {
            Operation = '*';
        }
        else if (Node->Value == -4) {
            Operation = '/';
        }
        else if (Node->Value == -5) {
            Operation = '%';
        }
        else if (Node->Value == -6) {
            Operation = '^';
        }
        Out << Operation << ' ';
    }

    _PrintPrefixNode(Node->Left, Out);
    _PrintPrefixNode(Node->Right, Out);
}

void CExpressionTree::PrintRootPointer(std::ostream& Out) const {
    Out << static_cast<const void*>(_Root) << '\n';
}

const SExpressionNode* CExpressionTree::GetRoot() const {
    return _Root;
}

int CExpressionTree::Evaluate() const {
    return _EvaluateNode(_Root);
}

void CExpressionTree::_DestroyTree(SExpressionNode* Node) {
    if (Node == nullptr) {
        return;
    }

    _DestroyTree(Node->Left);
    _DestroyTree(Node->Right);
    delete Node;
}
