# Project 3: Dijkstra's Algorithm Implementation

This project focuses on implementing Dijkstra's algorithm in C++ to solve the single-source shortest-path problem on a graph. The program reads a graph from an input file where each line represents a directed edge with a source vertex, destination vertex, and cost. It then prompts the user to specify a starting vertex and computes the shortest paths to all other vertices in the graph using Dijkstra's algorithm.

Key features of this project include:

- **Custom Data Structures**: Utilizes a binary heap and a hash table, both custom-implemented, to manage priority queues and efficient vertex lookups, ensuring optimal performance of the algorithm.
  
- **Graph Representation**: Implements a graph class that stores vertices and edges, using adjacency lists for efficient traversal. The graph is constructed dynamically by reading from the input file.
  
- **User Interaction**: Provides a command-line interface that prompts the user for the graph file name, starting vertex, and output file name, enhancing usability and flexibility.
  
- **Performance Measurement**: Outputs the CPU time taken to apply Dijkstra's algorithm, offering insights into the efficiency of the implementation.
  
- **Output Formatting**: Writes the shortest paths and distances to an output file in a specified format, listing vertices in the order they first appear in the input file and indicating unreachable vertices with "NO PATH".
