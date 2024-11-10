#ifndef GRAPH_H
#define GRAPH_H

#include "hash.h"
#include "heap.h"
#include <climits>
#include <fstream>
#include <iostream>
#include <list>
#include <string>

class hashTable;
class heap;

class graph {
public:
  // Constructor to initialize the graph from a file
  graph(const std::string &input_file);

  // Checks if a vertex exists in the graph
  bool contains(const std::string &vertex_name) const;

  // Executes Dijkstra's algorithm starting from start_vertex
  void dijkstra(const std::string &start_vertex);

  // Outputs the shortest paths and distances to a specified file
  void outputPaths(const std::string &output_file) const;

private:
  struct GraphNode; // Forward declaration of GraphNode

  // Edge structure representing a directed edge with a weight
  struct GraphEdge {
    int cost;        // Cost of the edge
    GraphNode *dest; // Pointer to destination vertex
    GraphEdge(GraphNode *d, int c) : cost(c), dest(d) {}
  };

  // Vertex structure representing a graph node and its properties
  struct GraphNode {
    std::string name;   // Unique identifier for the vertex
    bool known = false; // True if vertex is processed in Dijkstra’s algorithm
    int dist = INT_MAX; // Distance from the source vertex
    GraphNode *prev =
        nullptr; // Pointer to the previous vertex in the shortest path
    std::list<GraphEdge> adj; // Adjacency list of edges

    GraphNode(const std::string &vertexName) : name(vertexName) {}
  };

  hashTable *vertices; // Hash table to store and access vertices by their names
  std::list<GraphNode *>
      adj_list; // List to maintain the order of vertices as they are inserted

  // Loads graph from an input file
  void loadGraph(const std::string &input_file);

  // Helper function to print the path for a vertex to an output stream
  void printPath(GraphNode *v, std::ostream &out) const;
};

#endif
