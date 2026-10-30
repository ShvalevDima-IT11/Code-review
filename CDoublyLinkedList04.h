// Copyright (c) 2026. Shvalev Dmitrij

#pragma once

// Node of a doubly linked list (data transfer object)
struct SNode {
    int Data;        // Node value
    SNode* Previous; // Pointer to the previous node
    SNode* Next;     // Pointer to the next node
};
