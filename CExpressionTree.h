#pragma once

#include <cstddef>
#include <memory>
#include <string>

struct SNode;

/// <summary>
/// Binary tree of an arithmetic expression given in prefix (Polish) notation.
/// Operands are single digits 0..9, operations are + - * / % ^.
/// </summary>
class CExpressionTree {
public:
    /// <summary>Creates an empty tree.</summary>
    CExpressionTree();

    /// <summary>Destroys the tree together with all of its nodes.</summary>
    ~CExpressionTree();

    CExpressionTree(const CExpressionTree&) = delete;
    CExpressionTree& operator=(const CExpressionTree&) = delete;

    /// <summary>
    /// Reads a prefix expression from a text file and builds the tree.
    /// </summary>
    /// <param name="_FileName">Path to the text file with the expression.</param>
    /// <exception cref="std::runtime_error">The file cannot be opened.</exception>
    /// <exception cref="std::invalid_argument">The file does not contain a valid expression.</exception>
    void LoadFromFile(const std::string& _FileName);

    /// <summary>
    /// Builds the tree from a prefix expression. White space between symbols is ignored.
    /// If the expression is invalid the current tree is left unchanged.
    /// </summary>
    /// <param name="_Expression">Expression such as "+ * 2 3 4" or "+*234".</param>
    /// <exception cref="std::invalid_argument">
    /// The expression is empty, incomplete, has an unknown symbol or has extra symbols at the end.
    /// </exception>
    void BuildFromPrefix(const std::string& _Expression);

    /// <summary>
    /// Replaces every subtree whose root is the power operation (^) with a leaf
    /// that holds the value of that subtree. Afterwards the tree has no ^ operations.
    /// </summary>
    /// <exception cref="std::domain_error">Division by zero, zero to a negative power, etc.</exception>
    /// <exception cref="std::overflow_error">An intermediate result does not fit into int.</exception>
    void RemovePowerOperations();

    /// <summary>Checks whether the tree has no nodes.</summary>
    /// <returns>True if the tree is empty; otherwise false.</returns>
    bool IsEmpty() const;

    /// <summary>Gets the root of the tree.</summary>
    /// <returns>Pointer to the root node, or nullptr if the tree is empty. The tree keeps the ownership.</returns>
    const SNode* GetRoot() const;

    /// <summary>
    /// Formats the tree in prefix form for diagnostics. Tokens are separated by spaces,
    /// operations are printed as symbols, leaves as decimal numbers.
    /// </summary>
    /// <returns>Prefix form of the tree; an empty string for an empty tree.</returns>
    std::string ToPre


        fixString() const;

private:
    /// <summary>
    /// Recursively parses one operand (a digit or an operation with two operands).
    /// </summary>
    /// <param name="_Expression">Whole expression.</param>
    /// <param name="_Position">Index of the next unread symbol; advanced while parsing.</param>
    /// <returns>Root of the parsed subtree.</returns>
    /// <exception cref="std::invalid_argument">The expression is incomplete or has an unknown symbol.</exception>
    std::unique_ptr<SNode> _ParseNode(const std::string& _Expression, std::size_t& _Position) const;

    /// <summary>
    /// Recursively replaces the topmost power subtrees with their values.
    /// </summary>
    /// <param name="_Node">Owning pointer to the subtree root; may be replaced by a leaf.</param>
    void _CollapsePowers(std::unique_ptr<SNode>& _Node) const;

    /// <summary>Root of the tree; nullptr for an empty tree.</summary>
    std::unique_ptr<SNode> Root;
};
