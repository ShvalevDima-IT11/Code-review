// Copyright (c) 2026. Shvalev Dmitrij

#pragma once

#ifndef CLIST03_H
#define CLIST03_H

struct SNode;

// Singly linked list of integers kept sorted in ascending order.
// Only a pointer to the head is stored, as required by the task.
class CList {
public:
    CList();
    CList(const CList& _Other); // Deep copy constructor
    ~CList();

    void Add(int _Value);                      // Append a value to the end of the list
    void InsertSorted(int _Value);             // Insert a value keeping ascending order
    void DeleteByValue(int _Value);            // Remove the first occurrence of a value
    void Print(bool _bShowEmptyMessage) const; // Print all elements
    bool IsEmpty() const;                      // Check whether the list has no elements

private:
    SNode* FindInsertPosition(int _Value) const; // Find the node after which to insert
    SNode* FindByValue(int _Value) const;        // Find the first node with a given value
    void Clear();                                // Delete all nodes and reset Head

    SNode* Head; // Pointer to the first node
};

#endif
