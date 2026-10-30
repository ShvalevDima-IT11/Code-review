// Copyright (c) 2026. Shvalev Dmitrij

#pragma once

#ifndef SNODE03_H
#define SNODE03_H

// Singly linked list node (data transfer object)
struct SNode {
    int Data;    // Node value
    SNode* Next; // Pointer to the next node

    SNode(int _Data);
};

#endif
