#ifndef PQ_H
#define PQ_H

#include <stdbool.h>
#include "item.h"

typedef struct{
    Item *pq;
    int *map;
    int N;
} PQueue;

PQueue* PQ_init(int maxN); // cria uma min PQ com capacidade maxN
void PQ_insert(Item v, PQueue* p);   // Insere Item na PQ. A maior prioridade é a do Item com menor campo 'value'
Item PQ_delmin(PQueue* p);       // Remove Item com menor campo 'value' da PQ
void PQ_decrease_key(int id, double value, PQueue* p); // Muda a prioridade do nó com identificador 'id' para 'value'
Item PQ_min(PQueue* p);          // Retorna Item com menor campo 'value' da PQ
bool PQ_contains(int id, PQueue* p); // Retorna True se o elemento id estiver na PQ
bool PQ_empty(PQueue* p);        // Retorna True se a PQ não tem elementos
int  PQ_size(PQueue* p);         // Número de elementos na PQ
void PQ_finish(PQueue* p);       // Libera memória

#endif // PQ_H