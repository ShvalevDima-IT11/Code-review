// Copyright (c) 2026. Shvalev Dmitrij
#pragma once

#ifndef CSTACK01_H
#define CSTACK01_H

struct SNode;

// Stack of integers built as a singly linked list
class CStack {
public:
    CStack();

    void Push(int _Value);      // Add a value on top of the stack
    void Show() const;          // Print all elements from top to bottom
    void ShowAddress() const;   // Print the address of the top node
    int GetTopValue() const;    // Return the value of the top node
    bool IsEmpty() const;       // Check whether the stack is empty

private:
    SNode* Top; // Pointer to the top of the stack
};

#endif
