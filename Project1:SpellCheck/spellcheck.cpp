/*
  Name: Taha Akhlaq
  Description:
   * This program implements a spell checker that utilizes a hash table
   * to efficiently store a dictionary and identify unrecognized or invalid
   * words in a given document. The program processes the input files,
   * checks for errors, and outputs the results.
*/

#include "hash.h"
#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// Function to load the dictionary into the hash table
void loadDictionary(const string &dictionaryName, hashTable &Hash) {
  ifstream dictFile(dictionaryName); // Open the dictionary file
  if (!dictFile.is_open()) {
    cerr << "Error: Could not open dictionary file." << endl;
    exit(EXIT_FAILURE);
  }

  string word;
  while (getline(dictFile, word)) {
    // Convert each word to lowercase
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    Hash.insert(word);
  }
  dictFile.close();
}

// Function to check the input file and spell-check it
void spellCheck(const string &inputFile, const string &outputFile, hashTable &Hash) {
  ifstream inFile(inputFile);
  if (!inFile.is_open()) {
    cerr << "Error: Could not open input file." << endl;
    exit(EXIT_FAILURE);
  }

  // Open the output file for writing
  ofstream outFile(outputFile);
  if (!outFile.is_open()) {
    cerr << "Error: Could not open output file." << endl;
    exit(EXIT_FAILURE);
  }

  string line, word;  // Store the current line and word being processed
  int lineNum = 0;    // Track the line number for error reporting
  bool containsDigit; // Check if a word contains a digit

  // Read the input file
  while (getline(inFile, line)) {
    lineNum++;
    word.clear();
    containsDigit = false;

    // Convert line to lowercase
    transform(line.begin(), line.end(), line.begin(), ::tolower);

    // Process each character in the line
    for (int i = 0; i <= line.size(); ++i) {
      char ch = line[i];

      // Check if the character is part of a valid word 
      if (isalnum(ch) || ch == '-' || ch == '\'') {
        word += ch; // Add the character to the current word
        if (isdigit(ch))
          containsDigit = true; // Set flag if the word contains a digit
      }
      // If a non-word character is encountered or end of line
      else if (!word.empty()) {
        // Check if the word exceeds the length limit (20 characters)
        if (word.size() > 20) {
          outFile << "Long word at line " << lineNum << ", starts: " << word.substr(0, 20) << endl;
        }
        // Check if the word is in the dictionary (ignoring words with digits)
        else if (!containsDigit && !Hash.contains(word)) {
          outFile << "Unknown word at line " << lineNum << ": " << word << endl;
        }
        // Reset the word buffer and digit flag for the next word
        word.clear();
        containsDigit = false;
      }
    }
  }

  // Close the input and output files
  inFile.close();
  outFile.close();
}

int main() {
  string dictFile, inputFile, outputFile;

  // Prompt user for the dictionary, input, and output file names
  cout << "Enter name of dictionary: ";
  cin >> dictFile;

  cout << "Enter name of input file: ";
  cin >> inputFile;

  cout << "Enter name of output file: ";
  cin >> outputFile;

  // Initialize the hash table with an estimated size of 50,000 words
  hashTable dictionaryHash(50000);

  // Measure time for loading the dictionary
  clock_t t1 = clock();
  loadDictionary(dictFile,
                 dictionaryHash); // Load the dictionary into the hash table
  clock_t t2 = clock();
  double loadTime = static_cast<double>(t2 - t1) / CLOCKS_PER_SEC;
  cout << "Total time (in seconds) to load dictionary: " << loadTime << endl;

  // Measure time for spell-checking
  t1 = clock();
  spellCheck(inputFile, outputFile,
             dictionaryHash); // Spellcheck the input file
  t2 = clock();
  double checkTime = static_cast<double>(t2 - t1) / CLOCKS_PER_SEC;
  cout << "Total time (in seconds) to check document: " << checkTime << endl;

  return 0;
}
