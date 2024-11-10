/*
  Name: Taha Akhlaq
  Description:
   * This program reads a graph from an input file, prompts the user for a
   * starting vertex, and calculates the shortest paths to all reachable nodes.
   * It displays the total execution time and writes the output paths to a
   * specified output file.
 */

#include "graph.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  string inputFile, outputFile, startVertex;
  clock_t start, end;

  // Prompt for the graph file and load it
  cout << "Enter name of graph file: ";
  cin >> inputFile;

  graph g(inputFile); // The constructor now loads the graph from the file

  // Prompt for a valid starting vertex
  cout << "Enter name of starting vertex: ";
  cin >> startVertex;
  while (!g.contains(startVertex)) {
    cerr << "Invalid vertex. Please enter a valid starting vertex: ";
    cin >> startVertex;
  }

  // Execute Dijkstra's algorithm and measure execution time
  start = clock();
  g.dijkstra(startVertex);
  end = clock();
  double timeTaken = static_cast<double>(end - start) / CLOCKS_PER_SEC;
  cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << timeTaken
       << endl;

  // Prompt for the output file and write paths
  cout << "Enter name of output file: ";
  cin >> outputFile;
  g.outputPaths(outputFile);

  return 0;
}
