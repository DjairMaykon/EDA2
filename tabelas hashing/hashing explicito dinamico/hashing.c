#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashing.h"

HashTable* initHashTable(int size, unsigned int (*hashFunc)(HashTable* table, const int value)) {
  HashTable* table = (HashTable*)malloc(sizeof(HashTable));
  table->size = size;
  table->buckets = (Node**)malloc(size * sizeof(Node*));
  table->hashFunc = hashFunc;
  for (int i = 0; i < size; i++) {
    table->buckets[i] = NULL;
  }
  return table;
}

Node* createNode(int value) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  newNode->value = value;
  newNode->next = NULL;
  return newNode;
}

void insert(HashTable* table, int value) {
  unsigned int key = table->hashFunc(table, value);
  Node* current = table->buckets[key];

  while (current) {
    if (current->value == value) {
      return;
    }
    current = current->next;
  }

  Node* newNode = createNode(value);
  newNode->next = table->buckets[key];
  table->buckets[key] = newNode;
}

Node* search(HashTable* table, int value) {
  unsigned int index = table->hashFunc(table, value);
  Node* current = table->buckets[index];
  while (current) {
    if (current->value == value) {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

// Remove um par chave-valor da tabela hash
void removeKey(HashTable* table, int value) {
  unsigned int index = table->hashFunc(table, value);
  Node* current = table->buckets[index];
  Node* prev = NULL;
  
  while (current) {
    if (current->value == value) {
      if (prev) {
        prev->next = current->next;
      } else {
        table->buckets[index] = current->next;
      }
      free(current);
      return;
    }
  }
}

// Libera a memória da tabela hash
void freeHashTable(HashTable* table) {
  for (int i = 0; i < table->size; i++) {
    Node* current = table->buckets[i];
    while (current) {
      Node* temp = current;
      current = current->next;
      free(temp);
    }
  }
  free(table->buckets);
  free(table);
}
