#ifndef _HEAP_H
#define _HEAP_H

#include "hash.h"
#include <string>
#include <vector>

class heap {
public:
  // Constructor initializes the heap with the specified capacity.
  // Allocates space for the nodes and the hash table based on capacity.
  heap(int capacity);

  // Insert a node with the specified id, key, and optionally a pointer.
  // The key is used to determine the final position of the new node.
  // Returns:
  //   0 on success,
  //   1 if the heap is already filled to capacity,
  //   2 if a node with the given id already exists.
  int insert(const std::string &id, int key, void *pv = nullptr);

  // Set the key of the node identified by the specified id.
  // Returns:
  //   0 on success,
  //   1 if a node with the given id does not exist.
  int setKey(const std::string &id, int key);

  // Remove the node with the smallest key from the heap.
  // If pId is supplied, write the id of the node being deleted to that address.
  // If pKey is supplied, write the key of the node being deleted to that
  // address. If ppData is supplied, write the associated pointer to that
  // address. Returns:
  //   0 on success,
  //   1 if the heap is empty.
  int deleteMin(std::string *pId = nullptr, int *pKey = nullptr,
                void *ppData = nullptr);

  // Remove the node with the specified id from the heap.
  // If pKey is supplied, write the key of the node being deleted to that
  // address. If ppData is supplied, write the associated pointer to that
  // address. Returns:
  //   0 on success,
  //   1 if a node with the given id does not exist.
  int remove(const std::string &id, int *pKey = nullptr,
             void *ppData = nullptr);

private:
  // Nested node class representing elements in the heap.
  class node {
  public:
    std::string id{""};   // The id of this node.
    int key{0};           // The key of this node.
    void *pData{nullptr}; // A pointer to the actual data (optional).
  };

  // Vector storing the binary heap as a list of nodes.
  std::vector<node> data;

  // Hash table for mapping ids to nodes for quick lookup.
  hashTable *mapping;

  // Maximum capacity of the heap.
  int capacity;

  // Current size of the heap.
  int size; 

  // Helper function to move a node up the heap.
  void percolateUp(int posCur);

  // Helper function to move a node down the heap.
  void percolateDown(int posCur);

  // Get the position of a node in the heap based on its pointer.
  int getPos(node *pn);
};

#endif
