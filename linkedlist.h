#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>

#include "item.h"

typedef struct cel Celula;
typedef struct lista Lista;

struct cel {
    Item* aresta;
    Celula* prox;
};

struct lista{
    Celula* primeira;
    Celula* ultima;
};

// Incializa um lista encadeada com sentinela
Lista* inic_lista(void);

// Insere um elemento Item na lista encadeada
void insere_lista(Lista* lista, Item* aresta);

// Imprime os elementos da lista encadeada
void imprime_lista (Lista* lista);

// Libera a memória alocada pela lista encadeada
void destroi_lista(Lista* lista);

#endif //LINKED_LIST_H