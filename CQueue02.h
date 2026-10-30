// Copyright (c) 2026. Shvalev Dmitrij

#pragma once

#ifndef CQUEUE02_H
#define CQUEUE02_H

struct SNode;

// Queue of integers built as a singly linked list.
// A pointer to the tail is stored to allow fast insertion at the end.
class CQueue {
public:
    CQueue();
    ~CQueue();

    void Add(int _Value);                // Add a value to the tail of the queue
    void ShowInitial() const;            // Print the initial state before extraction
    void ExtractElements(int _Count);    // Extract _Count elements from the head
    void ShowAfterExtraction() const;    // Print the state after extraction

private:
    SNode* Head; // Pointer to the first node
    SNode* Tail; // Pointer to the last node
};

#endif
