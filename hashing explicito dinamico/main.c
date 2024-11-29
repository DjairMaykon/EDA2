#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "hashing.h"

bool numeroRepetido(int *lista, int tamanho, int numero) {
  for (int i = 0; i < tamanho; i++) {
    if (lista[i] == numero) {
      return true;
    }
  }
  return false;
}

void gerarListaAleatoriaSemRepeticao(int *lista, int n, int limiteInferior, int limiteSuperior) {
  int i = 0;
  while (i < n) {
    int numero = limiteInferior + rand() % (limiteSuperior - limiteInferior + 1);
    if (!numeroRepetido(lista, i, numero)) {
      lista[i] = numero;
      i++;
    }
  }
}

void exibirLista(int *lista, int n) {
  for (int i = 0; i < n; i++) {
    printf("%d ", lista[i]);
  }
  printf("\n");
}

unsigned int hashFunc(HashTable* table, const int value) {
  return value % table->size;
}

int main() {
  int n, limiteInferior, limiteSuperior;

  // Configura a geração de números aleatórios
  srand(time(NULL));

  // Solicita o tamanho da lista e os limites
  printf("Digite o tamanho da lista: ");
  scanf("%d", &n);

  printf("Digite o limite inferior: ");
  scanf("%d", &limiteInferior);

  printf("Digite o limite superior: ");
  scanf("%d", &limiteSuperior);

  // Verifica se é possível gerar uma lista sem repetição
  if (limiteSuperior - limiteInferior + 1 < n) {
    printf("Erro: Não é possível gerar %d números únicos no intervalo especificado.\n", n);
    return 1;
  }

  // Aloca memória para a lista
  int *lista = (int *)malloc(n * sizeof(int));
  if (lista == NULL) {
    printf("Erro ao alocar memória.\n");
    return 1;
  }

  // Gera e exibe a lista
  gerarListaAleatoriaSemRepeticao(lista, n, limiteInferior, limiteSuperior);
  printf("Lista gerada sem repetição:\n");
  exibirLista(lista, n);

  HashTable* table = initHashTable(n, hashFunc);
  for (int i = 0; i < n; i++) {
    insert(table, lista[i]);
  }

  for (int i = 0; i < table->size; i++) {
    printf("Bucket [%d]: ", i);
    Node* current = table->buckets[i];
    while(current) {
      printf("%d ", current->value);
      current = current->next;
    }
    printf("\n");
  }

  freeHashTable(table);
  free(lista);

  return 0;
}
