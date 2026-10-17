// Copyright (c) 2026. Shvalev Dmitrij

#include <iostream>

#include "CStack01.h"
#include "SNode01.h"

using namespace std;

namespace {
    const char* const Separator = " ";              // Separator between printed values
    const char* const TopAddressLabel = "Адрес вершины стека: ";
    const int EmptyStackValue = 1;                  // Value returned when the stack is empty
}

// An empty stack has no top node
CStack::CStack() : Top(nullptr) {
}

// Create a new node and make it the new top of the stack
void CStack::Push(int _Value) {
    SNode* NewNode = new SNode(_Value);
    NewNode->Next = Top;
    Top = NewNode;
}

// Print all elements of the stack from top to bottom
void CStack::Show() const {
    const SNode* Current = Top;
    while (Current != nullptr) {
        cout << Current->Data << Separator;
        Current = Current->Next;
    }
    cout << endl;
}

// Print the address of the top node
void CStack::ShowAddress() const {
    cout << TopAddressLabel << Top << endl;
}

// Return the value of the top node, or a fallback value if the stack is empty
int CStack::GetTopValue() const {
    if (Top != nullptr) {
        return Top->Data;
    }
    return EmptyStackValue;
}

// A stack is empty when its top pointer is null
bool CStack::IsEmpty() const {
    return Top == nullptr;
}
