#pragma once

#include <memory>

/// <summary>
/// Node of an expression tree.
/// </summary>
/// <remarks>
/// A node without children is a leaf and <see cref="Data"/> is its operand value.
/// A node with two children is an inner node and <see cref="Data"/> is the code of
/// an <see cref="EOperation"/> (a negative number). Whether a node is a leaf must always
/// be decided by its children, not by the sign of <see cref="Data"/>, because a leaf that was
/// produced by evaluating a subtree may hold any int value, including a negative one.
/// </remarks>
struct SNode {
    /// <summary>Operand value (leaf) or operation code (inner node).</summary>
    int Data = 0;

    /// <summary>Left operand; nullptr for a leaf.</summary>
    std::unique_ptr<SNode> Left;

    /// <summary>Right operand; nullptr for a leaf.</summary>
    std::unique_ptr<SNode> Right;
};
