# Code Review and Architecture Analysis
**Assignment:** Laboratory Work #3 (Option 5)  
**Target Standard:** C++ Coding Standard (PascalCase, C/T/I/S/E/b/_ Prefixes, Upper-CamelCase, Doxygen XML Docs)

---

## 1. Executive Summary & Architecture Overview

Option 5 requires solving three specific algorithmic problems:
1. **Task 1 (Problem 2):** String permutation shuffle until original match with iteration counter.
2. **Task 2 (CalcTree6):** Prefix arithmetic expression tree construction (operators `-1` to `-6`), elimination/evaluation of exponentiation subtrees (`^`, operator `-6`), and root pointer output.
3. **Task 3 (Graf5):** Graph reachability analysis using Breadth-First Search (BFS) to identify all target cities reachable from city $K$ with strictly *fewer than* $L$ layovers (transfers).

All code components strictly conform to the provided **C++ Coding Standard**:
- Filename convention: PascalCase (`Main.cpp`, `CPasswordGenerator.h`, etc.).
- Entity Prefixes: `C` for Classes, `S` for Structs, `E` for Enums, `b` for Booleans, `_` for Private fields/parameters.
- Standard compliant formatting: Same-line opening braces `{`, no inline single-line function definitions, no `auto` (explicit typing throughout), `nullptr` instead of `NULL`, `const&` correctness, no magic constants, standard C++ casts (`static_cast`).
- Full XML Doxygen comment blocks (`/// <summary>`, `<param>`, `<returns>`) included for all declarations.

---

## 2. Individual Task Code Reviews

### Task 1: String Permutation Shuffle (Problem 2)

#### Code Design Analysis
- **Goal:** Read a word from console input, randomly shuffle its characters repeatedly using modern pseudo-random generation (`std::mt19937`), print each attempt, count total attempts until the generated word matches the original word.
- **Key Method:** `std::shuffle` powered by `std::random_device` and `std::mt19937` ensures unbiased random permutations without C-style `rand()` vulnerabilities.

#### Code Review Checklist
- [x] **PascalCase & Prefixes:** Class `CStringShuffler` (prefix `C`), boolean state `bIsMatching` (prefix `b`), private method `_PrintAttempt` (prefix `_`).
- [x] **Const-Correctness:** Parameters passed by `const std::string&`.
- [x] **Memory Management:** Stack allocation for string objects; standard library containers used safely.
- [x] **XML Documentation:** Complete XML tags applied to class methods.

---

### Task 2: Expression Tree Transformation (CalcTree6)

#### Code Design Analysis
- **Goal:** Read a prefix expression from `filename.txt`, build a binary expression tree (operators encoded as: `+` = `-1`, `-` = `-2`, `*` = `-3`, `/` = `-4`, `%` = `-5`, `^` = `-6`), transform the tree by eliminating all subtrees containing exponentiation (`^` / `-6`) and replacing them with their evaluated integer result, and return the pointer to the root.
- **Prefix Parsing Logic:** A recursive pre-order parsing algorithm processes tokens left-to-right.
- **Transformation Logic:** A post-order traversal (`_TransformAndEvaluate`) checks if a subtree contains the target operator (`-6`). If found, it computes the numeric value of the subtree, frees the old children memory to prevent memory leaks, converts the node into a terminal leaf storing the computed result, and returns.

#### Code Review Checklist
- [x] **Memory & Safety:** RAII and explicit recursive dynamic memory cleanup (`_ClearTree`).
- [x] **Code Style:** Operator codes defined via `enum class EOperatorType` (prefix `E`). All member fields private with `_` prefix.
- [x] **Error Handling:** Protects against division/modulo by zero and integer overflow in exponentiation.

---

### Task 3: Aviation Network Analysis (Graf5)

#### Code Design Analysis
- **Goal:** Given an $n \times n$ adjacency matrix ($n \le 25$), determine all cities reachable from city $K$ with *fewer than* $L$ layovers (i.e., path length in terms of edges $\le L$).
- **Algorithm Choice:** Breadth-First Search (BFS) shortest path search on an unweighted graph. Edge count corresponds to flight hops; $L - 1$ layovers corresponds to $L$ flights.
- **Output Requirements:** Cities listed in 1-based indexing, sorted in ascending order. Outputs `-1` if no such cities exist.

#### Code Review Checklist
- [x] **Algorithm Correctness:** BFS guarantees shortest flight distance calculation.
- [x] **Data Structures:** `std::queue<int>` and `std::vector<int>` for state representation.
- [x] **Code Style Compliance:** Encapsulated in `CAviationGraph` class, methods and variables use specified PascalCase and prefix patterns.

---
