/*
  Name: Taha Akhlaq
  Description:
   * This file checks if a string C is a valid merge of two strings A and B,
   * maintaining their character order. It uses recursive depth-first search
   * with memoization (dynamic programming) to validate merges and constructs
   * the output with A's characters capitalized.
*/

#include <cctype>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define MAX_LEN 1001 // Maximum size for A and B

// Global memoization table and path matrix
int memo[MAX_LEN][MAX_LEN];  // -1: unvisited, 0: invalid merge, 1: valid merge
char path[MAX_LEN][MAX_LEN]; // Stores the choice made at each position

string A_global, B_global, C_global;

// Recursive function with memoization
bool dfs(int i, int j, int k) {
  // Check if this subproblem has already been solved
  if (memo[i][j] != -1)
    return memo[i][j];

  // Base case: if reached the end of C_global
  if (k == C_global.length()) {
    // If also consumed all of A_global and B_global, it's a valid merge
    if (i == A_global.length() && j == B_global.length()) {
      return memo[i][j] = 1;
    } else {
      return memo[i][j] = 0;
    }
  }

  // Matching character from A_global to ensure A's characters occur early
  bool res = false;
  if (i < A_global.length() && A_global[i] == C_global[k]) {
    if (dfs(i + 1, j, k + 1)) {
      res = true;
      path[i][j] = 'A';
    }
  }

  // Matching with A_global was not valid, try matching with B_global
  if (!res && j < B_global.length() && B_global[j] == C_global[k]) {
    if (dfs(i, j + 1, k + 1)) {
      res = true;
      path[i][j] = 'B';
    }
  }

  // Store the result in memoization table and return
  memo[i][j] = res ? 1 : 0;
  return res;
}

// Function to construct the merged string with A's characters capitalized
string constructMerge() {
  string result = C_global;
  int i = 0, j = 0, k = 0;

  // Reconstruct the path taken during dfs to build the final result
  while (k < C_global.length()) {
    if (path[i][j] == 'A') {
      result[k] = toupper(result[k]);
      i++;
    } else if (path[i][j] == 'B') {
      j++;
    } else {
      // Should not happen if dfs returned true
      break;
    }
    k++;
  }

  return result;
}

// Function to process the input and output files
void processFiles(const string &inputFile, const string &outputFile) {
  ifstream input(inputFile);
  ofstream output(outputFile);

  if (!input.is_open()) {
    cerr << "Error: Could not open input file: " << inputFile << endl;
    exit(1);
  }
  if (!output.is_open()) {
    cerr << "Error: Could not open output file: " << outputFile << endl;
    exit(1);
  }

  string A, B, C;
  while (getline(input, A) && getline(input, B) && getline(input, C)) {
    A_global = A;
    B_global = B;
    C_global = C;

    if (A.length() + B.length() != C.length()) {
      output << "*** NOT A MERGE ***\n";
      continue;
    }

    // Initialize memoization table and path matrix
    memset(memo, -1, sizeof(memo));
    memset(path, 0, sizeof(path));

    // Perform DFS with memoization
    if (dfs(0, 0, 0)) {
      output << constructMerge() << "\n";
    } else {
      output << "*** NOT A MERGE ***\n";
    }
  }

  input.close();
  output.close();
}

int main() {
  string inputFile, outputFile;

  // Prompt user for input and output file names
  cout << "Enter name of input file: ";
  cin >> inputFile;
  cout << "Enter name of output file: ";
  cin >> outputFile;

  // Process the files
  processFiles(inputFile, outputFile);

  cout << "Processing complete. Check the output file." << endl;
  return 0;
}
