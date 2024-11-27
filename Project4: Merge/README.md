# Project 4: Valid String Merge Checker

This project involves implementing a C++ program that checks whether a given string `C` is a valid merge of two other strings `A` and `B`, while preserving the original character order of each. The program reads multiple sets of strings from an input file and determines if `C` can be formed by interleaving `A` and `B`. If `C` is a valid merge, the program outputs `C` with all characters from `A` converted to uppercase, ensuring that characters from `A` appear as early as possible in `C`.

Key features of this project include:

- **Recursive Depth-First Search with Memoization**: Utilizes a top-down dynamic programming approach by implementing a recursive depth-first search with memoization. This efficiently solves the problem by avoiding redundant computations and handling large inputs effectively.

- **Priority Character Placement**: When multiple valid merges are possible, the program prioritizes characters from `A`, placing them as early (far left) as possible in the merged string. This is achieved by first attempting to match characters from `A` during the recursive search.

- **Global Data Structures**: Utilizes global arrays for memoization and path tracking to prevent stack overflow and eliminate the need for dynamic memory allocation.


