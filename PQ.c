#include <stdio.h>
#include <stdlib.h>
#include "PQ.h"

static void swap(int i, int j, PQueue* p) {
    exch(p->pq[i], p->pq[j]);
    p->map[id(p->pq[i])] = i;
    p->map[id(p->pq[j])] = j;
}

void fix_up(Item *a, int k, PQueue* p) {
    while (k > 1 && more(a[k/2], a[k])) {
        swap(k, k/2, p);
        k = k/2;
    }
}

void fix_down(Item *a, int sz, int k, PQueue* p){
  while (2*k <= sz) {
    int j = 2*k;
    if (j < sz && more(a[j], a[j+1])){
      j++;
    }
    if (!more(a[k], a[j])) {
      break;
    }
    swap(k, j, p);
    k = j;
  }
}

PQueue* PQ_init(int maxN) {
    PQueue* p = (PQueue*)malloc(sizeof(PQueue));
    p->pq = (Item *) malloc((maxN+1) * sizeof (Item));
    p->map = (int *) calloc((maxN+1), sizeof (int)); // Utilizando calloc para facilitar na PQ_contains
    p->N = 0;
}

void PQ_insert(Item v, PQueue* p) {
    p->N++;
    p->pq[p->N] = v;
    p->map[id(v)] = p->N;
    fix_up(p->pq, p->N, p);
}

Item PQ_delmin(PQueue* p) {
    Item min = p->pq[1];
    swap(1, p->N, p);
    p->N--;
    fix_down(p->pq, p->N, 1, p);
    p->map[min.id] = 0; // Seta novamente para 0
    return min;
}

Item PQ_min(PQueue* p) {
    return p->pq[1];
}

void PQ_decrease_key(int id, double value, PQueue* p) {
    int i = p->map[id];
    value(p->pq[i]) = value;
    fix_up(p->pq, i, p);
}

bool PQ_contains(int id, PQueue* p){
    if(p->map[id] == 0){
        return false;
    }else{
        return true;
    }
}

bool PQ_empty(PQueue* p) {
    return p->N == 0;
}

int  PQ_size(PQueue* p) {
    return p->N;
}

void PQ_finish(PQueue* p) {
    free(p->pq);
    free(p->map);
    free(p);
}