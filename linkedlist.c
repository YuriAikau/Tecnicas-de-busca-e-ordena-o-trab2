#include "linkedlist.h"

Lista* inic_lista(void) {
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    lista->primeira = NULL;
    lista->ultima = NULL;
    return lista;
}

void insere_lista(Lista* lista, Item* aresta) {
    Celula* nova = (Celula*)malloc(sizeof(Celula));
    nova->aresta = aresta;
    nova->prox = NULL;

    if (lista->primeira == NULL)
        lista->primeira = nova;
    else {
        Celula* p = lista->primeira;
        while(p->prox != NULL)
            p = p->prox;
        p->prox = nova;
    }
}

void imprime_lista (Lista* lista) {
    Celula* p;

    for (p = lista->primeira; p != NULL; p = p->prox)
        printf("%d %f\n", p->aresta->id, p->aresta->value);
}

void destroi_lista(Lista* lista) {
    Celula* p = lista->primeira;
    Celula* t;

    while(p != NULL) {
        t = p->prox;
        free(p->aresta);
        free(p);
        p = t;
    }
    free(lista);
}