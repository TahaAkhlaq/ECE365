/*
  Name: Taha Akhlaq
  Description:
   * This file implements all member functions and data structures
   * as defined in graph.h. The Graph class leverages Dijkstra's
   * algorithm to find the shortest path between vertices, using
   * a hash table to store vertices and a min-heap for priority
   * management during path calculations.
*/

#include "graph.h"
#include "hash.h"
#include "heap.h"
#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>

// Constructor with input file
graph::graph(const std::string &input_file) {
  vertices = new hashTable(100000); // Initialize hash table
  loadGraph(input_file);            // Load graph from file
}

// Load graph from file
void graph::loadGraph(const std::string &input_file) {
  std::ifstream infile(input_file);
  if (!infile) {
    std::cerr << "Error: Cannot open graph file " << input_file << std::endl;
    exit(1);
  }

  std::string vertex1, vertex2;
  int cost;

  // Process each line of the file
  while (infile >> vertex1 >> vertex2 >> cost) {
    // Insert vertices if they don't exist
    if (!vertices->contains(vertex1)) {
      GraphNode *newVertex1 = new GraphNode(vertex1);
      vertices->insert(vertex1, newVertex1);
      adj_list.push_back(newVertex1);
    }
    if (!vertices->contains(vertex2)) {
      GraphNode *newVertex2 = new GraphNode(vertex2);
      vertices->insert(vertex2, newVertex2);
      adj_list.push_back(newVertex2);
    }

    // Add edge from vertex1 to vertex2 with given cost
    GraphNode *src = static_cast<GraphNode *>(vertices->getPointer(vertex1));
    GraphNode *dest = static_cast<GraphNode *>(vertices->getPointer(vertex2));
    src->adj.push_back(GraphEdge(dest, cost));
  }
}

// Check if vertex exists in graph
bool graph::contains(const std::string &vertex_name) const {
  return vertices->contains(vertex_name);
}

// Dijkstra's algorithm for shortest path calculation
void graph::dijkstra(const std::string &start_vertex) {
  if (!contains(start_vertex)) {
    std::cerr << "Error: Starting vertex not found in graph.\n";
    return;
  }

  heap minHeap(adj_list.size());
  GraphNode *start =
      static_cast<GraphNode *>(vertices->getPointer(start_vertex));
  start->dist = 0;
  minHeap.insert(start_vertex, start->dist, start);

  // For all other vertices, insert with infinite distance
  for (GraphNode *v : adj_list) {
    if (v != start) {
      minHeap.insert(v->name, v->dist, v);
    }
  }

  std::string vertex_id;
  int dist;
  GraphNode *min_vertex;

  while (!minHeap.deleteMin(&vertex_id, &dist, &min_vertex)) {
    if (min_vertex->known)
      continue; // Skip if already processed

    // If the smallest distance is INT_MAX, remaining vertices are unreachable
    if (dist == INT_MAX)
      break;

    min_vertex->known = true;

    for (const GraphEdge &e : min_vertex->adj) {
      if (!e.dest->known && min_vertex->dist != INT_MAX) {
        int newDist = min_vertex->dist + e.cost;
        if (newDist < e.dest->dist) {
          e.dest->dist = newDist;
          e.dest->prev = min_vertex;
          minHeap.setKey(e.dest->name, e.dest->dist);
        }
      }
    }
  }
}

// Output paths to output file
void graph::outputPaths(const std::string &output_file) const {
  std::ofstream out(output_file);
  if (!out) {
    std::cerr << "Error: Cannot open output file " << output_file << std::endl;
    exit(1);
  }

  for (GraphNode *v : adj_list) {
    out << v->name << ": ";
    if (v->dist == INT_MAX) {
      out << "NO PATH\n";
    } else {
      out << v->dist << " [";
      printPath(v, out);
      out << "]\n";
    }
  }
}

// Print path for a vertex
void graph::printPath(GraphNode *v, std::ostream &out) const {
  if (v->prev) {
    printPath(v->prev, out);
    out << ", ";
  }
  out << v->name;
}
