// Copyright (c) 2026. Shvalev Dmitrij

#pragma once

#include <string>

// Number that finishes the input
inline constexpr int ExitValue = -1;

// Read a number from the keyboard with validation
int ReadNumber();

// Print the content of a file
void PrintFileContent(const std::string& _FileName);
