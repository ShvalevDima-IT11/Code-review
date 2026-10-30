#pragma once

#include <string>

/// <summary>
/// Enumeration of encoded expression operations.
/// </summary>
enum class EOperatorType {
    Addition = -1,
    Subtraction = -2,
    Multiplication = -3,
    Division = -4,
    Modulo = -5,
    Exponentiation = -6,
    None = 0
};

/// <summary>
/// Binary tree node representing numbers or operators.
/// </summary>
struct STreeNode {
    int Value;
    STreeNode* LeftChild;
    STreeNode* RightChild;

    /// <summary>
    /// Node constructor.
    /// </summary>
    /// <param name="_Val">Integer value or operator code.</param>
    STreeNode(int _Val) {
        Value = _Val;
        LeftChild = nullptr;
        RightChild = nullptr;
    }
};

/// <summary>
/// Class for building and transforming prefix expression trees.
/// </summary>
class CCalcTree {
public:
    /// <summary>
    /// Constructor.
    /// </summary>
    CCalcTree();

    /// <summary>
    /// Destructor releasing tree memory.
    /// </summary>
    ~CCalcTree();

    /// <summary>
    /// Builds expression tree from prefix expression file.
    /// </summary>
    /// <param name="_FilePath">Path to text file with prefix expression.</param>
    /// <returns>Boolean indicating successful tree creation.</returns>
    bool BuildFromPrefixFile(const std::string& _FilePath);

    /// <summary>
    /// Transforms tree replacing subtrees containing exponentiation with calculated values.
    /// </summary>
    void EliminateExponentiation();

    /// <summary>
    /// Gets pointer to root node of tree.
    /// </summary>
    /// <returns>Pointer to root STreeNode.</returns>
    STreeNode* GetRoot() const;

private:
    STreeNode* RootNode;

    /// <summary>
    /// Recursive helper to parse prefix stream into tree.
    /// </summary>
    /// <param name="_Stream">File input stream reference.</param>
    /// <returns>Constructed subtree root pointer.</returns>
    STreeNode* _ParsePrefixStream(std::istream& _Stream);

    /// <summary>
    /// Recursively checks if subtree contains exponentiation operator (-6).
    /// </summary>
    /// <param name="_Node">Subtree root node.</param>
    /// <returns>True if exponentiation operator exists in subtree.</returns>
    bool _HasExponentiation(STreeNode* _Node) const;

    /// <summary>
    /// Evaluates full numerical result of a subtree.
    /// </summary>
    /// <param name="_Node">Subtree root node.</param>
    /// <returns>Evaluated integer result.</returns>
    int _EvaluateSubtree(STreeNode* _Node) const;

    /// <summary>
    /// Recursively transforms subtrees containing exponentiation.
    /// </summary>
    /// <param name="_Node">Subtree root pointer reference.</param>
    void _TransformAndEvaluate(STreeNode*& _Node);

    /// <summary>
    /// Helper to free memory associated with subtree.
    /// </summary>
    /// <param name="_Node">Node to release.</param>
    void _ClearTree(STreeNode* _Node);

    /// <summary>
    /// Evaluates power function for integers.
    /// </summary>
    /// <param name="_Base">Base integer.</param>
    /// <param name="_Exponent">Exponent power.</param>
    /// <returns>Integer power result.</returns>
    int _Power(int _Base, int _Exponent) const;
};
