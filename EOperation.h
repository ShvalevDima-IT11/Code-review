#pragma once

/// <summary>
/// Arithmetic operations of the expression tree.
/// The numeric values are the codes required by the task and are stored in inner nodes.
/// </summary>
enum class EOperation : int {
    Addition = -1,
    Subtraction = -2,
    Multiplication = -3,
    Division = -4,
    Remainder = -5,
    Power = -6
};
