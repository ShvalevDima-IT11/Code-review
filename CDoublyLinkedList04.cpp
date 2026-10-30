// Copyright (c) 2026. AShvalev Dmitrij

#include <fstream>
#include <iostream>

#include "CDoublyLinkedList04.h"
#include "SNode04.h"

using namespace std;

// Create an empty list
CDoublyLinkedList::CDoublyLinkedList() : Head(nullptr) {
}

// Free all remaining nodes when the list goes out of scope
CDoublyLinkedList::~CDoublyLinkedList() {
    Clear();
}

// Reset the head pointer so the list becomes empty
void CDoublyLinkedList::Initialize() {
    Head = nullptr;
}

// Append a new node with the given value to the tail of the list
void CDoublyLinkedList::AddElement(int _Value) {
    SNode* NewNode = new SNode;
    NewNode->Data = _Value;
    NewNode->Previous = nullptr;
    NewNode->Next = nullptr;

    // The first node becomes the head
    if (Head == nullptr) {
        Head = NewNode;
        return;
    }

    // Traverse to the last node and link the new node after it
    SNode* Current = Head;
    while (Current->Next != nullptr) {
        Current = Current->Next;
    }
    Current->Next = NewNode;
    NewNode->Previous = Current;
}

// Detach the node from the list and free the memory it occupies
void CDoublyLinkedList::RemoveElement(SNode* _NodeToRemove) {
    if (_NodeToRemove == nullptr) {
        return;
    }

    SNode* PreviousNode = _NodeToRemove->Previous;
    SNode* NextNode = _NodeToRemove->Next;

    // Relink the previous node, or update the head if the node is the first one
    if (PreviousNode != nullptr) {
        PreviousNode->Next = NextNode;
    }
    else {
        Head = NextNode;
    }

    // Relink the next node if it exists
    if (NextNode != nullptr) {
        NextNode->Previous = PreviousNode;
    }

    delete _NodeToRemove;
}

// Print all values of the list from head to tail
void CDoublyLinkedList::Print() const {
    const SNode* Current = Head;
    cout << "Список: ";
    while (Current != nullptr) {
        cout << Current->Data << Separator;
        Current = Current->Next;
    }
    cout << endl;
}

// Write the list values to a file in reverse order and delete the nodes one by one
void CDoublyLinkedList::WriteToFileAndClear(const string& _FileName) {
    ofstream OutputFile(_FileName);
    if (!OutputFile.is_open()) {
        cout << "Ошибка открытия файла!" << endl;
        return;
    }

    // Find the last node to start writing from the tail
    SNode* Current = Head;
    while (Current != nullptr && Current->Next != nullptr) {
        Current = Current->Next;
    }

    // Write values from tail to head; delete each node as it is written
    bool bIsFirstElement = true;
    while (Current != nullptr) {
        if (bIsFirstElement) {
            OutputFile << Current->Data;
            bIsFirstElement = false;
        }
        else {
            OutputFile << Separator << Current->Data;
        }

        SNode* PreviousNode = Current->Previous;
        RemoveElement(Current);
        Current = PreviousNode;
    }

    OutputFile.close();
    cout << "Данные записаны в файл и список очищен." << endl;
}

// Delete every node of the list and reset the head pointer
void CDoublyLinkedList::Clear() {
    SNode* Current = Head;
    while (Current != nullptr) {
        SNode* NextNode = Current->Next;
        delete Current;
        Current = NextNode;
    }
    Head = nullptr;
}
