// Copyright (c) 2026. Shvalev Dmitrij

#include <iostream>

#include "CList03.h"
#include "SNode03.h"

using namespace std;

namespace {
    const char* const Separator = " "; // Separator between printed values
    const char* const AllNumbersLabel = "Все полученные числа: ";
    const char* const EmptyListMessage = "Пусто!";
}

// Create an empty list
CList::CList() : Head(nullptr) {
}

// Deep copy: allocate new nodes and append their values one by one
CList::CList(const CList& _Other) : Head(nullptr) {
    const SNode* Current = _Other.Head;
    while (Current != nullptr) {
        Add(Current->Data);
        Current = Current->Next;
    }
}

// Free all nodes when the list goes out of scope
CList::~CList() {
    Clear();
}

// Delete every node and reset the head pointer
void CList::Clear() {
    SNode* Current = Head;
    while (Current != nullptr) {
        SNode* NextNode = Current->Next;
        delete Current;
        Current = NextNode;
    }
    Head = nullptr;
}

// A list is empty when its head pointer is null
bool CList::IsEmpty() const {
    return Head == nullptr;
}

// Append a new node to the end of the list
void CList::Add(int _Value) {
    SNode* NewNode = new SNode(_Value);

    // The first node becomes the head
    if (Head == nullptr) {
        Head = NewNode;
        return;
    }

    // Traverse to the last node, since only the head pointer is stored
    SNode* Current = Head;
    while (Current->Next != nullptr) {
        Current = Current->Next;
    }
    Current->Next = NewNode;
}

// Return the node after which a new value should be inserted.
// Returns nullptr if the new value must become the new head.
SNode* CList::FindInsertPosition(int _Value) const {
    SNode* Current = Head;
    SNode* PreviousNode = nullptr;
    while (Current != nullptr && Current->Data < _Value) {
        PreviousNode = Current;
        Current = Current->Next;
    }
    return PreviousNode;
}

// Insert a value so that the ascending order is preserved
void CList::InsertSorted(int _Value) {
    SNode* NewNode = new SNode(_Value);

    // Insert at the head if the list is empty or the new value is the smallest
    if (Head == nullptr || Head->Data >= _Value) {
        NewNode->Next = Head;
        Head = NewNode;
        return;
    }

    // Otherwise insert after the found node
    SNode* InsertAfter = FindInsertPosition(_Value);
    NewNode->Next = InsertAfter->Next;
    InsertAfter->Next = NewNode;
}

// Return the first node whose value equals _Value, or nullptr if none
SNode* CList::FindByValue(int _Value) const {
    SNode* Current = Head;
    while (Current != nullptr && Current->Data != _Value) {
        Current = Current->Next;
    }
    return Current;
}

// Remove the first node with the given value, if it exists
void CList::DeleteByValue(int _Value) {
    SNode* NodeToDelete = FindByValue(_Value);
    if (NodeToDelete == nullptr) {
        return; // Nothing to delete
    }

    // Special case: the node to delete is the head
    if (NodeToDelete == Head) {
        Head = NodeToDelete->Next;
        delete NodeToDelete;
        return;
    }

    // Find the node that precedes the one to delete
    SNode* PreviousNode = Head;
    while (PreviousNode != nullptr && PreviousNode->Next != NodeToDelete) {
        PreviousNode = PreviousNode->Next;
    }

    // Relink the neighbours and free the memory
    if (PreviousNode != nullptr) {
        PreviousNode->Next = NodeToDelete->Next;
    }
    delete NodeToDelete;
}

// Print all elements; optionally show a message when the list is empty
void CList::Print(bool _bShowEmptyMessage) const {
    cout << AllNumbersLabel;

    if (Head == nullptr && _bShowEmptyMessage) {
        cout << EmptyListMessage;
    }

    const SNode* Current = Head;
    while (Current != nullptr) {
        cout << Current->Data << Separator;
        Current = Current->Next;
    }
    cout << endl;
}
