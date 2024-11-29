#ifndef HASH_TABLE_H
#define HASH_TABLE_H

typedef struct Node {
  int value;
  struct Node* next;
} Node;

typedef struct HashTable HashTable;

struct HashTable {
  Node** buckets;
  int size;
  unsigned int (*hashFunc)(
    HashTable* table,
    const int value
  );
} ;

HashTable* initHashTable(int size, unsigned int (*hashFunc)(HashTable* table, const int value));
void insert(HashTable* table, int value);
Node* search(HashTable* table, int value);
void removeValue(HashTable* table, int value);
void freeHashTable(HashTable* table);

#endif