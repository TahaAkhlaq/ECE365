/*
  Name: Taha Akhlaq
  Description:
   * This program implements a binary heap to store elements with unique IDs and associated keys.
   * The heap maintains the minimum element at the root for efficient access.
   * Elements can be inserted, their keys updated, and the minimum can be removed.
   * The heap structure is enforced through percolation (up/down) operations.
   * A hash table maps IDs to nodes for quick access during operations like updates and deletions.
*/

#include "heap.h"

#include <climits>
#include <iostream>

using namespace std;

// Constructor to initialize heap and hash table
heap::heap(int capacity) {
  this->capacity = capacity;       // Set heap capacity
  this->size = 0;                  // Start with an empty heap
  data.resize(this->capacity + 1); // Allocate space for heap (1-based indexing)
  mapping = new hashTable(
      2 * capacity); // Create a hash table with twice the capacity
}

// Insert a new node into the heap
int heap::insert(const std::string &id, int key, void *pv) {
  // If heap is full, return 1
  if (size >= capacity)
    return 1;

  // If the id already exists, return 2
  if (mapping->contains(id))
    return 2;

  // Insert new node at the end of the heap
  size++;
  data[size].id = id;
  data[size].key = key;
  data[size].pData = pv;

  // Insert node into the hash table
  if (mapping->insert(id, &data[size]) != 0) {
    cerr << "Error inserting into hash table." << endl;
    return 2;
  }

  // Percolate up to restore heap order
  percolateUp(size);
  return 0;
}

// Update the key of a node in the heap
int heap::setKey(const std::string &id, int key) {
  bool found;
  node *pn = static_cast<node *>(mapping->getPointer(id, &found));

  // If node is not found, return 1
  if (!found)
    return 1;

  // Update key and adjust the heap accordingly
  int currentPos = getPos(pn);
  int oldKey = pn->key;
  pn->key = key;

  // Percolate up or down based on key change
  if (key < oldKey) {
    percolateUp(currentPos);
  } else {
    percolateDown(currentPos);
  }

  return 0;
}

// Remove the node with the smallest key (root node)
int heap::deleteMin(std::string *pId, int *pKey, void *ppData) {
  if (size == 0)
    return 1; // If heap is empty, return 1

  // Store the minimum node's data in the provided addresses
  if (pId != nullptr)
    *pId = data[1].id;
  if (pKey != nullptr)
    *pKey = data[1].key;
  if (ppData != nullptr)
    *(static_cast<void **>(ppData)) = data[1].pData;

  // Remove the root node from the hash table
  mapping->remove(data[1].id);

  // Replace root with the last node and decrease heap size
  data[1] = data[size--];

  // Percolate down to restore heap order
  percolateDown(1);

  return 0;
}

// Remove a node from the heap by its ID
int heap::remove(const std::string &id, int *pKey, void *ppData) {
  bool found;
  node *pn = static_cast<node *>(mapping->getPointer(id, &found));

  // If the node doesn't exist, return 1
  if (!found)
    return 1;

  // Store the node's data in the provided addresses
  if (pKey != nullptr)
    *pKey = pn->key;
  if (ppData != nullptr)
    *(static_cast<void **>(ppData)) = pn->pData;

  // Set the node's key to INT_MIN and delete it using deleteMin
  setKey(id, INT_MIN);
  deleteMin(nullptr, nullptr, nullptr);

  return 0;
}

// Percolate a node up the heap to restore heap order
void heap::percolateUp(int posCur) {
  node tmp = data[posCur];
  while (posCur > 1 && tmp.key < data[posCur / 2].key) {
    data[posCur] = data[posCur / 2];
    mapping->setPointer(data[posCur].id, &data[posCur]);
    posCur /= 2; // Correctly update posCur
  }
  data[posCur] = tmp;
  mapping->setPointer(tmp.id, &data[posCur]);
}

// Percolate a node down the heap to restore heap order
void heap::percolateDown(int posCur) {
  node tmp = data[posCur];
  int child;
  while (2 * posCur <= size) {
    child = 2 * posCur;

    // Select the smaller of the two children
    if (child < size && data[child + 1].key < data[child].key)
      child++;

    // If the child is smaller than current node, move it up
    if (data[child].key < tmp.key) {
      data[posCur] = data[child];
      mapping->setPointer(data[posCur].id, &data[posCur]);
      posCur = child;
    } else {
      break;
    }
  }
  data[posCur] = tmp;
  mapping->setPointer(tmp.id, &data[posCur]);
}

// Get the position of a node in the heap
int heap::getPos(node *pn) { return pn - &data[0]; }
