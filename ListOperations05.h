// Copyright (c) 2026. Shvalev Dmitrij

#pragma once

#ifndef LISTOPERATIONS05_H
#define LISTOPERATIONS05_H

#include <list>

using namespace std;

// Fill the list with _Count elements
void FillList(list<int>& _List, int _Count);

// Print the content of the list
void PrintList(const list<int>& _List);

// Move the middle element of the source list to the end of the destination list
void MoveMiddleElement(list<int>& _SourceList, list<int>& _DestinationList);

#endif
