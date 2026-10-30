// Copyright (c) 2026. Shvalev Dmitrij

#include <iostream>

#include "CQueue02.h"
#include "SNode02.h"

using namespace std;

namespace {
    const char* const Separator = " ";              // Separator between printed values
    const char* const NullPointerText = "nullptr";  // Text used for null pointers

    const char* const InitialHeadAddressLabel = "Исходный адрес первого элемента: ";
    const char* const InitialQueueLabel = "Исходная очередь: ";
    const char* const InitialTailAddressLabel = "Исходный адрес последнего элемента: ";
    const char* const EmptyAfterExtractMessage =
        "Очередь после удаления элементов оказалась пустой";
    const char* const NewHeadAddressLabel = "Новое начало очереди: ";
    const char* const RemainingQueueLabel = "Оставшиеся элементы очереди: ";
    const char* const NewTailAddressLabel = "Новый конец очереди: ";
    const char* const QueueHeadAddressLabel = "Начало очереди: ";
    const char* const QueueTailAddressLabel = "Конец очереди: ";
}

// An empty queue has no head and no tail
CQueue::CQueue() : Head(nullptr), Tail(nullptr) {
}

// Free all remaining nodes when the queue goes out of scope
CQueue::~CQueue() {
    while (Head != nullptr) {
        SNode* Temp = Head;
        Head = Head->Next;
        delete Temp;
    }
    Tail = nullptr;
}

// Append a new node to the tail of the queue
void CQueue::Add(int _Value) {
    SNode* NewNode = new SNode(_Value);
    if (Head == nullptr) {
        Head = NewNode;
        Tail = NewNode;
    }
    else {
        Tail->Next = NewNode;
        Tail = NewNode;
    }
}

// Print the initial addresses of the head and the tail and the whole content
void CQueue::ShowInitial() const {
    cout << InitialHeadAddressLabel << Head << Separator << Head->Data << endl;

    cout << InitialQueueLabel;
    const SNode* Current = Head;
    while (Current != nullptr) {
        cout << Current->Data << Separator;
        Current = Current->Next;
    }
    cout << endl;

    cout << InitialTailAddressLabel << Tail << Separator << Tail->Data << endl;
}

// Extract up to _Count leading elements and free the memory they occupied
void CQueue::ExtractElements(int _Count) {
    for (int Index = 0; Index < _Count && Head != nullptr; Index++) {
        SNode* Temp = Head;
        // Print the value and the address of the next node before deleting
        cout << Temp->Data << Separator << Temp->Next << Separator;
        Head = Head->Next;
        delete Temp;
        if (Head == nullptr) {
            Tail = nullptr;
        }
        cout << endl;
    }
    cout << endl;
}

// Print the new addresses of the head and the tail and the remaining content
void CQueue::ShowAfterExtraction() const {
    if (Head == nullptr) {
        // The queue became empty: print nullptr twice as required by the task
        cout << EmptyAfterExtractMessage << endl;
        cout << QueueHeadAddressLabel << NullPointerText << endl;
        cout << QueueTailAddressLabel << NullPointerText << endl;
        return;
    }

    cout << NewHeadAddressLabel << Head << Separator << Head->Data << endl;

    cout << RemainingQueueLabel;
    const SNode* Current = Head;
    while (Current != nullptr) {
        cout << Current->Data << Separator;
        Current = Current->Next;
    }
    cout << endl;

    cout << NewTailAddressLabel << Tail << Separator << Tail->Data << endl;
}
