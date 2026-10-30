#pragma once

#include <cstddef>
#include <iosfwd>
#include <string>

/// <summary>
/// Node of an arithmetic expression tree.
/// </summary>
struct SExpressionNode {
    int Value;              ///< Digit 0-9 or operation code: -1 (+), -2 (-), -3 (*), -4 (/), -5 (%), -6 (^).
    SExpressionNode* Left;  ///< Left child.
    SExpressionNode* Right; ///< Right child.
};

/// <summary>
/// Builds and transforms an arithmetic expression tree from prefix notation.
/// Supports +, -, *, /, %, ^.
/// </summary>
class CExpressionTree {
public:
    CExpressionTree();
    ~CExpressionTree();

    CExpressionTree(const CExpressionTree&) = delete;
    CExpressionTree& operator=(const CExpressionTree&) = delete;

    /// <summary>
    /// Reads a prefix expression from a text file and builds the tree.
    /// </summary>
    /// <param name="FileName">Path to the text file with the expression.</param>
    void BuildFromPrefixFile(const std::string& FileName);

    /// <summary>
    /// Replaces every subtree containing exponentiation by its computed value.
    /// </summary>
    void TransformPowerSubtreesToValues();

    /// <summary>
    /// Prints the tree in prefix notation.
    /// </summary>
    /// <param name="Out">Output stream.</param>
    void PrintPrefix(std::ostream& Out) const;

    /// <summary>
    /// Prints the address of the root pointer.
    /// </summary>
    /// <param name="Out">Output stream.</param>
    void PrintRootPointer(std::ostream& Out) const;

    /// <summary>
    /// Returns the root node pointer.
    /// </summary>
    /// <returns>Root pointer or nullptr if the tree is empty.</returns>
    const SExpressionNode* GetRoot() const;

    /// <summary>
    /// Evaluates the whole tree.
    /// </summary>
    /// <returns>Integer result of the expression.</returns>
    int Evaluate() const;

private:
    SExpressionNode* _Root;

    SExpressionNode* _ParsePrefix(const std::string& Expression, std::size_t& Index);
    SExpressionNode* _TransformNode(SExpressionNode* Node);
    bool _ContainsPower(const SExpressionNode* Node) const;
    int _EvaluateNode(const SExpressionNode* Node) const;
    int _IntegerPower(int Base, int Exponent) const;
    void _PrintPrefixNode(const SExpressionNode* Node, std::ostream& Out) const;
    void _DestroyTree(SExpressionNode* Node);
};
