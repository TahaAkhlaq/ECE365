/*
  Name: Taha Akhlaq
  Description:
   * This program implements a hash table that uses linear probing to handle collisions.
   * It allows inserting, deleting, and searching for keys, and resizes the table when needed.
   * The program also supports attaching additional data to each key.
*/

#include "hash.h"
#include <string>
#include <vector>

using namespace std;

// Prime numbers to be used for table sizing and rehashing
const unsigned int primeNumbers[] = {
    53,        97,        193,       389,       769,       1543,     3079,
    6151,      12289,     24593,     49157,     98317,     196613,   393241,
    786433,    1572869,   3145739,   6291469,   12582917,  25165843, 50331653,
    100663319, 201326611, 402653189, 805306457, 1610612741};

// Constructor to initialize hash table
hashTable::hashTable(int size) {
  capacity = getPrime(size);
  data.resize(capacity);
  filled = 0;
}

// Insert function, returns 0 on success, 1 if key exists, and 2 if rehash fails
int hashTable::insert(const string &key, void *pv) {
  // Rehash if the table is more than half full
  if (filled >= capacity / 2) {
    if (!rehash()) {
      return 2; // Rehash failed
    }
  }

  int index = hash(key);
  while (data[index].isOccupied && !data[index].isDeleted) {
    if (data[index].key == key) {
      return 1; // Key already exists
    }
    index = (index + 1) % capacity; // Move to the next slot
  }

  // Insert the new key and mark it as occupied
  data[index].key = key;
  data[index].isOccupied = true;
  data[index].isDeleted = false;
  data[index].pv = pv;
  filled++; // Increase the count of occupied slots

  return 0; // Success
}

// Checks if the specified key is in the hash table
bool hashTable::contains(const string &key) { return findPos(key) != -1; }

// Gets the pointer associated with the key and returns nullptr if not found
void *hashTable::getPointer(const string &key, bool *b) {
  int pos = findPos(key);
  if (b != nullptr) {
    *b = (pos != -1);
  }
  return (pos == -1) ? nullptr : data[pos].pv;
}

// Sets the pointer for a key, returns 0 on success and 1 if the key does not exist
int hashTable::setPointer(const string &key, void *pv) {
  int pos = findPos(key);
  if (pos == -1) {
    return 1; // Key not found
  }
  data[pos].pv = pv;
  return 0;
}

// Mark the key as deleted without removing it from the table
bool hashTable::remove(const string &key) {
  int pos = findPos(key);
  if (pos == -1) {
    return false; // Key not found
  }
  data[pos].isDeleted = true;
  return true;
}

// Hash function to generate an index for a given key
int hashTable::hash(const string &key) {
  unsigned int hashVal = 0;
  for (char ch : key) {
    hashVal = 37 * hashVal + ch;
  }
  return hashVal % capacity;
}

// Finds the position of a key, returns -1 if not found
int hashTable::findPos(const string &key) {
  int index = hash(key);
  while (data[index].isOccupied) {
    if (data[index].key == key && !data[index].isDeleted) {
      return index; // Found key
    }
    index = (index + 1) % capacity; // Move to the next available slot
  }
  return -1; // Key not found
}

// Rehashes the table by resizing and reinserting elements
bool hashTable::rehash() {
  vector<hashItem> oldData = data;
  capacity = getPrime(2 * capacity);
  data.clear();
  data.resize(capacity);
  filled = 0;

  for (const auto &item : oldData) {
    if (item.isOccupied && !item.isDeleted) {
      // Reinsert existing items
      insert(item.key, item.pv);
    }
  }
  return true;
}

// Returns the next prime number larger than the given size
unsigned int hashTable::getPrime(int size) {
  for (unsigned int prime : primeNumbers) {
    if (prime > size) {
      return prime;
    }
  }
  // Return largest prime if size is too large
  return primeNumbers[sizeof(primeNumbers) / sizeof(primeNumbers[0]) - 1];
}
