#include "Task2_CalcTree.h"
#include <fstream>
#include <iostream>
#include <cmath>

CCalcTree::CCalcTree() {
    RootNode = nullptr;
}

CCalcTree::~CCalcTree() {
    _ClearTree(RootNode);
}

bool CCalcTree::BuildFromPrefixFile(const std::string& _FilePath) {
    std::ifstream InputFile(_FilePath);
    if (!InputFile.is_open()) {
        return false;
    }

    _ClearTree(RootNode);
    RootNode = _ParsePrefixStream(InputFile);
    InputFile.close();
    return (RootNode != nullptr);
}

STreeNode* CCalcTree::_ParsePrefixStream(std::istream& _Stream) {
    std::string Token;
    if (!(_Stream >> Token)) {
        return nullptr;
    }

    int NodeValue = 0;
    bool bIsOperator = false;

    if (Token == "+") {
        NodeValue = static_cast<int>(EOperatorType::Addition);
        bIsOperator = true;
    }
    else if (Token == "-") {
        NodeValue = static_cast<int>(EOperatorType::Subtraction);
        bIsOperator = true;
    }
    else if (Token == "*") {
        NodeValue = static_cast<int>(EOperatorType::Multiplication);
        bIsOperator = true;
    }
    else if (Token == "/") {
        NodeValue = static_cast<int>(EOperatorType::Division);
        bIsOperator = true;
    }
    else if (Token == "%") {
        NodeValue = static_cast<int>(EOperatorType::Modulo);
        bIsOperator = true;
    }
    else if (Token == "^") {
        NodeValue = static_cast<int>(EOperatorType::Exponentiation);
        bIsOperator = true;
    }
    else {
        NodeValue = std::stoi(Token);
    }

    STreeNode* NewNode = new STreeNode(NodeValue);

    if (bIsOperator) {
        NewNode->LeftChild = _ParsePrefixStream(_Stream);
        NewNode->RightChild = _ParsePrefixStream(_Stream);
    }

    return NewNode;
}

void CCalcTree::EliminateExponentiation() {
    _TransformAndEvaluate(RootNode);
}

void CCalcTree::_TransformAndEvaluate(STreeNode*& _Node) {
    if (_Node == nullptr) {
        return;
    }

    _TransformAndEvaluate(_Node->LeftChild);
    _TransformAndEvaluate(_Node->RightChild);

    if (_HasExponentiation(_Node)) {
        int CalculatedVal = _EvaluateSubtree(_Node);
        _ClearTree(_Node->LeftChild);
        _ClearTree(_Node->RightChild);
        _Node->LeftChild = nullptr;
        _Node->RightChild = nullptr;
        _Node->Value = CalculatedVal;
    }
}

bool CCalcTree::_HasExponentiation(STreeNode* _Node) const {
    if (_Node == nullptr) {
        return false;
    }
    if (_Node->Value == static_cast<int>(EOperatorType::Exponentiation)) {
        return true;
    }
    return _HasExponentiation(_Node->LeftChild) || _HasExponentiation(_Node->RightChild);
}

int CCalcTree::_EvaluateSubtree(STreeNode* _Node) const {
    if (_Node == nullptr) {
        return 0;
    }

    if (_Node->LeftChild == nullptr && _Node->RightChild == nullptr) {
        return _Node->Value;
    }

    int LeftVal = _EvaluateSubtree(_Node->LeftChild);
    int RightVal = _EvaluateSubtree(_Node->RightChild);

    EOperatorType Op = static_cast<EOperatorType>(_Node->Value);
    switch (Op) {
    case EOperatorType::Addition:
        return LeftVal + RightVal;
    case EOperatorType::Subtraction:
        return LeftVal - RightVal;
    case EOperatorType::Multiplication:
        return LeftVal * RightVal;
    case EOperatorType::Division:
        return (RightVal != 0) ? (LeftVal / RightVal) : 0;
    case EOperatorType::Modulo:
        return (RightVal != 0) ? (LeftVal % RightVal) : 0;
    case EOperatorType::Exponentiation:
        return _Power(LeftVal, RightVal);
    default:
        return 0;
    }
}

int CCalcTree::_Power(int _Base, int _Exponent) const {
    int Result = 1;
    for (int Index = 0; Index < _Exponent; ++Index) {
        Result *= _Base;
    }
    return Result;
}

STreeNode* CCalcTree::GetRoot() const {
    return RootNode;
}

void CCalcTree::_ClearTree(STreeNode* _Node) {
    if (_Node != nullptr) {
        _ClearTree(_Node->LeftChild);
        _ClearTree(_Node->RightChild);
        delete _Node;
    }
}
