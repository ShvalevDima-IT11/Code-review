// Copyright(c) 2026. Shvalev Dmitrij

#pragma once

#ifndef EINPUTMETHOD05_H
#define EINPUTMETHOD05_H

// Method of filling a container
enum class EInputMethod {
    Keyboard = 1, // Enter values manually
    Random = 2,   // Generate values with a pseudo-random generator
    File = 3      // Read values from a text file
};

#endif
